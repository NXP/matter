/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2020 Google LLC.
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
 *          Platform-specific configuration overrides for the CHIP System
 *          Layer on NXP MCXW72 Platforms.
 *
 */

#pragma once

#include <stdint.h>

namespace chip {
namespace DeviceLayer {
struct ChipDeviceEvent;
} // namespace DeviceLayer
} // namespace chip

// ==================== Platform Adaptations ====================
#define CHIP_SYSTEM_CONFIG_PLATFORM_PROVIDES_TIME 1
#define CHIP_SYSTEM_CONFIG_EVENT_OBJECT_TYPE const struct ::chip::DeviceLayer::ChipDeviceEvent *
#define CHIP_SYSTEM_CONFIG_PACKETBUFFER_POOL_SIZE 0

// Include default nxp platform configurations
#include "platform/nxp/common/SystemNXPPlatformDefaultConfig.h"
