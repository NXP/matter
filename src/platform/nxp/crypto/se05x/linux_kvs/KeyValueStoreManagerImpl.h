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
 *          Platform-specific implementation of KVS for SE05x + Linux.
 */

#pragma once

#include "CHIPCryptoPALHsm_se05x_readClusters.h"
#include "CHIPCryptoPALHsm_se05x_utils.h"
#include <lib/core/TLV.h>
#include <lib/core/TLVUtilities.h>
#include <lib/support/Base64.h>
#include <platform/Linux/CHIPLinuxStorage.h>
#include <unistd.h>
#include <vector>

namespace chip {
namespace DeviceLayer {
namespace PersistedStorage {

class KeyValueStoreManagerImpl : public KeyValueStoreManager
{
public:
    /**
     * @brief
     * Initialize the KVS, must be called before using.
     */
    CHIP_ERROR Init(const char * file)
    {
        ChipLogDetail(Crypto, "SE05x :: KVS Initialization");

        // Reset breadcrumb and commissioning state
        ReturnErrorOnFailure(se05x_reset_breadcrumb());
        ReturnErrorOnFailure(se05x_reset_iscomm_without_power(false));

        // Check if NFC commissioning was performed
        if (se05x_is_nfc_commissioning_done() != CHIP_NO_ERROR)
        {
            ChipLogDetail(Crypto, "SE05x :: No NFC commissioned data found");
            ReturnErrorOnFailure(se05x_close_session());
            return mStorage.Init(file);
        }

        ChipLogDetail(Crypto, "SE05x :: NFC commissioned data found. Reading contents from SE05x");

        // Disable NFC commissioning after successful detection
        ReturnErrorOnFailure(se05x_disable_nfc_commision());

        // Initialize storage
        ReturnErrorOnFailure(mStorage.Init(file));

        // Check if KVS is already synchronized with SE05x
        if (IsKVSAlreadySynchronized())
        {
            ChipLogDetail(Crypto, "SE05x :: KVS is already updated with SE contents. Skipping synchronization.");
            return CHIP_NO_ERROR;
        }

        // Mark that we're reading from SE05x for fail-safe timer handling
        se05x_read_fail_safe = 1;

        // Synchronize all credentials from SE05x to KVS
        ReturnErrorOnFailure(SynchronizeOperationalCredentials());
        ReturnErrorOnFailure(SynchronizeNetworkCredentials());

        ChipLogDetail(Crypto, "SE05x :: Successfully synchronized all credentials to KVS");
        return CHIP_NO_ERROR;
    }

    uint32_t GetRemainingFailSafeTimerForSE05x()
    {
        // If not reading from SE05x for the first time after NFC commissioning, return 0
        if (se05x_read_fail_safe == 0)
        {
            ChipLogDetail(Crypto, "SE05x: Fail-safe timer not active (not first read after NFC commissioning)");
            return 0;
        }

        uint16_t fail_safe_time = 0;
        CHIP_ERROR status       = se05x_get_remain_fail_safe_time(&fail_safe_time);

        if (status != CHIP_NO_ERROR)
        {
            ChipLogError(Crypto, "SE05x: Failed to read fail-safe time from secure element (error: %" CHIP_ERROR_FORMAT ")",
                         status.Format());
            // Reset the flag since we attempted to read
            se05x_read_fail_safe = 0;
            return 0;
        }

        // Reset the flag after successful read
        se05x_read_fail_safe = 0;

        // TODO: Remove hardcoded value
        // Currently returning 120 seconds as a workaround for applet limitation
        constexpr uint32_t kDefaultFailSafeTimeSeconds = 120;

        ChipLogDetail(Crypto, "SE05x: Fail-safe time read from SE: %u seconds, returning: %u seconds (hardcoded)", fail_safe_time,
                      kDefaultFailSafeTimeSeconds);

        return kDefaultFailSafeTimeSeconds;
    }

    /**
     * @brief Register NFC commissioning completion callback thread
     * @param argv Arguments to pass to the callback thread
     * @return CHIP_NO_ERROR on success, appropriate error code on failure
     */
    CHIP_ERROR RegisterNfcCommCompleteCallback(char * const * argv)
    {
        pthread_t tid;
        pthread_attr_t attr;

        // Initialize thread attributes
        int result = pthread_attr_init(&attr);
        if (result != 0)
        {
            ChipLogError(NotSpecified, "Failed to initialize thread attributes: %d", result);
            return CHIP_ERROR_INTERNAL;
        }

        // Set thread to detached state
        result = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        if (result != 0)
        {
            ChipLogError(NotSpecified, "Failed to set thread detach state: %d", result);
            if (pthread_attr_destroy(&attr) != 0)
            {
                ChipLogError(NotSpecified, "Failed to destroy thread attributes during cleanup");
            }
            return CHIP_ERROR_INTERNAL;
        }

        // Create the callback thread
        result = pthread_create(&tid, &attr, se05x_host_gpio_notification_monitor_init, (void *) argv);
        if (result != 0)
        {
            ChipLogError(NotSpecified, "Failed to create NFC callback thread: %d", result);
            if (pthread_attr_destroy(&attr) != 0)
            {
                ChipLogError(NotSpecified, "Failed to destroy thread attributes during cleanup");
            }
            return CHIP_ERROR_INTERNAL;
        }

        // Clean up thread attributes
        if (pthread_attr_destroy(&attr) != 0)
        {
            ChipLogError(NotSpecified, "Failed to destroy thread attributes");
        }

        ChipLogProgress(NotSpecified, "NFC callback thread registered successfully (TID: %lu)", (unsigned long) tid);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR _Get(const char * key, void * value, size_t value_size, size_t * read_bytes_size = nullptr, size_t offset = 0);
    CHIP_ERROR _Delete(const char * key);
    CHIP_ERROR _Put(const char * key, const void * value, size_t value_size);

    inline static uint32_t se05x_read_fail_safe;

private:
    /**
     * @brief Check if KVS already contains synchronized SE05x data
     * @return true if KVS is synchronized, false otherwise
     */
    bool IsKVSAlreadySynchronized()
    {
        constexpr size_t kMaxKeySize     = 32;
        constexpr size_t kMaxOperKeySize = 256;

        char kvs_key_name[kMaxKeySize];
        uint8_t kvs_node_oper_key[kMaxOperKeySize] = { 0 };
        uint8_t se_node_oper_key[kMaxOperKeySize]  = { 0 };
        size_t kvs_key_len                         = sizeof(kvs_node_oper_key);
        size_t se_key_len                          = sizeof(se_node_oper_key);

        // Build key name for operational keypair
        VerifyOrReturnValue(snprintf(kvs_key_name, sizeof(kvs_key_name), "f/%x/o", 1) > 0, false);

        // Try to read operational key from KVS
        CHIP_ERROR status = _Get(kvs_key_name, kvs_node_oper_key, sizeof(kvs_node_oper_key), &kvs_key_len, 0);
        VerifyOrReturnValue(status == CHIP_NO_ERROR, false);

        // Read operational key from SE05x
        status = se05x_read_node_operational_keypair(se_node_oper_key, &se_key_len);
        VerifyOrReturnValue(status == CHIP_NO_ERROR, false);

        // Compare keys - if identical, KVS is already synchronized
        return (kvs_key_len == se_key_len) && (memcmp(kvs_node_oper_key, se_node_oper_key, kvs_key_len) == 0);
    }

    /**
     * @brief Synchronize operational credentials from SE05x to KVS
     */
    CHIP_ERROR SynchronizeOperationalCredentials()
    {
        constexpr size_t kMaxBufferSize  = (2 * chip::Credentials::kMaxCHIPCertLength) + 32;
        constexpr size_t kMaxKeyNameSize = 32;

        uint8_t buffer[kMaxBufferSize] = { 0 };
        char key_name[kMaxKeyNameSize] = { 0 };
        size_t buffer_len;

        // Read and store operational keypair
        buffer_len = sizeof(buffer);
        ReturnErrorOnFailure(se05x_read_node_operational_keypair(buffer, &buffer_len));
        VerifyOrReturnError(snprintf(key_name, sizeof(key_name), "f/%x/o", 1) > 0, CHIP_ERROR_INTERNAL);
        ReturnErrorOnFailure(_Put(key_name, buffer, buffer_len));

        // Read and store Node Operational Certificate (NOC)
        buffer_len = sizeof(buffer);
        ReturnErrorOnFailure(se05x_read_node_oper_cert(buffer, &buffer_len));
        VerifyOrReturnError(snprintf(key_name, sizeof(key_name), "f/%" PRIx32 "/n", 1) > 0, CHIP_ERROR_INTERNAL);
        ReturnErrorOnFailure(_Put(key_name, buffer, buffer_len));

        const uint32_t fabric_id = se05x_get_fabric_id();

        // Read and store Root Certificate
        buffer_len = sizeof(buffer);
        ReturnErrorOnFailure(se05x_read_root_cert(buffer, &buffer_len));
        VerifyOrReturnError(snprintf(key_name, sizeof(key_name), "f/%" PRIx32 "/r", fabric_id) > 0, CHIP_ERROR_INTERNAL);
        ReturnErrorOnFailure(_Put(key_name, buffer, buffer_len));

        // Read and store Intermediate CA Certificate (if present)
        buffer_len = sizeof(buffer);
        ReturnErrorOnFailure(se05x_read_ICA(buffer, &buffer_len));
        if (buffer_len > 0)
        {
            VerifyOrReturnError(snprintf(key_name, sizeof(key_name), "f/%x/i", fabric_id) > 0, CHIP_ERROR_INTERNAL);
            ReturnErrorOnFailure(_Put(key_name, buffer, buffer_len));
        }

        // Read and store Identity Protection Key (IPK)
        buffer_len = sizeof(buffer);
        ReturnErrorOnFailure(se05x_read_ipk(buffer, &buffer_len));
        VerifyOrReturnError(snprintf(key_name, sizeof(key_name), "f/%" PRIx32 "/k/0", fabric_id) > 0, CHIP_ERROR_INTERNAL);
        ReturnErrorOnFailure(_Put(key_name, buffer, buffer_len));

        // Read and store Access Control List (ACL)
        buffer_len = sizeof(buffer);
        ReturnErrorOnFailure(se05x_read_acl_data(buffer, &buffer_len));
        VerifyOrReturnError(snprintf(key_name, sizeof(key_name), "f/%" PRIx32 "/ac/0/0", fabric_id) > 0, CHIP_ERROR_INTERNAL);
        ReturnErrorOnFailure(_Put(key_name, buffer, buffer_len));

        // Read and store fabric groups
        buffer_len = sizeof(buffer);
        ReturnErrorOnFailure(se05x_read_fabric_groups(buffer, &buffer_len));
        VerifyOrReturnError(snprintf(key_name, sizeof(key_name), "f/%" PRIx32 "/g", fabric_id) > 0, CHIP_ERROR_INTERNAL);
        ReturnErrorOnFailure(_Put(key_name, buffer, buffer_len));

        // Read and store metadata
        buffer_len = sizeof(buffer);
        ReturnErrorOnFailure(se05x_read_meta_data(buffer, &buffer_len));
        VerifyOrReturnError(snprintf(key_name, sizeof(key_name), "f/%" PRIx32 "/m", fabric_id) > 0, CHIP_ERROR_INTERNAL);
        ReturnErrorOnFailure(_Put(key_name, buffer, buffer_len));

        // Read and store fabric index info
        buffer_len = sizeof(buffer);
        ReturnErrorOnFailure(se05x_read_fabric_index_info_data(buffer, &buffer_len));
        ReturnErrorOnFailure(_Put("g/fidx", buffer, buffer_len));

        return CHIP_NO_ERROR;
    }

    /**
     * @brief Synchronize network credentials from SE05x to KVS
     */
    CHIP_ERROR SynchronizeNetworkCredentials()
    {
        constexpr size_t kMaxBufferSize = 512;

        uint8_t buffer[kMaxBufferSize];
        char password[DeviceLayer::Internal::kMaxWiFiKeyLength] = { 0 };
        char op_data_set[256]                                   = { 0 };
        size_t ssid_len                                         = sizeof(op_data_set);
        size_t password_len                                     = sizeof(password);
        size_t op_data_set_len                                  = sizeof(op_data_set);
        uint32_t network_cred_id                                = 0;

        // Get network credential ID from network commissioning cluster
        ReturnErrorOnFailure(se05x_net_id_from_net_comm_cluster(&network_cred_id));

        // Read WiFi/Thread credentials
        CHIP_ERROR status = se05x_read_wifi_and_thread_credentials(buffer, sizeof(buffer), op_data_set, &ssid_len, password, &password_len,
                                                                   op_data_set, &op_data_set_len, &network_cred_id);

        if (status != CHIP_NO_ERROR)
        {
            ChipLogDetail(Crypto, "SE05x: Reading network credentials from secure element failed");
            return CHIP_NO_ERROR; // Non-fatal - continue without network credentials
        }

        // Store WiFi credentials if present
        if (ssid_len > 0 && password_len > 0)
        {
            ChipLogDetail(Crypto, "SE05x: Setting Wi-Fi credentials");
            ReturnErrorOnFailure(_Put("wifi-ssid", op_data_set, ssid_len));
            ReturnErrorOnFailure(_Put("wifi-pass", password, password_len));
        }
        // Store Thread credentials if available
        else if (op_data_set_len > 0)
        {
#if CHIP_DEVICE_CONFIG_ENABLE_THREAD
            ChipLogDetail(Crypto, "SE05x: Setting Thread operational data");
            ByteSpan dataset(reinterpret_cast<const uint8_t *>(op_data_set), op_data_set_len);
            DeviceLayer::ThreadStackMgrImpl().SetThreadProvision(dataset);
#else
            ChipLogDetail(Crypto, "SE05x: SE05x commissioned for Thread, but example is not built with Thread support");
#endif
        }
        else
        {
            ChipLogDetail(Crypto, "SE05x: No valid network credentials found");
        }

        return CHIP_NO_ERROR;
    }

    DeviceLayer::Internal::ChipLinuxStorage mStorage;

    // ===== Members for internal use by the following friends.
    friend KeyValueStoreManager & KeyValueStoreMgr();
    friend KeyValueStoreManagerImpl & KeyValueStoreMgrImpl();

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
