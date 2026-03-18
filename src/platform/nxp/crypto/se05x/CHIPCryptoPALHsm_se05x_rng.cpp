/*
 *
 *    Copyright (c) 2021, 2025 Project CHIP Authors
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
 *      HSM based implementation of CHIP crypto primitives
 *      Based on configurations in CHIPCryptoPALHsm_config.h file,
 *      chip crypto apis use either HSM or rollback to software implementation.
 */

#include "CHIPCryptoPALHsm_se05x_utils.h"
#include <lib/core/CHIPEncoding.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>

namespace chip {
namespace Crypto {

#if ENABLE_SE05X_RND_GEN

#if !CHIP_SYSTEM_CONFIG_NO_LOCKING
using namespace chip::System;
static Mutex se05x_rng_crypto_mutex;
#define LOCK_RNG_CRYPTO_MUTEX()                                                                                                    \
    do                                                                                                                             \
    {                                                                                                                              \
        se05x_rng_crypto_mutex.Lock();                                                                                             \
    } while (0);
#define UNLOCK_RNG_CRYPTO_MUTEX()                                                                                                  \
    do                                                                                                                             \
    {                                                                                                                              \
        se05x_rng_crypto_mutex.Unlock();                                                                                           \
    } while (0);

#else
#define LOCK_RNG_CRYPTO_MUTEX()
#define UNLOCK_RNG_CRYPTO_MUTEX()
#endif // !CHIP_SYSTEM_CONFIG_NO_LOCKING

CHIP_ERROR DRBG_get_bytes(uint8_t * out_buffer, const size_t out_length)
{
    sss_status_t status;
    sss_rng_context_t ctx_rng = { 0 };

    VerifyOrReturnError(out_buffer != nullptr, CHIP_ERROR_INVALID_ARGUMENT);
    VerifyOrReturnError(out_length > 0, CHIP_ERROR_INVALID_ARGUMENT);

    ChipLogDetail(Crypto, "se05x::Random number generation using se05x");

    LOCK_RNG_CRYPTO_MUTEX();

    if (se05x_session_open() != CHIP_NO_ERROR)
    {
        UNLOCK_RNG_CRYPTO_MUTEX();
        return CHIP_ERROR_INTERNAL;
    }

    status = sss_rng_context_init(&ctx_rng, &gex_sss_chip_ctx.session /* Session */);
    if (status != kStatus_SSS_Success)
    {
        UNLOCK_RNG_CRYPTO_MUTEX();
        return CHIP_ERROR_INTERNAL;
    }

    status = sss_rng_get_random(&ctx_rng, out_buffer, out_length);
    if (status != kStatus_SSS_Success)
    {
        UNLOCK_RNG_CRYPTO_MUTEX();
        return CHIP_ERROR_INTERNAL;
    }

    sss_rng_context_free(&ctx_rng);

    UNLOCK_RNG_CRYPTO_MUTEX();
    return CHIP_NO_ERROR;
}

#endif

} // namespace Crypto
} // namespace chip
