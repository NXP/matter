/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
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

#include "Se05xDataProvider.h"
#include <credentials/CHIPCert.h>
#include <credentials/DeviceAttestationCredsProvider.h>
#include <crypto/CHIPCryptoPAL.h>
#include <lib/core/CHIPError.h>
#include <lib/core/TLV.h>
#include <lib/support/Base64.h>
#include <lib/support/SafeInt.h>
#include <lib/support/Span.h>
#include <platform/ConfigurationManager.h>
#include <platform/nxp/crypto/se05x/CHIPCryptoPALHsm_se05x_utils.h>

#include <cctype>

using namespace chip::DeviceLayer::PersistedStorage;

namespace chip {
namespace DeviceLayer {

static Se05xDataProviderImpl sInstance;
static constexpr size_t kSpake2pSalt_MaxBase64Len = BASE64_ENCODED_LEN(chip::Crypto::kSpake2p_Max_PBKDF_Salt_Length) + 1;

constexpr size_t kSpake2p_PBKDF_Salt_Length_SE05x = 32;
constexpr size_t kSpake2p_Passcode_Length_SE05x   = 4;
constexpr uint32_t kSpake2p_Pwd_Salt_Bin_File_id  = 0x7FFF2000;
uint32_t setUpPINCode_se05x                       = 0;

#define BCD_TO_DEC(x) (x - 6 * (x >> 4))

CHIP_ERROR GeneratePaseSaltSe05x(char * buf, uint16_t bufLen, uint16_t * outLen)
{
    CHIP_ERROR err            = CHIP_NO_ERROR;
    constexpr size_t kSaltLen = kSpake2p_PBKDF_Salt_Length_SE05x;
    uint8_t cert[128]         = {
        0,
    };
    size_t certLen = sizeof(cert);
    /* 3 set of verifiers are provisioned in se05x. Each with 4 bytes passcode and 32 bytes salt */
    uint8_t offset = (SE05X_SPAKE_VERIFIER_TP_SET_NO - 1) * (kSpake2p_PBKDF_Salt_Length_SE05x + kSpake2p_Passcode_Length_SE05x);

    err = se05x_get_certificate(kSpake2p_Pwd_Salt_Bin_File_id, cert, &certLen);
    VerifyOrReturnError(err == CHIP_NO_ERROR, err);

    // To ensure we turn off the gpio and be ready for NFC comm
    VerifyOrReturnError(se05x_close_session() == CHIP_NO_ERROR, CHIP_ERROR_INTERNAL);

    VerifyOrReturnError(certLen >= (offset + kSpake2p_PBKDF_Salt_Length_SE05x + kSpake2p_Passcode_Length_SE05x),
                        CHIP_ERROR_INTERNAL);

    VerifyOrReturnError(bufLen >= kSaltLen, CHIP_ERROR_INTERNAL);
    memcpy(buf, cert + offset + kSpake2p_Passcode_Length_SE05x, kSaltLen);
    *outLen            = kSaltLen;
    setUpPINCode_se05x = (BCD_TO_DEC(cert[offset + 3])) + (100 * BCD_TO_DEC(cert[offset + 2])) +
        (10000 * BCD_TO_DEC(cert[offset + 1])) + (1000000 * BCD_TO_DEC(cert[offset]));

    return CHIP_NO_ERROR;
}

CHIP_ERROR Se05xDataProviderImpl::GetSpake2pSalt(MutableByteSpan & saltBuf)
{

    CHIP_ERROR err                          = CHIP_NO_ERROR;
    char saltB64[kSpake2pSalt_MaxBase64Len] = { 0 };
    uint16_t saltB64Len                     = 0;
    err                                     = GeneratePaseSaltSe05x(saltB64, sizeof(saltB64), &saltB64Len);
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(Support, "Failed to generate PASE salt: %" CHIP_ERROR_FORMAT, err.Format());
        return err;
    }
    VerifyOrReturnError(saltB64Len <= saltBuf.size(), CHIP_ERROR_BUFFER_TOO_SMALL);
    memcpy(saltBuf.data(), saltB64, saltB64Len);
    saltBuf.reduce_size(saltB64Len);
    return err;
}

CHIP_ERROR Se05xDataProviderImpl::GetSetupPasscode(uint32_t & setupPasscode)
{
    CHIP_ERROR err                          = CHIP_NO_ERROR;
    char saltB64[kSpake2pSalt_MaxBase64Len] = { 0 };
    uint16_t saltB64Len                     = 0;
    err                                     = GeneratePaseSaltSe05x(saltB64, sizeof(saltB64), &saltB64Len);
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(Support, "Failed to generate PASE salt: %" CHIP_ERROR_FORMAT, err.Format());
        return err;
    }
    setupPasscode = setUpPINCode_se05x;
    return err;
}

CHIP_ERROR Se05xDataProviderImpl::GetSpake2pIterationCount(uint32_t & iterationCount)
{
    iterationCount = SE05X_SPAKE_VERIFIER_TP_ITTER_CNT;
    return CHIP_NO_ERROR;
}

CHIP_ERROR Se05xDataProviderImpl::GetSpake2pVerifier(MutableByteSpan & verifierBuf, size_t & verifierLen)
{
    char verifierB64[kSpake2pSerializedVerifier_MaxBase64Len] = { 0 };
    uint16_t verifierB64Len                                   = 0;
    ReturnErrorOnFailure(SearchForId(FactoryDataId::kVerifierId, (uint8_t *) &verifierB64[0], sizeof(verifierB64), verifierB64Len));

    verifierLen = chip::Base64Decode32(verifierB64, verifierB64Len, reinterpret_cast<uint8_t *>(verifierB64));
    VerifyOrReturnError(verifierLen <= verifierBuf.size(), CHIP_ERROR_BUFFER_TOO_SMALL);
    // Set verifier buffer to zero - the actual verifier remains in SE05x secure element
    memset(verifierBuf.data(), 0, verifierLen);
    verifierBuf.reduce_size(verifierLen);

    return CHIP_NO_ERROR;
}

Se05xDataProviderImpl & Se05xDataPrvdImpl()
{
    return sInstance;
}

} // namespace DeviceLayer
} // namespace chip
