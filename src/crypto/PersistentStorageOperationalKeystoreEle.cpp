/*
 *    Copyright (c) 2025 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include <crypto/OperationalKeystore.h>
#include <lib/core/CHIPEncoding.h>
#include <lib/core/CHIPError.h>
#include <lib/core/DataModelTypes.h>
#include <lib/support/CHIPMem.h>
#include <lib/support/CodeUtils.h>

#include "PersistentStorageOperationalKeystore.h"
#include "hsm_api.h"

constexpr int kKeyGroup              = 1;
constexpr int kPubkeySize            = 65;
constexpr unsigned int kKeyGroupSync = 0x1U << 7;

// Pass keyId == 0 to hsm_generate_key so ELE allocates a fresh random keyId and writes it back.
constexpr uint32_t kEleAllocateKeyId = 0;

// data_id of the committed fabricIndex->keyId table stored in ELE data storage (ASCII "MATP").
constexpr uint32_t kFabricKeyMapDataId = 0x4D415450;

// Table layout: [count:uint8][ (fabricIndex:uint8, keyId:uint32 little-endian) x count ].
// Sized to CHIP_CONFIG_MAX_FABRICS committed entries plus one reserved pending slot, so the stack
// buffer stays small (~86 bytes): these helpers run on the CASE signing path, which uses a small
// task stack on embedded targets.
constexpr size_t kMapEntrySize   = 1 + sizeof(uint32_t);
constexpr size_t kMapMaxEntries  = CHIP_CONFIG_MAX_FABRICS + 1;
constexpr size_t kMapMaxBytes    = 1 + kMapMaxEntries * kMapEntrySize;

namespace chip {

using namespace chip::Crypto;

// fabricIndex 0 is kUndefinedFabricIndex (never assigned to a real fabric), reused as a reserved
// slot in the same table to persist the pending keyId so it can be reclaimed after a power loss
// between key generation and commit/revert (the pending key may already be NVM-resident).
constexpr FabricIndex kReservedFabricIndex = kUndefinedFabricIndex;

namespace {

using Credentials::ele::EleManagerKeystore;

CHIP_ERROR LoadCommittedKeyId(EleManagerKeystore * ele, FabricIndex fabric, uint32_t & outKeyId)
{
    VerifyOrReturnError(ele != nullptr, CHIP_ERROR_INCORRECT_STATE);

    uint8_t buf[kMapMaxBytes];
    size_t size    = sizeof(buf);
    hsm_err_t hsmret = ele->EleRetrieveData(kFabricKeyMapDataId, buf, size);
    // HSM_UNKNOWN_ID means the table has never been written (no committed keys); any other error is a
    // real ELE/IO fault and must not be reported as "key absent", or a transient fault could make the
    // caller discard a valid fabric.
    if (hsmret == HSM_UNKNOWN_ID)
    {
        return CHIP_ERROR_KEY_NOT_FOUND;
    }
    VerifyOrReturnError(hsmret == HSM_NO_ERROR, CHIP_ERROR_HSM);
    VerifyOrReturnError(size >= 1, CHIP_ERROR_KEY_NOT_FOUND);

    uint8_t count = buf[0];
    VerifyOrReturnError(count <= kMapMaxEntries, CHIP_ERROR_INCORRECT_STATE);
    VerifyOrReturnError(size >= 1 + static_cast<size_t>(count) * kMapEntrySize, CHIP_ERROR_INCORRECT_STATE);

    const uint8_t * cursor = buf + 1;
    for (uint8_t i = 0; i < count; i++)
    {
        FabricIndex entryFabric = cursor[0];
        if (entryFabric == fabric)
        {
            outKeyId = Encoding::LittleEndian::Get32(cursor + 1);
            return CHIP_NO_ERROR;
        }
        cursor += kMapEntrySize;
    }
    return CHIP_ERROR_KEY_NOT_FOUND;
}

CHIP_ERROR StoreCommittedKeyId(EleManagerKeystore * ele, FabricIndex fabric, uint32_t keyId)
{
    VerifyOrReturnError(ele != nullptr, CHIP_ERROR_INCORRECT_STATE);

    uint8_t buf[kMapMaxBytes];
    size_t size    = sizeof(buf);
    uint8_t count;
    hsm_err_t hsmret = ele->EleRetrieveData(kFabricKeyMapDataId, buf, size);
    if (hsmret == HSM_NO_ERROR && size >= 1)
    {
        count = buf[0];
        VerifyOrReturnError(count <= kMapMaxEntries, CHIP_ERROR_INCORRECT_STATE);
        VerifyOrReturnError(size >= 1 + static_cast<size_t>(count) * kMapEntrySize, CHIP_ERROR_INCORRECT_STATE);
    }
    else if (hsmret == HSM_UNKNOWN_ID || (hsmret == HSM_NO_ERROR && size < 1))
    {
        // Table absent (HSM_UNKNOWN_ID) or present but empty (zero-length blob): start a fresh one,
        // matching how LoadCommittedKeyId/DeleteCommittedKeyId treat an empty blob as "no table". Any
        // other retrieve error is a real ELE/IO fault; treating it as an empty table would overwrite
        // the existing mapping and lose keys.
        count  = 0;
        buf[0] = 0;
    }
    else
    {
        return CHIP_ERROR_HSM;
    }

    uint8_t * cursor = buf + 1;
    for (uint8_t i = 0; i < count; i++)
    {
        if (cursor[0] == fabric)
        {
            Encoding::LittleEndian::Put32(cursor + 1, keyId);
            return (ele->EleStoreData(kFabricKeyMapDataId, buf, 1 + static_cast<size_t>(count) * kMapEntrySize) == HSM_NO_ERROR)
                ? CHIP_NO_ERROR
                : CHIP_ERROR_HSM;
        }
        cursor += kMapEntrySize;
    }

    VerifyOrReturnError(count < kMapMaxEntries, CHIP_ERROR_NO_MEMORY);
    cursor[0] = fabric;
    Encoding::LittleEndian::Put32(cursor + 1, keyId);
    buf[0]    = static_cast<uint8_t>(count + 1);

    return (ele->EleStoreData(kFabricKeyMapDataId, buf, 1 + static_cast<size_t>(count + 1) * kMapEntrySize) == HSM_NO_ERROR)
        ? CHIP_NO_ERROR
        : CHIP_ERROR_HSM;
}

CHIP_ERROR DeleteCommittedKeyId(EleManagerKeystore * ele, FabricIndex fabric)
{
    VerifyOrReturnError(ele != nullptr, CHIP_ERROR_INCORRECT_STATE);

    uint8_t buf[kMapMaxBytes];
    size_t size    = sizeof(buf);
    hsm_err_t hsmret = ele->EleRetrieveData(kFabricKeyMapDataId, buf, size);
    // Table never written: nothing to delete. Any other retrieve error is a real ELE/IO fault; the
    // entry may still exist, so report a hard error instead of a false success.
    if (hsmret == HSM_UNKNOWN_ID)
    {
        return CHIP_NO_ERROR;
    }
    VerifyOrReturnError(hsmret == HSM_NO_ERROR, CHIP_ERROR_HSM);
    if (size < 1)
    {
        return CHIP_NO_ERROR;
    }

    uint8_t count = buf[0];
    VerifyOrReturnError(count <= kMapMaxEntries, CHIP_ERROR_INCORRECT_STATE);
    VerifyOrReturnError(size >= 1 + static_cast<size_t>(count) * kMapEntrySize, CHIP_ERROR_INCORRECT_STATE);

    uint8_t * cursor = buf + 1;
    for (uint8_t i = 0; i < count; i++)
    {
        if (cursor[0] == fabric)
        {
            // Removing the last entry: delete the whole blob so "no committed key" is represented as
            // an absent table (retrieve -> HSM_UNKNOWN_ID) rather than a lingering zero-entry table.
            if (count == 1)
            {
                return (ele->EleDeleteData(kFabricKeyMapDataId) == HSM_NO_ERROR) ? CHIP_NO_ERROR : CHIP_ERROR_HSM;
            }
            uint8_t * next = cursor + kMapEntrySize;
            uint8_t * end  = buf + 1 + static_cast<size_t>(count) * kMapEntrySize;
            memmove(cursor, next, static_cast<size_t>(end - next));
            buf[0] = static_cast<uint8_t>(count - 1);
            return (ele->EleStoreData(kFabricKeyMapDataId, buf, 1 + static_cast<size_t>(count - 1) * kMapEntrySize) == HSM_NO_ERROR)
                ? CHIP_NO_ERROR
                : CHIP_ERROR_HSM;
        }
        cursor += kMapEntrySize;
    }
    return CHIP_NO_ERROR;
}

// Atomically promote the reserved-slot pending key to a committed fabric entry: in one blob rewrite,
// upsert (fabric -> keyId) and drop the (kReservedFabricIndex -> *) entry. A separate write-then-
// delete sequence could lose power between the two writes, leaving the same keyId under both fabric
// and the reserved slot; a later ReconcilePendingKey would then strict-delete a live committed key.
CHIP_ERROR PromoteReservedToFabric(EleManagerKeystore * ele, FabricIndex fabric, uint32_t keyId)
{
    VerifyOrReturnError(ele != nullptr, CHIP_ERROR_INCORRECT_STATE);

    uint8_t buf[kMapMaxBytes];
    size_t size      = sizeof(buf);
    uint8_t count    = 0;
    hsm_err_t hsmret = ele->EleRetrieveData(kFabricKeyMapDataId, buf, size);
    if (hsmret == HSM_NO_ERROR && size >= 1)
    {
        count = buf[0];
        VerifyOrReturnError(count <= kMapMaxEntries, CHIP_ERROR_INCORRECT_STATE);
        VerifyOrReturnError(size >= 1 + static_cast<size_t>(count) * kMapEntrySize, CHIP_ERROR_INCORRECT_STATE);
    }
    else if (hsmret == HSM_UNKNOWN_ID || (hsmret == HSM_NO_ERROR && size < 1))
    {
        count = 0;
    }
    else
    {
        return CHIP_ERROR_HSM;
    }

    uint8_t * base       = buf + 1;
    bool fabricFound     = false;
    uint8_t reservedIdx  = count;
    for (uint8_t i = 0; i < count; i++)
    {
        uint8_t * entry = base + static_cast<size_t>(i) * kMapEntrySize;
        if (entry[0] == fabric)
        {
            Encoding::LittleEndian::Put32(entry + 1, keyId);
            fabricFound = true;
        }
        else if (entry[0] == kReservedFabricIndex)
        {
            reservedIdx = i;
        }
    }

    if (!fabricFound)
    {
        VerifyOrReturnError(count < kMapMaxEntries, CHIP_ERROR_NO_MEMORY);
        uint8_t * entry = base + static_cast<size_t>(count) * kMapEntrySize;
        entry[0]        = fabric;
        Encoding::LittleEndian::Put32(entry + 1, keyId);
        count++;
    }

    if (reservedIdx < count)
    {
        uint8_t * slot = base + static_cast<size_t>(reservedIdx) * kMapEntrySize;
        uint8_t * next = slot + kMapEntrySize;
        uint8_t * end  = base + static_cast<size_t>(count) * kMapEntrySize;
        memmove(slot, next, static_cast<size_t>(end - next));
        count--;
    }

    buf[0] = count;
    return (ele->EleStoreData(kFabricKeyMapDataId, buf, 1 + static_cast<size_t>(count) * kMapEntrySize) == HSM_NO_ERROR)
        ? CHIP_NO_ERROR
        : CHIP_ERROR_HSM;
}

// True if keyId is referenced by any committed (non-reserved) fabric entry. Used to avoid deleting a
// key that a committed fabric still depends on.
bool IsKeyIdReferencedByCommitted(EleManagerKeystore * ele, uint32_t keyId)
{
    VerifyOrReturnValue(ele != nullptr, false);

    uint8_t buf[kMapMaxBytes];
    size_t size      = sizeof(buf);
    hsm_err_t hsmret = ele->EleRetrieveData(kFabricKeyMapDataId, buf, size);
    if (hsmret != HSM_NO_ERROR || size < 1)
    {
        return false;
    }
    uint8_t count = buf[0];
    if (count > kMapMaxEntries || size < 1 + static_cast<size_t>(count) * kMapEntrySize)
    {
        return false;
    }

    const uint8_t * cursor = buf + 1;
    for (uint8_t i = 0; i < count; i++)
    {
        if (cursor[0] != kReservedFabricIndex && Encoding::LittleEndian::Get32(cursor + 1) == keyId)
        {
            return true;
        }
        cursor += kMapEntrySize;
    }
    return false;
}

} // namespace

namespace Credentials {
namespace ele {

void EleManagerKeystore::ReconcilePendingKey()
{
    // A pending keyId persisted in the reserved slot but never promoted (no commit) or cleared (no
    // revert) means power was lost mid-commissioning. The key may have been synced to NVM by another
    // fabric's commit, so strict-delete it and drop the slot. Best-effort: failures are logged only.
    uint32_t orphanKeyId = 0;
    if (LoadCommittedKeyId(this, kReservedFabricIndex, orphanKeyId) != CHIP_NO_ERROR)
    {
        return;
    }
    // Defense in depth against a non-atomic promote: if the same keyId is also referenced by a
    // committed fabric, deleting it would brick that fabric. Only drop the stale reserved slot then.
    if (IsKeyIdReferencedByCommitted(this, orphanKeyId))
    {
        ChipLogProgress(Crypto, "Reserved slot keyId 0x%x is a committed key; dropping slot only\n", orphanKeyId);
        DeleteCommittedKeyId(this, kReservedFabricIndex);
        return;
    }
    ChipLogProgress(Crypto, "Reclaiming orphaned pending ELE keyId 0x%x from previous session\n", orphanKeyId);
    EleDeleteKeySync(orphanKeyId);
    DeleteCommittedKeyId(this, kReservedFabricIndex);
}

} // namespace ele
} // namespace Credentials

bool PersistentStorageOperationalKeystore::HasPendingOpKeypair() const
{
    return (mPendingFabricIndex != kUndefinedFabricIndex);
}

bool PersistentStorageOperationalKeystore::HasOpKeypairForFabric(FabricIndex fabricIndex) const
{
    VerifyOrReturnError(IsValidFabricIndex(fabricIndex), false);
    // If there was a pending keypair, then there's really a usable key
    if (mIsPendingKeypairActive && (fabricIndex == mPendingFabricIndex))
    {
        return true;
    }

    // A committed keypair exists iff we have a persisted fabricIndex->keyId mapping in ELE.
    uint32_t keyId = 0;
    if (LoadCommittedKeyId(mEleManager.get(), fabricIndex, keyId) == CHIP_NO_ERROR)
    {
        ChipLogDetail(Crypto, "Found keypair for fabric: %d (ELE keyId 0x%x).\n", fabricIndex, keyId);
        return true;
    }

    ChipLogDetail(Crypto, "No keypair for fabric: %d found.\n", fabricIndex);
    return false;
}

CHIP_ERROR PersistentStorageOperationalKeystore::NewOpKeypairForFabric(FabricIndex fabricIndex,
                                                                       MutableByteSpan & outCertificateSigningRequest)
{
    op_generate_key_args_t key_gen_args;
    uint32_t keyId;
    hsm_err_t hsm_err;
    CHIP_ERROR err;

    VerifyOrReturnError(IsValidFabricIndex(fabricIndex), CHIP_ERROR_INVALID_FABRIC_INDEX);
    // If a key is pending, we cannot generate for a different fabric index until we commit or revert.
    if ((mPendingFabricIndex != kUndefinedFabricIndex) && (fabricIndex != mPendingFabricIndex))
    {
        return CHIP_ERROR_INVALID_FABRIC_INDEX;
    }
    VerifyOrReturnError(outCertificateSigningRequest.size() >= Crypto::kMIN_CSR_Buffer_Size, CHIP_ERROR_BUFFER_TOO_SMALL);

    // Drop any previous pending key for this fabric. mPendingKeyId is the sole source of truth for
    // "an ELE pending key needs deleting"; do not also gate on mPendingFabricIndex, which is cleared
    // independently by ResetPendingKey() and could leave the key undeleted while its id is zeroed
    // below (orphaned key). Use a strict delete: the pending key lives in the shared kKeyGroup, so a
    // commit for another fabric may already have synced it to NVM, where a non-strict delete cannot
    // reach it. Best-effort (return value ignored): a stale pending key must not block a new one.
    if (mEleManager->mPendingKeyId != 0)
    {
        mEleManager->EleDeleteKeySync(mEleManager->mPendingKeyId);
    }
    mEleManager->mPendingKeyId = 0;
    DeleteCommittedKeyId(mEleManager.get(), kReservedFabricIndex);
    ResetPendingKey();

    // For UpdateNOC the committed key of `fabricIndex` must keep working until commit (fail-safe
    // revert), so do NOT delete it here. Generate the pending key under a fresh ELE-allocated keyId.
    memset(&key_gen_args, 0, sizeof(key_gen_args));
    keyId                       = kEleAllocateKeyId; // 0 -> ELE allocates and writes back a random keyId
    key_gen_args.key_identifier = &keyId;
    key_gen_args.key_group      = kKeyGroup;
    key_gen_args.key_lifetime   = HSM_SE_KEY_STORAGE_PERSISTENT;
    key_gen_args.key_usage =
        HSM_KEY_USAGE_SIGN_HASH | HSM_KEY_USAGE_VERIFY_HASH | HSM_KEY_USAGE_SIGN_MSG | HSM_KEY_USAGE_VERIFY_MSG;
    key_gen_args.permitted_algo = PERMITTED_ALGO_ECDSA_SHA256;
    // "sync" not set: pending key stays in HSM local memory (not NVM) until CommitOpKeypairForFabric().
    key_gen_args.flags         = 0;
    key_gen_args.key_type      = HSM_KEY_TYPE_ECC_NIST;
    key_gen_args.bit_key_sz    = HSM_KEY_SIZE_ECC_NIST_256;
    key_gen_args.key_lifecycle = (hsm_key_lifecycle_t) 0;
    hsm_err                    = hsm_generate_key(mEleManager->key_mgmt_hdl, &key_gen_args);
    ChipLogDetail(Crypto, "Generate new pending keypair returns: 0x%x, ELE keyId 0x%x\n", hsm_err, keyId);
    if (hsm_err != HSM_NO_ERROR)
        return CHIP_ERROR_HSM;

    // Persist the pending keyId in the reserved slot before doing anything else: a commit for another
    // fabric can group-sync this key to NVM, so if power is lost before commit/revert the RAM-only id
    // would be gone while the key survives, unreachable and unremovable. The reserved slot lets a
    // startup reconciliation reclaim it.
    err = StoreCommittedKeyId(mEleManager.get(), kReservedFabricIndex, keyId);
    if (err != CHIP_NO_ERROR)
    {
        mEleManager->EleDeleteKeySync(keyId);
        return err;
    }

    // generate the CSR with the pending key.
    size_t csrLength = outCertificateSigningRequest.size();
    err              = mEleManager->EleGenerateCSR(keyId, outCertificateSigningRequest.data(), csrLength);
    if (err != CHIP_NO_ERROR)
    {
        mEleManager->EleDeleteKeySync(keyId);
        DeleteCommittedKeyId(mEleManager.get(), kReservedFabricIndex);
        return err;
    }

    outCertificateSigningRequest.reduce_size(csrLength);
    mPendingFabricIndex        = fabricIndex;
    mEleManager->mPendingKeyId = keyId;

    return CHIP_NO_ERROR;
}

CHIP_ERROR PersistentStorageOperationalKeystore::ActivateOpKeypairForFabric(FabricIndex fabricIndex,
                                                                            const Crypto::P256PublicKey & nocPublicKey)
{
    uint8_t pubkey[kPubkeySize];
    hsm_err_t hsmret = HSM_NO_ERROR;

    VerifyOrReturnError(IsValidFabricIndex(fabricIndex) && (fabricIndex == mPendingFabricIndex), CHIP_ERROR_INVALID_FABRIC_INDEX);

    // Validate public key being activated matches last generated pending keypair
    // public key size is 65
    pubkey[0] = 0x04;

    uint32_t pendingKeyId = mEleManager->mPendingKeyId;
    VerifyOrReturnError(pendingKeyId != 0, CHIP_ERROR_INCORRECT_STATE);

    op_pub_key_recovery_args_t args = { 0 };
    args.key_identifier             = pendingKeyId;
    args.out_key_size               = 64;
    args.out_key                    = &pubkey[1];
    hsmret                          = hsm_pub_key_recovery(mEleManager->key_store_hdl, &args);
    if (hsmret != HSM_NO_ERROR)
    {
        ChipLogDetail(Crypto, "recover public key failed. ret:0x%x\n", hsmret);
        return CHIP_ERROR_HSM;
    }

    if (memcmp(pubkey, nocPublicKey.ConstBytes(), sizeof(pubkey)))
    {
        ChipLogDetail(Crypto, "the public key being activated doesn't match pending key.\n");
        return CHIP_ERROR_INVALID_PUBLIC_KEY;
    }

    mIsPendingKeypairActive = true;

    return CHIP_NO_ERROR;
}

CHIP_ERROR PersistentStorageOperationalKeystore::CommitOpKeypairForFabric(FabricIndex fabricIndex)
{
    hsm_err_t hsmret = HSM_NO_ERROR;
    VerifyOrReturnError(IsValidFabricIndex(fabricIndex) && (fabricIndex == mPendingFabricIndex), CHIP_ERROR_INVALID_FABRIC_INDEX);
    VerifyOrReturnError(mIsPendingKeypairActive == true, CHIP_ERROR_INCORRECT_STATE);

    uint32_t pendingKeyId = mEleManager->mPendingKeyId;
    VerifyOrReturnError(pendingKeyId != 0, CHIP_ERROR_INCORRECT_STATE);

    // Previously committed key for this fabric (present for UpdateNOC, absent for AddNOC).
    uint32_t oldKeyId       = 0;
    bool hasOldCommittedKey = (LoadCommittedKeyId(mEleManager.get(), fabricIndex, oldKeyId) == CHIP_NO_ERROR);

    // Persist the pending key to NVM. On failure, leave everything pending so fail-safe can revert.
    op_manage_key_group_args_t keygroup_args;
    memset(&keygroup_args, 0, sizeof(keygroup_args));
    keygroup_args.key_group = kKeyGroup;
    keygroup_args.flags     = kKeyGroupSync;
    hsmret                  = hsm_manage_key_group(mEleManager->key_mgmt_hdl, &keygroup_args);
    if (hsmret != HSM_NO_ERROR)
    {
        ChipLogDetail(Crypto, "commit key failed. ret: 0x%x\n", hsmret);
        return CHIP_ERROR_HSM;
    }
    ChipLogDetail(Crypto, "commit key successfully (ELE keyId 0x%x).\n", pendingKeyId);

    // Atomically promote pending->committed: one blob rewrite that adds the fabric entry and drops
    // the reserved slot, so a crash can never leave the same keyId under both (which would make
    // ReconcilePendingKey strict-delete a live committed key). On failure leave everything pending so
    // fail-safe can revert.
    CHIP_ERROR err = PromoteReservedToFabric(mEleManager.get(), fabricIndex, pendingKeyId);
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(Crypto, "Failed to persist ELE keyId mapping for fabric %d: %" CHIP_ERROR_FORMAT, fabricIndex, err.Format());
        // The group sync above already flushed the pending key to NVM. Without a mapping entry it is
        // an unreachable orphan, and RevertPendingKeypair's non-strict delete cannot remove an
        // NVM-resident key; only a strict delete can.
        mEleManager->EleDeleteKeySync(pendingKeyId);
        mEleManager->mPendingKeyId = 0;
        DeleteCommittedKeyId(mEleManager.get(), kReservedFabricIndex);
        ResetPendingKey();
        return err;
    }

    // Delete the previous committed key (UpdateNOC rotation). Best-effort: the mapping already points
    // at the new key, so a failure here at worst leaves oldKeyId as an orphan, never loses the fabric.
    if (hasOldCommittedKey && (oldKeyId != pendingKeyId))
    {
        hsmret = mEleManager->EleDeleteKeySync(oldKeyId);
        if (hsmret != HSM_NO_ERROR)
        {
            ChipLogError(Crypto, "Failed to delete previous ELE keyId 0x%x for fabric %d: 0x%x\n", oldKeyId, fabricIndex, hsmret);
        }
    }

    mEleManager->mPendingKeyId = 0;
    ResetPendingKey();
    return CHIP_NO_ERROR;
}

CHIP_ERROR PersistentStorageOperationalKeystore::ExportOpKeypairForFabric(FabricIndex fabricIndex,
                                                                          Crypto::P256SerializedKeypair & outKeypair)
{
    return CHIP_ERROR_NOT_IMPLEMENTED;
}

CHIP_ERROR PersistentStorageOperationalKeystore::RemoveOpKeypairForFabric(FabricIndex fabricIndex)
{
    VerifyOrReturnError(IsValidFabricIndex(fabricIndex), CHIP_ERROR_INVALID_FABRIC_INDEX);

    // Clear a pending key for this fabric, then fall through to also delete its committed key: during
    // an UpdateNOC the fabric has both. Strict delete because the pending key lives in the shared
    // kKeyGroup and may already be NVM-resident from another fabric's commit.
    if (fabricIndex == mPendingFabricIndex)
    {
        if (mEleManager->mPendingKeyId != 0)
        {
            mEleManager->EleDeleteKeySync(mEleManager->mPendingKeyId);
        }
        mEleManager->mPendingKeyId = 0;
        DeleteCommittedKeyId(mEleManager.get(), kReservedFabricIndex);
        ResetPendingKey();
    }

    uint32_t keyId = 0;
    CHIP_ERROR err = LoadCommittedKeyId(mEleManager.get(), fabricIndex, keyId);
    if (err == CHIP_ERROR_KEY_NOT_FOUND)
    {
        ChipLogDetail(Crypto, "No committed keypair for fabric: %d. No need to delete\n", fabricIndex);
        return CHIP_NO_ERROR;
    }
    ReturnErrorOnFailure(err);

    // Mapping is dropped before the key so a failed key deletion leaves at most an unreachable
    // orphan. The reverse order risks a stale entry pointing at a deleted key, which would make a
    // later SignWithOpKeypair fail obscurely and HasOpKeypairForFabric still report the fabric.
    ReturnErrorOnFailure(DeleteCommittedKeyId(mEleManager.get(), fabricIndex));

    return (mEleManager->EleDeleteKeySync(keyId) == HSM_NO_ERROR) ? CHIP_NO_ERROR : CHIP_ERROR_HSM;
}

void PersistentStorageOperationalKeystore::RevertPendingKeypair()
{
    // Delete the pending ELE key with a strict delete; leave the committed key untouched so the
    // fabric keeps working after a fail-safe revert of an UpdateNOC. Strict is required because the
    // pending key lives in the shared kKeyGroup and a commit for another fabric may already have
    // synced it to NVM, where a non-strict delete cannot reach it. Gate only on mPendingKeyId:
    // mPendingFabricIndex is cleared independently by ResetPendingKey() and would leak the key.
    if (mEleManager->mPendingKeyId != 0)
    {
        mEleManager->EleDeleteKeySync(mEleManager->mPendingKeyId);
    }
    mEleManager->mPendingKeyId = 0;
    DeleteCommittedKeyId(mEleManager.get(), kReservedFabricIndex);
    ResetPendingKey();
}

CHIP_ERROR PersistentStorageOperationalKeystore::SignWithOpKeypair(FabricIndex fabricIndex, const ByteSpan & message,
                                                                   Crypto::P256ECDSASignature & outSignature) const
{
    uint8_t sig[kP256_ECDSA_Signature_Length_Raw];
    hsm_err_t hsmret = HSM_NO_ERROR;
    uint32_t keyId   = 0;

    VerifyOrReturnError(IsValidFabricIndex(fabricIndex), CHIP_ERROR_INVALID_FABRIC_INDEX);

    // Use the active pending key if any, otherwise the committed key.
    if (mIsPendingKeypairActive && (fabricIndex == mPendingFabricIndex))
    {
        VerifyOrReturnError(mEleManager->mPendingKeyId != 0, CHIP_ERROR_INCORRECT_STATE);
        keyId = mEleManager->mPendingKeyId;
    }
    else
    {
        ReturnErrorOnFailure(LoadCommittedKeyId(mEleManager.get(), fabricIndex, keyId));
    }

    hsmret = mEleManager->EleSignMessage(keyId, message.data(), message.size(), sig, kP256_ECDSA_Signature_Length_Raw);
    VerifyOrReturnError(hsmret == HSM_NO_ERROR, CHIP_ERROR_INTERNAL);
    VerifyOrReturnError(outSignature.SetLength(kP256_ECDSA_Signature_Length_Raw) == CHIP_NO_ERROR, CHIP_ERROR_INTERNAL);
    memcpy(outSignature.Bytes(), sig, kP256_ECDSA_Signature_Length_Raw);

    return CHIP_NO_ERROR;
}

Crypto::P256Keypair * PersistentStorageOperationalKeystore::AllocateEphemeralKeypairForCASE()
{
    return Platform::New<Crypto::P256Keypair>();
}

void PersistentStorageOperationalKeystore::ReleaseEphemeralKeypair(Crypto::P256Keypair * keypair)
{
    Platform::Delete<Crypto::P256Keypair>(keypair);
}

CHIP_ERROR PersistentStorageOperationalKeystore::MigrateOpKeypairForFabric(FabricIndex fabricIndex,
                                                                           OperationalKeystore & operationalKeystore) const
{
    return CHIP_ERROR_NOT_IMPLEMENTED;
}

} // namespace chip
