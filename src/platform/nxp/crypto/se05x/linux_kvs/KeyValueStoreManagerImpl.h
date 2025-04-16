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
    
       std::array<uint32_t, 9> keyIds = {
           0x7D300022, 0x7D300013, 0x7D300014, 0x7D300015,
           0x7D300016, 0x7D300020, 0x7D300017, 0x7D300018, 0x7D300019
       };
       for (uint32_t keyId : keyIds) {
           std::vector<uint8_t> Buf(2000, 0);
           size_t Buf_len = Buf.size();
           std::vector<uint8_t> decodeBuf(2000, 0);
           uint16_t decodeBufLen = 0;
           CHIP_ERROR status = se05xGetCertificate(keyId, Buf.data(), &Buf_len);
           if (status != CHIP_NO_ERROR) {
               printf("se05xGetCertificate failed for Key ID: 0x%X\n", keyId);
               return status;
           }
           size_t start = 0;
           while (start < Buf_len) {
               size_t end = start;
               while (end < Buf_len && Buf[end] != '\n') {
                   end++;
               }
               std::string line(reinterpret_cast<char *>(&Buf[start]), end - start);
               start = end + 1;
               size_t pos = line.find('=');
               if (pos != std::string::npos) {
                   std::string key = line.substr(0, pos);
                   std::string value = line.substr(pos + 1);
                   decodeBufLen = Base64Decode(value.c_str(), value.length(), decodeBuf.data());
                   if (decodeBufLen > 0) {
                       CHIP_ERROR err = _Put(key.c_str(), decodeBuf.data(), decodeBufLen);
                       if (err != CHIP_NO_ERROR) {
                           printf("Failed to store key: %s\n", key.c_str());
                           return err;
                       }
                   } else {
                       printf("Base64 decode failed for key: %s\n", key.c_str());
                   }
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
