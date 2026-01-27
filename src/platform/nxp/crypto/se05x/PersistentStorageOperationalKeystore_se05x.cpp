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

#include "PersistentStorageOperationalKeystore_se05x.h"
#include "CHIPCryptoPALHsm_se05x_utils.h"
#include <lib/support/DefaultStorageKeyAllocator.h>

namespace chip {

using namespace chip::Crypto;

#define CHIP_SE05x_NODE_OP_KEY_INDEX            (SE051H_NODE_OP_KEY_ID - 1)
#define NUM_NODE_OP_KEY_INDEXES                 (5)                                                                                      \

#define CHIP_SE05x_NODE_OP_REF_KEY_TEMPLATE                                                                                        \
    {                                                                                                                              \
        0xA5, 0xA6, 0xB5, 0xB6, 0xA5, 0xA6, 0xB5, 0xB6, 0x7E, 0x00, 0x00, 0x00                                                     \
    }
#define CHIP_SE05x_NODE_OP_KEY_ID_INDEX 11

static CHIP_ERROR generate_node_oper_key()
{
    sss_object_t keyObject = { 0 };
    sss_status_t status    = kStatus_SSS_Fail;

    status = sss_key_object_init(&keyObject, &gex_sss_chip_ctx.ks);
    VerifyOrReturnError(status == kStatus_SSS_Success, CHIP_ERROR_INTERNAL);

    status = sss_key_object_allocate_handle(&keyObject, CHIP_SE05x_NODE_OP_KEY_INDEX + 1, kSSS_KeyPart_Pair,
                                            kSSS_CipherType_EC_NIST_P, 256, kKeyObject_Mode_Persistent);
    VerifyOrReturnError(status == kStatus_SSS_Success, CHIP_ERROR_INTERNAL);

    status = sss_key_store_generate_key(&gex_sss_chip_ctx.ks, &keyObject, 256, 0);
    VerifyOrReturnError(status == kStatus_SSS_Success, CHIP_ERROR_INTERNAL);

    return CHIP_NO_ERROR;
}

CHIP_ERROR PersistentStorageOpKeystorese05x::NewOpKeypairForFabric(FabricIndex fabricIndex,
                                                                   MutableByteSpan & outCertificateSigningRequest)
{
    P256SerializedKeypair serializedKeypair;
    uint8_t privatekey[32] = CHIP_SE05x_NODE_OP_REF_KEY_TEMPLATE;
    uint8_t publickey[65]  = {
        0x00,
    };
    size_t privatekey_len = sizeof(privatekey);
    size_t pubkey_len     = sizeof(publickey);
    uint32_t hsmKeyId     = 0;

    VerifyOrReturnError(mStorage != nullptr, CHIP_ERROR_INCORRECT_STATE);
    VerifyOrReturnError(IsValidFabricIndex(fabricIndex), CHIP_ERROR_INVALID_FABRIC_INDEX);
    VerifyOrReturnError(se05x_session_open() == CHIP_NO_ERROR, CHIP_ERROR_INTERNAL);

    // If a key is pending, we cannot generate for a different fabric index until we commit or revert.
    if ((mPendingFabricIndex != kUndefinedFabricIndex) && (fabricIndex != mPendingFabricIndex))
    {
        return CHIP_ERROR_INVALID_FABRIC_INDEX;
    }

    VerifyOrReturnError(outCertificateSigningRequest.size() >= Crypto::kMIN_CSR_Buffer_Size, CHIP_ERROR_BUFFER_TOO_SMALL);

    // Replace previous pending key pair, if any was previously allocated
    ResetPendingKey();

    mPendingKeypair = Platform::New<Crypto::P256Keypair>();
    VerifyOrReturnError(mPendingKeypair != nullptr, CHIP_ERROR_NO_MEMORY);

    hsmKeyId                                        = CHIP_SE05x_NODE_OP_KEY_INDEX + fabricIndex;
    privatekey[CHIP_SE05x_NODE_OP_KEY_ID_INDEX - 3] = (hsmKeyId >> 24) & 0xFF;
    privatekey[CHIP_SE05x_NODE_OP_KEY_ID_INDEX - 2] = (hsmKeyId >> 16) & 0xFF;
    privatekey[CHIP_SE05x_NODE_OP_KEY_ID_INDEX - 1] = (hsmKeyId >> 8) & 0xFF;
    privatekey[CHIP_SE05x_NODE_OP_KEY_ID_INDEX]     = (hsmKeyId >> 0) & 0xFF;

    memcpy(serializedKeypair.Bytes(), &publickey, pubkey_len);
    memcpy(serializedKeypair.Bytes() + pubkey_len, &privatekey[0], privatekey_len);
    serializedKeypair.SetLength(privatekey_len + pubkey_len);

    // This is required to ensure we pass the key id (mapping to fabric id) to CHIPCryptoPALHsm_se05x_p256.cpp NIST256 class.
    ReturnErrorOnFailure(mPendingKeypair->Deserialize(serializedKeypair));

    ChipLogDetail(Crypto,
                  "PersistentStorageOpKeystorese05x::NewOpKeypairForFabric ::Create NIST256 key in SE05x (at id = 0x%" PRIx32 ")",
                  hsmKeyId);
    mPendingKeypair->Initialize(Crypto::ECPKeyTarget::ECDSA);
    size_t csrLength = outCertificateSigningRequest.size();
    CHIP_ERROR err   = mPendingKeypair->NewCertificateSigningRequest(outCertificateSigningRequest.data(), csrLength);
    if (err != CHIP_NO_ERROR)
    {
        ResetPendingKey();
        return err;
    }

    outCertificateSigningRequest.reduce_size(csrLength);
    mPendingFabricIndex = fabricIndex;

    CHIP_ERROR nfcErr = se05x_disable_nfc_commision();
    if (nfcErr != CHIP_NO_ERROR)
    {
        ChipLogError(Crypto, "Failed to disable NFC commissioning: %" CHIP_ERROR_FORMAT, nfcErr.Format());
    }
    else
    {
        ChipLogProgress(Crypto, "NOTE: NFC commissioning disabled");
    }

    /* De initializing the task or thread which is monitoring the GPIO */
    se05x_host_gpio_notification_monitor_deinit();

    return CHIP_NO_ERROR;
}

#define SE05X_SET_BIN_DATA_TEMPLATE(keyid, buf)                     \
    {                                                               \
        const uint8_t buffer[] = {buf};                             \
        err = se05x_set_binary_data(keyid, buffer, sizeof(buffer)); \
        VerifyOrReturnError(err == CHIP_NO_ERROR, err);             \
    }


CHIP_ERROR PersistentStorageOpKeystorese05x::RemoveOpKeypairForFabric(FabricIndex fabricIndex)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    VerifyOrReturnError(mStorage != nullptr, CHIP_ERROR_INCORRECT_STATE);
    VerifyOrReturnError(IsValidFabricIndex(fabricIndex), CHIP_ERROR_INVALID_FABRIC_INDEX);
    VerifyOrReturnError(se05x_session_open() == CHIP_NO_ERROR, CHIP_ERROR_INTERNAL);

    uint32_t keyId = CHIP_SE05x_NODE_OP_KEY_INDEX + fabricIndex;
    SE05x_Result_t exists;
    bool allDeleted = true;

    ChipLogDetail(
        Crypto, "PersistentStorageOpKeystorese05x::RemoveOpKeypairForFabric ::Delete NIST256 key in SE05x (at id = 0x%" PRIx32 ")",
        keyId);
    Se05x_API_DeleteSecureObject(&((sss_se05x_session_t *) &gex_sss_chip_ctx.session)->s_ctx, keyId);

    // remove key from secure element
    if ((mPendingKeypair != nullptr) && (fabricIndex == mPendingFabricIndex))
    {
        RevertPendingKeypair();
    }

    err = mStorage->SyncDeleteKeyValue(DefaultStorageKeyAllocator::FabricOpKey(fabricIndex).KeyName());
    if (err == CHIP_ERROR_PERSISTED_STORAGE_VALUE_NOT_FOUND)
    {
        return CHIP_ERROR_INVALID_FABRIC_INDEX;
    }

    for (int i = 0; i < NUM_NODE_OP_KEY_INDEXES; i++)
    {
        uint32_t objectID = CHIP_SE05x_NODE_OP_KEY_INDEX + i;
        smStatus_t status =
            Se05x_API_CheckObjectExists(&((sss_se05x_session_t *) &gex_sss_chip_ctx.session)->s_ctx, objectID, &exists);
        if (status == SM_OK)
        {
            if (exists == kSE05x_Result_SUCCESS)
            {
                // Object exists — so don't enable NFC
                allDeleted = false;
                break;
            }
        }
        else
        {
            ChipLogError(Crypto, "SE05x error checking object 0x%" PRIx32, objectID);
            allDeleted = false;
            break;
        }
    }

    if (allDeleted)
    {
        err = se05x_enable_nfc_commision();
        if (err != CHIP_NO_ERROR)
        {
            ChipLogError(Crypto, "Failed to enable NFC commissioning: %" CHIP_ERROR_FORMAT, err.Format());
        }
        else
        {
            ChipLogProgress(Crypto, "NOTE: All node OP keys deleted — NFC commissioning enabled.");
        }
    }

    /* Create a dummy key pair at node operational key location,
    so that if the NFC commissioned data is provisioned, user can do the NFC commission. */
    if (keyId == CHIP_SE05x_NODE_OP_KEY_INDEX + 1)
    {
        err = generate_node_oper_key();
        if (err != CHIP_NO_ERROR)
        {
            ChipLogError(Crypto, "Failed to dummy key pair (at id = 0x%" PRIx32 ")", (uint32_t) (CHIP_SE05x_NODE_OP_KEY_INDEX + 1));
            return err;
        }
        else
        {
            ChipLogProgress(Crypto, "Created dummy key pair (at id = 0x%" PRIx32 ")",
                            (uint32_t) (CHIP_SE05x_NODE_OP_KEY_INDEX + 1));
        }

        /* Delete NFC commissioned data also, like Operational Credential cluster,
        Root CA, ICA, IPK, Access control cluster, Wi-fi / thread credentials,  */
        SE05X_SET_BIN_DATA_TEMPLATE(SE051H_OP_CRED_CLUSTER_ID, OCC);
        SE05X_SET_BIN_DATA_TEMPLATE(SE051H_ROOT_CER_ID, ROOT_CERTIFICATE);
        SE05X_SET_BIN_DATA_TEMPLATE(SE051H_IPK_ID, IPK);
        SE05X_SET_BIN_DATA_TEMPLATE(SE051H_ACL_ID, ACL);
        SE05X_SET_BIN_DATA_TEMPLATE(SE051H_WIFI_CRED_ID_APP_8_4, WIFI_CRED_DATA);
        SE05X_SET_BIN_DATA_TEMPLATE(SE051H_WIFI_CRED_ID_APP_8_8, WIFI_CRED_DATA);
        {
            uint8_t ncc_buf[] = {
              DATA_VERSION_NCC,
              CLUSTER_REVISION_NCC,
              FEATUREMAP_NCC,
              ATTRIBUTE_LIST_NCC,
              ACCEPTED_COMMAND_LIST_NCC,
              GENERATED_COMMAND_LIST_NCC,
              MAX_NETWORKS,
              NETWORKS,
              NETWORKS_FILLER,
              SCAN_MAX_TIME_SECONDS,
              CONNECT_MAX_TIME_SECONDS,
              INTERFACE_ENABLED,
              LAST_NETWORKING_STATUS,
              LAST_NETWORK_ID,
              LAST_NETWORK_ID_FILLER,
              LAST_CONNECT_ERROR_VALUE_NCC,
              LAST_CONNECT_ERROR_VALUE_FILLER_NCC,
              SUPPORTED_WIFI_BANDS_NCC,
              SUPPORTED_THREAD_FEATURES_NCC,
              THREAD_VERSION_NCC,
            };
            err = se05x_set_binary_data(SE051H_NCC_ID, ncc_buf, sizeof(ncc_buf));
            VerifyOrReturnError(err == CHIP_NO_ERROR, err);
        }

        {
            uint8_t Genaral_comm_cluster_data[] = {
              DATA_VERSION_GCC,
              CLUSTER_REVISION_GCC,
              FEATUREMAP_GCC,
              ATTRIBUTE_LIST_GCC,
              ACCEPTED_COMMAND_LIST_GCC,
              GENERATED_COMMAND_LIST_GCC,
              BREADCRUMB,
              BASIC_COMMISSIONING_INFO,
              REGULATORY_CONFIG,
              LOCATION_CAPABILITY,
              SUPPORTS_CONCURRENT_CONNECTION,
              TC_ACCEPTED_VERSION,
              TC_MIN_REQUIRED_VERSION,
              TC_ACKNOWLEDGEMENTS,
              TC_ACKNOWLEDGEMENTS_REQUIRED,
              TC_UPDATE_DEADLINE,
              IS_COMM_WITHOUT_POWER,
            };
            err = se05x_set_binary_data(SE051H_GENERAL_COMM_CLUSTER_ID, Genaral_comm_cluster_data, sizeof(Genaral_comm_cluster_data));
            VerifyOrReturnError(err == CHIP_NO_ERROR, err);
        }
    }

    return err;
}

} // namespace chip
