/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
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

/**
 *    @file
 *          Platform-specific key value storage implementation for SE05x with NXP platforms
 */

#pragma once

#include <string>

#include <platform/nxp/crypto/se05x/CHIPCryptoPALHsm_se05x_utils.h>
#include <platform/nxp/crypto/se05x/kvs_utilities/CHIPCryptoPALHsm_se05x_readClusters.h>
#include <credentials/CHIPCert.h>

namespace chip {
namespace DeviceLayer {
namespace PersistedStorage {

class KeyValueStoreManagerImpl final : public KeyValueStoreManager
{
    // Allow the KeyValueStoreManager interface class to delegate method calls to
    // the implementation methods provided by this class.
    friend class KeyValueStoreManager;

public:
    /* To read the provisioning data from se05x and write to the MCU flash */
    CHIP_ERROR Init(void)
    {
        CHIP_ERROR status = CHIP_NO_ERROR;
        // tmp_buffer - Need larger buffer to read node operational certificate chain
        uint8_t tmp_buffer[(2 * chip::Credentials::kMaxCHIPCertLength) + 32];
        size_t tmp_buffer_len                                   = sizeof(tmp_buffer);
        char kvs_key_name[32]                                   = { 0 };
        char ssid[DeviceLayer::Internal::kMaxWiFiSSIDLength]    = { 0 };
        char password[DeviceLayer::Internal::kMaxWiFiKeyLength] = { 0 };
        size_t ssid_len                                         = sizeof(ssid);
        size_t password_len                                     = sizeof(password);

        ChipLogDetail(Crypto, "SE05x :: KVS Initialization ");

        if (se05x_is_nfc_commissioning_done() != CHIP_NO_ERROR)
        {
            ChipLogDetail(Crypto, "SE05x :: No NFC commissioned data found ");
            VerifyOrReturnError(se05x_close_session() == CHIP_NO_ERROR, CHIP_ERROR_INTERNAL);
            return CHIP_NO_ERROR;
        }

        ChipLogDetail(Crypto, "SE05x :: NFC commissioned data found. Reading the contents from SE05x");

        /*  NFC commissioning is done, read the credentials from SE and
            write to chip kvs file.
        */

        status = se05x_read_node_oper_cert(tmp_buffer, &tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, CHIP_ERROR_INTERNAL);

        VerifyOrReturnError(snprintf(kvs_key_name, sizeof(kvs_key_name), "f/%" PRIx32 "/n", se05x_get_fabric_id()) > 0,
                            CHIP_ERROR_INTERNAL);
        status = _Put(kvs_key_name, tmp_buffer, tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, status);

        memset(tmp_buffer, 0, sizeof(tmp_buffer));
        tmp_buffer_len = sizeof(tmp_buffer);
        status         = se05x_read_root_cert(tmp_buffer, &tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, CHIP_ERROR_INTERNAL);

        VerifyOrReturnError(snprintf(kvs_key_name, sizeof(kvs_key_name), "f/%" PRIx32 "/r", se05x_get_fabric_id()) > 0,
                            CHIP_ERROR_INTERNAL);
        status = _Put(kvs_key_name, tmp_buffer, tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, status);

        memset(tmp_buffer, 0, sizeof(tmp_buffer));
        tmp_buffer_len = sizeof(tmp_buffer);
        status         = se05x_read_ICA(tmp_buffer, &tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, CHIP_ERROR_INTERNAL);

        VerifyOrReturnError(snprintf(kvs_key_name, sizeof(kvs_key_name), "f/%" PRIx32 "/i", se05x_get_fabric_id()) > 0,
                            CHIP_ERROR_INTERNAL);
        status = _Put(kvs_key_name, tmp_buffer, tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, status);

        memset(tmp_buffer, 0, sizeof(tmp_buffer));
        tmp_buffer_len = sizeof(tmp_buffer);
        status         = se05x_read_ipk(tmp_buffer, &tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, CHIP_ERROR_INTERNAL);

        VerifyOrReturnError(snprintf(kvs_key_name, sizeof(kvs_key_name), "f/%" PRIx32 "/k/0", se05x_get_fabric_id()) > 0,
                            CHIP_ERROR_INTERNAL);
        status = _Put(kvs_key_name, tmp_buffer, tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, status);

        memset(tmp_buffer, 0, sizeof(tmp_buffer));
        tmp_buffer_len = sizeof(tmp_buffer);
        status         = se05x_read_node_operational_keypair(tmp_buffer, &tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, CHIP_ERROR_INTERNAL);

        VerifyOrReturnError(snprintf(kvs_key_name, sizeof(kvs_key_name), "f/%" PRIx32 "/o", se05x_get_fabric_id()) > 0,
                            CHIP_ERROR_INTERNAL);
        status = _Put(kvs_key_name, tmp_buffer, tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, status);

        memset(tmp_buffer, 0, sizeof(tmp_buffer));
        tmp_buffer_len = sizeof(tmp_buffer);
        status         = se05x_read_acl_data(tmp_buffer, &tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, CHIP_ERROR_INTERNAL);

        VerifyOrReturnError(snprintf(kvs_key_name, sizeof(kvs_key_name), "f/%" PRIx32 "/ac/0/0", se05x_get_fabric_id()) > 0,
                            CHIP_ERROR_INTERNAL);
        status = _Put(kvs_key_name, tmp_buffer, tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, status);

        memset(tmp_buffer, 0, sizeof(tmp_buffer));
        tmp_buffer_len = sizeof(tmp_buffer);
        status         = se05x_read_fabric_groups(tmp_buffer, &tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, CHIP_ERROR_INTERNAL);

        VerifyOrReturnError(snprintf(kvs_key_name, sizeof(kvs_key_name), "f/%" PRIx32 "/g", se05x_get_fabric_id()) > 0,
                            CHIP_ERROR_INTERNAL);
        status = _Put(kvs_key_name, tmp_buffer, tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, status);

        memset(tmp_buffer, 0, sizeof(tmp_buffer));
        tmp_buffer_len = sizeof(tmp_buffer);
        status         = se05x_read_meta_data(tmp_buffer, &tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, CHIP_ERROR_INTERNAL);

        VerifyOrReturnError(snprintf(kvs_key_name, sizeof(kvs_key_name), "f/%" PRIx32 "/m", se05x_get_fabric_id()) > 0,
                            CHIP_ERROR_INTERNAL);
        status = _Put(kvs_key_name, tmp_buffer, tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, status);

        memset(tmp_buffer, 0, sizeof(tmp_buffer));
        tmp_buffer_len = sizeof(tmp_buffer);
        status         = se05x_read_fabric_index_info_data(tmp_buffer, &tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, CHIP_ERROR_INTERNAL);

        status = _Put("g/fidx", tmp_buffer, tmp_buffer_len);
        VerifyOrReturnError(status == CHIP_NO_ERROR, status);

        memset(tmp_buffer, 0, sizeof(tmp_buffer));
        tmp_buffer_len = sizeof(tmp_buffer);
        status         = se05x_read_wifi_credentials(tmp_buffer, tmp_buffer_len, ssid, &ssid_len, password, &password_len);

        if (status == CHIP_NO_ERROR)
        {
            status = _Put("wifi-ssid", ssid, ssid_len);
            VerifyOrReturnError(status == CHIP_NO_ERROR, status);
            status = _Put("wifi-pass", password, password_len);
            VerifyOrReturnError(status == CHIP_NO_ERROR, status);
        }
        else
        {
            ChipLogDetail(Crypto, "SE05x: Reading Wi-Fi credentials from secure element failed");
        }

        return CHIP_NO_ERROR;
    }

    // NOTE: Currently this platform does not support partial and offset reads
    //       these will return CHIP_ERROR_NOT_IMPLEMENTED.
    CHIP_ERROR _Get(const char * key, void * value, size_t value_size, size_t * read_bytes_size, size_t offset);

    CHIP_ERROR _Delete(const char * key);

    CHIP_ERROR _Put(const char * key, const void * value, size_t value_size);

private:
    // ===== Members for internal use by the following friends.
    friend KeyValueStoreManager & KeyValueStoreMgr();
    friend KeyValueStoreManagerImpl & KeyValueStoreMgrImpl();

    // Reading config values uses the NXPConfig API, which returns CHIP_DEVICE_ERROR_CONFIG_NOT_FOUND
    // error if a key was not found. Convert this error to the correct error KeyValueStoreManagerImpl
    // should return: CHIP_ERROR_PERSISTED_STORAGE_VALUE_NOT_FOUND
    void ConvertError(CHIP_ERROR & err);

    static KeyValueStoreManagerImpl sInstance;
};

/**
 * Returns the public interface of the KeyValueStoreManager singleton object.
 *
 * Chip applications should use this to access features of the KeyValueStoreManager object
 * that are common to all platforms.
 */
inline KeyValueStoreManager & KeyValueStoreMgr(void)
{
    return KeyValueStoreManagerImpl::sInstance;
}

/**
 * Returns the platform-specific implementation of the KeyValueStoreManager singleton object.
 *
 * Chip applications can use this to gain access to features of the KeyValueStoreManager
 * that are specific to NXP platforms.
 */
inline KeyValueStoreManagerImpl & KeyValueStoreMgrImpl(void)
{
    return KeyValueStoreManagerImpl::sInstance;
}

} // namespace PersistedStorage
} // namespace DeviceLayer
} // namespace chip
