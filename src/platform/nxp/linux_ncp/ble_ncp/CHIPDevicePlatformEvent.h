/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


/**
 * Defines platform-specific event types and data for the chip Device Layer on NCP platforms.
 */

#pragma once

#include <platform/CHIPDeviceEvent.h>
#include <system/SystemPacketBuffer.h>

namespace chip {
namespace DeviceLayer {

namespace DeviceEventType {

} // namespace DeviceEventType

struct BleConnEventType
{
    uint16_t BtConn;
    uint8_t HciResult;
};

struct BleCCCWriteEventType
{
    uint16_t BtConn;
    uint16_t Value;
};

struct BleC1WriteEventType
{
    uint16_t BtConn;
    ::chip::System::PacketBuffer * Data;
};

struct BleC2IndDoneEventType
{
    uint16_t BtConn;
    uint8_t Result;
};

/**
 * Represents platform-specific event information for Zephyr platforms.
 */
struct ChipDevicePlatformEvent final
{
    union
    {
        BleConnEventType BleConnEvent;
        BleCCCWriteEventType BleCCCWriteEvent;
        BleC1WriteEventType BleC1WriteEvent;
        BleC2IndDoneEventType BleC2IndDoneEvent;
    };
};

} // namespace DeviceLayer
} // namespace chip
