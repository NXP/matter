/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


namespace chip {
namespace DeviceLayer {

namespace DeviceEventType {
	
enum BLEPlatformSpecificEventTypes
{
    kPlatformZephyrEvent = 0x4000,
    kPlatformZephyrBleConnected,
    kPlatformZephyrBleDisconnected,
    kPlatformZephyrBleCCCWrite,
    kPlatformZephyrBleC1WriteEvent,
    kPlatformZephyrBleC2IndDoneEvent,
    kPlatformZephyrBleOutOfBuffersEvent,

};

} // namespace DeviceEventType

} // namespace DeviceLayer
} // namespace chip