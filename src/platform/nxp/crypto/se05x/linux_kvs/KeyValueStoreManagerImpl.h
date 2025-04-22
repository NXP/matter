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
 *          Platform-specific implementation of KVS for linux.
 */

#pragma once

#include <platform/Linux/CHIPLinuxStorage.h>
#include <lib/support/Base64.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <array>

#define NXP_CRYPTO_KEY_MAGIC                            \
    {                                                   \
        0xA5, 0xA6, 0xB5, 0xB6, 0xA5, 0xA6, 0xB5, 0xB6  \
    }
#define NIST256_HEADER_OFFSET 26
#define PUB_KEY_LEN           65

extern CHIP_ERROR Se05xCheckObjectExists(uint32_t keyId);
extern CHIP_ERROR se05xGetCertificate(uint32_t keyId, uint8_t * buf, size_t * buflen);


namespace chip {
namespace DeviceLayer {
namespace PersistedStorage {

class KeyValueStoreManagerImpl : public KeyValueStoreManager
{
public:
    /**
     * @brief
     * Initalize the KVS, must be called before using.
     */

    static CHIP_ERROR CreateSe05xRefKey(const uint8_t * pubKeyBuf, size_t  pubKeyBufLen, uint32_t keyId, uint8_t * outBuf, size_t * outLen) {

        const uint8_t header[] = { 0x15, 0x24, 0x00, 0x01, 0x30, 0x01, 0x61 };
        const uint8_t se05x_magic_no[] = NXP_CRYPTO_KEY_MAGIC;
        size_t offset = 0;

        memcpy(&outBuf[offset], header, sizeof(header));
        offset += sizeof(header);

        memcpy(&outBuf[offset], pubKeyBuf + 16, pubKeyBufLen - NIST256_HEADER_OFFSET);
        offset += PUB_KEY_LEN;

        memcpy(&outBuf[offset], se05x_magic_no, sizeof(se05x_magic_no));
        offset += sizeof(se05x_magic_no);

        uint8_t keyIdBytes[] = {
           static_cast<uint8_t>((keyId >> 24) & 0xFF),
           static_cast<uint8_t>((keyId >> 16) & 0xFF),
           static_cast<uint8_t>((keyId >> 8) & 0xFF),
           static_cast<uint8_t>(keyId & 0xFF)
        };

        memcpy(&outBuf[offset], keyIdBytes, sizeof(keyIdBytes));
        offset += sizeof(keyIdBytes);

        memset(&outBuf[offset], 0x00, 20);
        offset += 20;

        outBuf[offset++] = 0x18;
        *outLen = offset;

        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Init(const char *file) {

       printf("********************** KVS Init ***************************\n");

        if (access(file, F_OK) == 0) {
            if (remove(file) != 0) {
                return CHIP_ERROR_INTERNAL;
            }
        }

        CHIP_ERROR fCreate = mStorage.Init(file);
        if (fCreate != CHIP_NO_ERROR) {
            return fCreate;
        }

        std::vector<std::pair<uint32_t, std::string>> keyIdList = {
            {0x7D300013, "f/1/ac/0/0"},
            {0x7D300014, "f/1/g"},
            {0x7D300015, "f/1/i"},
            {0x7D300016, "f/1/k/0"},
            {0x7D300017, "f/1/m"},
            {0x7D300018, "f/1/n"},
            {0x7D300019, "f/1/o"},
            {0x7D300020, "f/1/r"},
            {0x7D300021, "f/1/s/000000000001B669"},
            {0x7D300022, "g/fidx"},
            {0x7D300023, "g/s/pk6lqwxDedYkcy9ukRIuCwx3dx3d"}};

        for(const auto &pair : keyIdList) {

            CHIP_ERROR status = CHIP_NO_ERROR;

            uint32_t keyId = pair.first;
            const std::string& key = pair.second;
            std::vector<uint8_t> certBuf(2000);
            size_t certBufLen = certBuf.size();

            status = Se05xCheckObjectExists(keyId);
            if(status != CHIP_NO_ERROR) {
                printf("Se05x is not NFC commisioned\n");
                break;
            }

            status = se05xGetCertificate(keyId, certBuf.data(), &certBufLen);
            if (status != CHIP_NO_ERROR) {
                printf("se05xGetCertificate failed for Key ID: 0x%X\n", keyId);
                return status;
            }
            if (keyId == 0x7D300019) {
                std::vector<uint8_t> formattedBuf(200);
                size_t formattedBufLen = 0;

                status = CreateSe05xRefKey(certBuf.data(), certBufLen, keyId, formattedBuf.data(), &formattedBufLen);
                if (status != CHIP_NO_ERROR) {
                    printf("CreateRefKey Failed : 0x%X\n", keyId);
                    return status;
                }
                status = _Put(key.c_str(), formattedBuf.data(), formattedBufLen);
                if (status != CHIP_NO_ERROR) {
                    printf("Failed to format the key\n");
                    return status;
                }
            } else {
                status = _Put(key.c_str(), certBuf.data(), certBufLen);
                if (status != CHIP_NO_ERROR) {
                    printf("Failed to store key: %s\n", key.c_str());
                    return status;
                }
            }
        }

        return CHIP_NO_ERROR;
    }

    CHIP_ERROR _Get(const char * key, void * value, size_t value_size, size_t * read_bytes_size = nullptr, size_t offset = 0);
    CHIP_ERROR _Delete(const char * key);
    CHIP_ERROR _Put(const char * key, const void * value, size_t value_size);

private:
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
 * that are specific to the ESP32 platform.
 */
inline KeyValueStoreManagerImpl & KeyValueStoreMgrImpl(void)
{
    return KeyValueStoreManagerImpl::sInstance;
}

} // namespace PersistedStorage
} // namespace DeviceLayer
} // namespace chip
