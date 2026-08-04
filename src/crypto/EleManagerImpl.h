/*
 *    Copyright (c) 2025 Project CHIP Authors
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

#pragma once

#include "hsm_api.h"
#include <lib/core/CHIPError.h>
#include <lib/support/logging/CHIPLogging.h>
#include <memory>

namespace chip {
namespace Credentials {
namespace ele {

class EleManagerImpl
{
public:
    EleManagerImpl()          = default;
    virtual ~EleManagerImpl() = default;

    hsm_err_t EleDeleteKey(uint32_t keyId);
    // Same as EleDeleteKey but sets the STRICT flag so the deletion is written back to NVM
    // (a non-strict delete only affects HSM local memory and is lost on reset, leaving the
    // key resurrected in the NVM key store on the next reload).
    hsm_err_t EleDeleteKeySync(uint32_t keyId);
    CHIP_ERROR EleGenerateCSR(uint32_t keyId, uint8_t * csr, size_t & csrLength);
    hsm_err_t EleSignMessage(uint32_t keyId, const uint8_t * msg, size_t msgSize, uint8_t * sig, size_t sigSize);

    hsm_hdl_t hsm_session_hdl = 0;
    hsm_hdl_t key_store_hdl   = 0;
    hsm_hdl_t key_mgmt_hdl    = 0;
    bool ele_service_ready    = false;

private:
    hsm_err_t DeleteKeyInternal(uint32_t keyId, hsm_op_delete_key_flags_t flags, const char * logSuffix);
};

class EleManagerKeystore : public EleManagerImpl
{
private:
    EleManagerKeystore();
    virtual ~EleManagerKeystore();

    EleManagerKeystore(const EleManagerKeystore &)             = delete;
    EleManagerKeystore & operator=(const EleManagerKeystore &) = delete;

    /* ELE does not allow multiple channels with same keyID, so I have to use a smart pointer
     * to manage ELE project here to make sure the ELE channel with kKeyStoreId = 0xAAAA be
     * opened only once */
    static std::weak_ptr<EleManagerKeystore> mWeakInstance;

public:
    static std::shared_ptr<EleManagerKeystore> getInstance();

    /* Unique keyID to open the key store channel in ELE HSM */
    static constexpr uint32_t kKeyStoreId  = 0xAAAA;
    static constexpr uint32_t kAuthenNonce = 0x1111;

    /* keyId of the pending operational keypair (RAM working copy). It is also persisted in a reserved
     * slot of the mapping table, because the key is created PERSISTENT in the shared key group and a
     * commit for another fabric can sync it to NVM; the persisted copy lets ReconcilePendingKey()
     * reclaim it after a power loss before commit/revert. 0 means no pending key. */
    uint32_t mPendingKeyId = 0;

    /* Generic data storage in ELE NVM, used to persist the fabricIndex->keyId table alongside the
     * keys themselves, so the mapping shares the keys' lifetime and cannot be lost independently.
     * Data storage writes are always persisted to NVM by the HSM without a SYNC flag. */
    hsm_hdl_t data_storage_hdl = 0;
    hsm_err_t EleStoreData(uint32_t dataId, const uint8_t * data, size_t dataSize);
    hsm_err_t EleRetrieveData(uint32_t dataId, uint8_t * data, size_t & dataSize);
    hsm_err_t EleDeleteData(uint32_t dataId);

    /* On startup, reclaim a pending key orphaned by a power loss before commit/revert (see
     * mPendingKeyId). Implemented in PersistentStorageOperationalKeystoreEle.cpp with the mapping
     * table helpers. Best-effort. */
    void ReconcilePendingKey();
};

class EleManagerAttestation : public EleManagerImpl
{
private:
    EleManagerAttestation();
    virtual ~EleManagerAttestation();

    EleManagerAttestation(const EleManagerAttestation &)             = delete;
    EleManagerAttestation & operator=(const EleManagerAttestation &) = delete;

    /* ELE does not allow multiple channels with same keyID, so I have to use a smart pointer
     * to manage ELE project here to make sure the ELE channel with kKeyStoreId = 0xBBBB be
     * opened only once */
    static std::weak_ptr<EleManagerAttestation> mWeakInstance;

public:
    static std::shared_ptr<EleManagerAttestation> getInstance();

    /* Unique keyID to open the key store channel in ELE HSM */
    static constexpr uint32_t kKeyStoreId  = 0xBBBB;
    static constexpr uint32_t kAuthenNonce = 0x2222;
};

} // namespace ele
} // namespace Credentials
} // namespace chip
