/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


/**
 * Provides an implementation of the BLEManager singleton object for the NCP platforms.
 */

#pragma once

#if CHIP_DEVICE_CONFIG_ENABLE_CHIPOBLE

#include "BlePlatformConfig.h"
#include "BLEAdvertisingArbiter.h"

#include <lib/support/CHIPMemString.h>

namespace chip {
namespace DeviceLayer {
namespace Internal {

using namespace chip::Ble;

/**
 * Concrete implementation of the BLEManager singleton object for the Zephyr platforms.
 */
class BLEManagerImpl final : public BLEManager, private BleLayer, private BlePlatformDelegate, private BleApplicationDelegate
{
    // Allow the BLEManager interface class to delegate method calls to
    // the implementation methods provided by this class.
    friend BLEManager;

private:
    // ===== Members that implement the BLEManager internal interface.

    CHIP_ERROR _Init(void);
    void _Shutdown() {}
    bool _IsAdvertisingEnabled(void);
    CHIP_ERROR _SetAdvertisingEnabled(bool val);
    bool _IsAdvertising(void);
    CHIP_ERROR _SetAdvertisingMode(BLEAdvertisingMode mode);
    CHIP_ERROR _GetDeviceName(char *buf, size_t bufSize);
    CHIP_ERROR _SetDeviceName(const char *deviceName);
    uint16_t _NumConnections(void);
    void _OnPlatformEvent(const ChipDeviceEvent *event);
    BleLayer * _GetBleLayer(void);

    // ===== Members that implement virtual methods on BlePlatformDelegate.

    bool SubscribeCharacteristic(BLE_CONNECTION_OBJECT conId, const ChipBleUUID *svcId, const ChipBleUUID *charId);
    bool UnsubscribeCharacteristic(BLE_CONNECTION_OBJECT conId, const ChipBleUUID *svcId, const ChipBleUUID *charId);
    bool CloseConnection(BLE_CONNECTION_OBJECT conId);
    uint16_t GetMTU(BLE_CONNECTION_OBJECT conId) const;
    bool SendIndication(BLE_CONNECTION_OBJECT conId, const ChipBleUUID *svcId, const ChipBleUUID *charId, PacketBufferHandle pBuf);
    bool SendWriteRequest(BLE_CONNECTION_OBJECT conId, const ChipBleUUID *svcId, const ChipBleUUID *charId, PacketBufferHandle pBuf);
    bool SendReadRequest(BLE_CONNECTION_OBJECT conId, const ChipBleUUID *svcId, const ChipBleUUID *charId, PacketBufferHandle pBuf);
    bool SendReadResponse(BLE_CONNECTION_OBJECT conId, BLE_READ_REQUEST_CONTEXT requestContext, const ChipBleUUID *svcId, const ChipBleUUID *charId);

    // ===== Members that implement virtual methods on BleApplicationDelegate.

    void NotifyChipConnectionClosed(BLE_CONNECTION_OBJECT conId);

    // ===== Private members reserved for use by this class only.

    enum class Flags : uint8_t
    {
        kAsyncInitCompleted       = 0x0001, /**< One-time asynchronous initialization actions have been performed. */
        kAdvertisingEnabled       = 0x0002, /**< The application has enabled CHIPoBLE advertising. */
        kFastAdvertisingEnabled   = 0x0004, /**< The application has enabled fast advertising. */
        kAdvertising              = 0x0008, /**< The system is currently CHIPoBLE advertising. */
        kAdvertisingRefreshNeeded = 0x0010, /**< The advertising state/configuration has changed, but the SoftDevice has yet to be updated. */
        kChipoBleGattServiceRegister = 0x0020, /**< The system has currently CHIPoBLE GATT service registered. */
    };

    struct ServiceData;

    BitFlags<Flags> mFlags;
    uint16_t mGAPConns;
    CHIPoBLEServiceMode mServiceMode;
    bool mSubscribedConns;

    bt_conn_cb mConnCallbacks;
    bt_svc_cb mSvcCallbacks;
    BLEAdvertisingArbiter::Request mAdvertisingRequest = {};
#if CHIP_ENABLE_ADDITIONAL_DATA_ADVERTISING
    PacketBufferHandle c3CharDataBufferHandle;
#endif

    void DriveBLEState(void);
    CHIP_ERROR PrepareAdvertisingRequest();
    CHIP_ERROR StartAdvertising(void);
    CHIP_ERROR StopAdvertising(void);
    CHIP_ERROR HandleGAPConnect(const ChipDeviceEvent *event);
    CHIP_ERROR HandleGAPDisconnect(const ChipDeviceEvent *event);
    CHIP_ERROR HandleRXCharWrite(const ChipDeviceEvent *event);
    CHIP_ERROR HandleTXCharCCCDWrite(const ChipDeviceEvent *event);
    CHIP_ERROR HandleTXCharComplete(const ChipDeviceEvent *event);
#if CHIP_ENABLE_ADDITIONAL_DATA_ADVERTISING
    CHIP_ERROR PrepareC3CharData();
#endif
    bool IsSubscribed(uint16_t conn);
    bool SetSubscribed(uint16_t conn);
    bool UnsetSubscribed(uint16_t conn);
    uint32_t GetAdvertisingInterval();

    static void DriveBLEState(intptr_t arg);

    // Below callbacks run from the system workqueue context and have a limited stack capacity.
    static void HandleTXIndicated(uint16_t conn, uint8_t err);
    static void HandleConnect(uint16_t conn, uint8_t err);
    static void HandleDisconnect(uint16_t conn, uint8_t reason);
    static void HandleBLEAdvertisementIntervalChange(System::Layer *layer, void *param);
    static void HandleRXWrite(uint16_t conId, void *buf, uint8_t len);
    static void HandleTXCCCWrite(uint16_t conId, uint16_t value);

    // ===== Members for internal use by the following friends.

    friend BLEManager & BLEMgr(void);
    friend BLEManagerImpl & BLEMgrImpl(void);

    static BLEManagerImpl sInstance;

public:
    CHIP_ERROR ConfigureBle(uint32_t aAdapterId, bool aIsCentral);

#if CHIP_ENABLE_ADDITIONAL_DATA_ADVERTISING
    static ssize_t HandleC3Read(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset);
#endif
};

/**
 * Returns a reference to the public interface of the BLEManager singleton object.
 *
 * Internal components should use this to access features of the BLEManager object
 * that are common to all platforms.
 */
inline BLEManager & BLEMgr(void)
{
    return BLEManagerImpl::sInstance;
}

/**
 * Returns the platform-specific implementation of the BLEManager singleton object.
 *
 * Internal components can use this to gain access to features of the BLEManager
 * that are specific to the Zephyr platforms.
 */
inline BLEManagerImpl & BLEMgrImpl(void)
{
    return BLEManagerImpl::sInstance;
}

inline BleLayer * BLEManagerImpl::_GetBleLayer()
{
    return this;
}

inline bool BLEManagerImpl::_IsAdvertisingEnabled(void)
{
    return mFlags.Has(Flags::kAdvertisingEnabled);
}

inline bool BLEManagerImpl::_IsAdvertising(void)
{
    return mFlags.Has(Flags::kAdvertising);
}

} // namespace Internal
} // namespace DeviceLayer
} // namespace chip

#endif // CHIP_DEVICE_CONFIG_ENABLE_CHIPOBLE
