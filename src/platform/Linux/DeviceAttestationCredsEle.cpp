/*
 *
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
#include "DeviceAttestationCredsEle.h"

#include <crypto/CHIPCryptoPAL.h>
#include <lib/core/CHIPError.h>
#include <lib/support/Span.h>

#define PAI_DATA_ID 0x1111
#define DAC_DATA_ID 0x1112
#define CD_DATA_ID  0x1113
#define DAC_PRIVATE_KEY_ID 0x1114

namespace chip {
namespace Credentials {
namespace ele {

CHIP_ERROR EleDACProvider::GetDeviceAttestationCert(MutableByteSpan & out_dac_buffer)
{
    op_data_storage_args_t data_storage_args = {0};
    hsm_err_t err;

    data_storage_args.svc_flags = 0;
    data_storage_args.data = out_dac_buffer.data();
    data_storage_args.data_size = out_dac_buffer.size();
    data_storage_args.data_id = DAC_DATA_ID;
    data_storage_args.flags = HSM_OP_DATA_STORAGE_FLAGS_RETRIEVE;
    err = hsm_data_ops(EleManager->key_store_hdl, &data_storage_args);
    if (err) {
        ChipLogDetail(Crypto, "ELE get DAC failed. ret: 0x%x\n", err);
        return CHIP_ERROR_CERT_LOAD_FAILED;
    }

    out_dac_buffer.reduce_size(data_storage_args.exp_output_size);
    return CHIP_NO_ERROR;
}

CHIP_ERROR EleDACProvider::GetProductAttestationIntermediateCert(MutableByteSpan & out_pai_buffer)
{
    op_data_storage_args_t data_storage_args = {0};
    hsm_err_t err;

    data_storage_args.svc_flags = 0;
    data_storage_args.data = out_pai_buffer.data();
    data_storage_args.data_size = out_pai_buffer.size();
    data_storage_args.data_id = PAI_DATA_ID;
    data_storage_args.flags = HSM_OP_DATA_STORAGE_FLAGS_RETRIEVE;
    err = hsm_data_ops(EleManager->key_store_hdl, &data_storage_args);
    if (err) {
        ChipLogDetail(Crypto, "ELE get PAI failed. ret: 0x%x\n", err);
        return CHIP_ERROR_CERT_LOAD_FAILED;
    }

    out_pai_buffer.reduce_size(data_storage_args.exp_output_size);
    return CHIP_NO_ERROR;
}

CHIP_ERROR EleDACProvider::GetCertificationDeclaration(MutableByteSpan & out_cd_buffer)
{
    op_data_storage_args_t data_storage_args = {0};
    hsm_err_t err;

    data_storage_args.svc_flags = 0;
    data_storage_args.data = out_cd_buffer.data();
    data_storage_args.data_size = out_cd_buffer.size();
    data_storage_args.data_id = CD_DATA_ID;
    data_storage_args.flags = HSM_OP_DATA_STORAGE_FLAGS_RETRIEVE;
    err = hsm_data_ops(EleManager->key_store_hdl, &data_storage_args);
    if (err) {
        ChipLogDetail(Crypto, "ELE get CD failed. ret: 0x%x\n", err);
        return CHIP_ERROR_CERT_LOAD_FAILED;
    }

    out_cd_buffer.reduce_size(data_storage_args.exp_output_size);
    return CHIP_NO_ERROR;
}

CHIP_ERROR EleDACProvider::GetFirmwareInformation(MutableByteSpan & out_firmware_info_buffer)
{
    // TODO: We need a real example FirmwareInformation to be populated.
    out_firmware_info_buffer.reduce_size(0);

    return CHIP_NO_ERROR;
}

CHIP_ERROR EleDACProvider::SignWithDeviceAttestationKey(const ByteSpan & message_to_sign,
                                                            MutableByteSpan & out_signature_buffer)
{
    open_svc_sign_gen_args_t open_sig_gen_args;
    op_generate_sign_args_t sig_gen_args;
    uint8_t signature[64];
    hsm_hdl_t  sig_gen_hdl;
    size_t out_size = 0;
    hsm_err_t hsmret;

    VerifyOrReturnError(IsSpanUsable(out_signature_buffer), CHIP_ERROR_INVALID_ARGUMENT);
    VerifyOrReturnError(IsSpanUsable(message_to_sign), CHIP_ERROR_INVALID_ARGUMENT);
    VerifyOrReturnError(out_signature_buffer.size() >= sizeof(signature), CHIP_ERROR_BUFFER_TOO_SMALL);

    // open signature generation service
    memset(&open_sig_gen_args, 0, sizeof(open_sig_gen_args));
    hsmret = hsm_open_signature_generation_service(EleManager->key_store_hdl, &open_sig_gen_args, &sig_gen_hdl);
    if (hsmret != HSM_NO_ERROR) {
        ChipLogDetail(Crypto, "open signature generation service failed. ret:0x%x\n", hsmret);
        return CHIP_ERROR_HSM;
    }

    // generate signature
    memset(&sig_gen_args, 0, sizeof(sig_gen_args));
    sig_gen_args.key_identifier = DAC_PRIVATE_KEY_ID;
    sig_gen_args.scheme_id = HSM_SIGNATURE_SCHEME_ECDSA_SHA256;
    sig_gen_args.message = (uint8_t *)(message_to_sign.data());
    sig_gen_args.signature = signature;
    sig_gen_args.message_size = message_to_sign.size();
    sig_gen_args.signature_size = sizeof(signature);
    sig_gen_args.flags = HSM_OP_GENERATE_SIGN_FLAGS_INPUT_MESSAGE;
    hsmret = hsm_generate_signature(sig_gen_hdl, &sig_gen_args);
    hsm_close_signature_generation_service(sig_gen_hdl);
    if (hsmret != HSM_NO_ERROR) {
        ChipLogDetail(Crypto, "generate signature failed. ret:0x%x\n", hsmret);
        return CHIP_ERROR_HSM;
    }

    memcpy(out_signature_buffer.data(), signature, sizeof(signature));
    out_signature_buffer.reduce_size(sizeof(signature));
    return CHIP_NO_ERROR;
}

EleDACProvider & EleDACProvider::GetEleDACProvider()
{
    static EleDACProvider ele_dac_provider;

    return ele_dac_provider;
}

} // namespace ele
} // namespace Credentials
} // namespace chip

