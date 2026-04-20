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
#pragma once

#if FRDM_RW612
#include <platform/nxp/rt/rw61x/FactoryDataProviderImpl.h>
#else
#include <platform/nxp/rt/rt1060/FactoryDataProviderImpl.h>
#endif
#include <lib/core/CHIPError.h>
#include <lib/support/Span.h>

#include <platform/nxp/crypto/se05x/CHIPCryptoPALHsm_se05x_utils.h>

#include <vector>

namespace chip {
namespace DeviceLayer {

/**
 * @brief This class provides spake salt data, iterations and passcode.
 */

class Se05xDataProviderImpl : public FactoryDataProviderImpl
{
public:
    CHIP_ERROR GetSpake2pSalt(MutableByteSpan & saltBuf) override;
    CHIP_ERROR GetSetupPasscode(uint32_t & setupPasscode) override;
    CHIP_ERROR GetSpake2pIterationCount(uint32_t & iterationCount) override;
    CHIP_ERROR GetSpake2pVerifier(MutableByteSpan & verifierBuf, size_t & verifierLen) override;
};

Se05xDataProviderImpl & Se05xDataPrvdImpl();

} // namespace DeviceLayer
} // namespace chip
