/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


/**
 * Provides an implementation of the BLEManager singleton object for NCP platforms.
 */

#include <platform/internal/CHIPDeviceLayerInternal.h>

#if CHIP_DEVICE_CONFIG_ENABLE_CHIPOBLE

#include "BLEManagerImpl.h"
#include "BLENCPPlatformEvent.h"
#include "BLENCPUtils.h"

#include <ble/CHIPBleServiceData.h>
#include <lib/support/CHIPMemString.h>
#include <lib/support/CodeUtils.h>
#include <lib/support/logging/CHIPLogging.h>
#include <platform/DeviceInstanceInfoProvider.h>
#include <platform/internal/BLEManager.h>
#if CHIP_ENABLE_ADDITIONAL_DATA_ADVERTISING
#include <setup_payload/AdditionalDataPayloadGenerator.h>
#endif

#include <array>

extern "C" {
#include "ncp_matter_ble.h"
}

using namespace ::chip;
using namespace ::chip::Ble;
using namespace ::chip::System;

namespace chip {
namespace DeviceLayer {
namespace Internal {

namespace {

bt_uuid_16 UUID16_CHIPoBLEService = BT_UUID_INIT_16(0xFFF6);

const ChipBleUUID chipUUID_CHIPoBLEChar_RX = { { 0x18, 0xEE, 0x2E, 0xF5, 0x26, 0x3D, 0x45, 0x59, 0x95, 0x9F, 0x4F, 0x9C, 0x42, 0x9F,
                                                 0x9D, 0x11 } };

const ChipBleUUID chipUUID_CHIPoBLEChar_TX = { { 0x18, 0xEE, 0x2E, 0xF5, 0x26, 0x3D, 0x45, 0x59, 0x95, 0x9F, 0x4F, 0x9C, 0x42, 0x9F,
                                                 0x9D, 0x12 } };

} // unnamed namespace

BLEManagerImpl BLEManagerImpl::sInstance;

CHIP_ERROR BLEManagerImpl::ConfigureBle(uint32_t aAdapterId, bool aIsCentral)
{
	return CHIP_NO_ERROR;
}

CHIP_ERROR BLEManagerImpl::_Init()
{
    ChipLogError(DeviceLayer, "NCP_adapter_log, BLEManagerImpl::_Init()");

    mServiceMode = ConnectivityManager::kCHIPoBLEServiceMode_Enabled;
    mFlags.ClearAll().Set(Flags::kAdvertisingEnabled, CHIP_DEVICE_CONFIG_CHIPOBLE_ENABLE_ADVERTISING_AUTOSTART);
    mFlags.Set(Flags::kFastAdvertisingEnabled, true);
    mGAPConns = 0;

    int err = ncp_bt_enable();
    VerifyOrReturnError(err == 0, MapErrorZephyr(err));

    memset(&mConnCallbacks, 0, sizeof(mConnCallbacks));
    mConnCallbacks.connected    = HandleConnect;
    mConnCallbacks.disconnected = HandleDisconnect;

    ncp_bt_conn_cb_register(&mConnCallbacks);

    // Initialize the CHIP BleLayer.
    ReturnErrorOnFailure(BleLayer::Init(this, this, &DeviceLayer::SystemLayer()));

    PlatformMgr().ScheduleWork(DriveBLEState, 0);

    return CHIP_NO_ERROR;
}

void BLEManagerImpl::DriveBLEState(intptr_t arg)
{
    BLEMgrImpl().DriveBLEState();
}

void BLEManagerImpl::DriveBLEState()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    // Perform any initialization actions that must occur after the CHIP task is running.
    if (!mFlags.Has(Flags::kAsyncInitCompleted))
    {
        mFlags.Set(Flags::kAsyncInitCompleted);
    }

    // If the application has enabled CHIPoBLE and BLE advertising...
    if (mServiceMode == ConnectivityManager::kCHIPoBLEServiceMode_Enabled &&
        mFlags.Has(Flags::kAdvertisingEnabled)
#if CHIP_DEVICE_CONFIG_CHIPOBLE_SINGLE_CONNECTION
        // and no connections are active...
        && (NumConnections() == 0)
#endif
    )
    {
        // Start/re-start advertising if not already advertising, or if the
        // advertising state needs to be refreshed.
        if (!mFlags.Has(Flags::kAdvertising) || mFlags.Has(Flags::kAdvertisingRefreshNeeded))
        {
            mFlags.Clear(Flags::kAdvertisingRefreshNeeded);
            err = StartAdvertising();
            SuccessOrExit(err);
        }
    }
    else
    {
        if (mFlags.Has(Flags::kAdvertising))
        {
            err = StopAdvertising();
            SuccessOrExit(err);
        }

        // If no connections are active unregister also CHIPoBLE GATT service
        if (NumConnections() == 0 && mFlags.Has(Flags::kChipoBleGattServiceRegister))
        {
            // Unregister CHIPoBLE service to not allow discovering it when pairing is disabled.
            if (ncp_bt_gatt_service_unregister() != 0)
            {
                ChipLogError(DeviceLayer, "NCP_adapter_log, Failed to unregister CHIPoBLE GATT service");
            }
            else
            {
                mFlags.Clear(Flags::kChipoBleGattServiceRegister);
            }
        }
    }

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(DeviceLayer, "NCP_adapter_log, Disabling CHIPoBLE service due to error: %" CHIP_ERROR_FORMAT, err.Format());
        mServiceMode = ConnectivityManager::kCHIPoBLEServiceMode_Disabled;
    }
}

struct BLEManagerImpl::ServiceData
{
    uint8_t uuid[2];
    ChipBLEDeviceIdentificationInfo deviceIdInfo;
} __attribute__((packed));

inline CHIP_ERROR BLEManagerImpl::PrepareAdvertisingRequest()
{
    static ServiceData serviceData;
    static std::array<bt_data, 2> advertisingData;
    static std::array<bt_data, 1> scanResponseData;
    static_assert(sizeof(serviceData) == 10, "Unexpected size of BLE advertising data!");

    //Seems that BLE commissioning identify device with adv service uuid, not concern about device name.
    //Setup name with "CHIP_DEVICE_CONFIG_BLE_DEVICE_NAME_PREFIX", or get name from ncp device "ncp_bt_get_name()".
    const char *name       = "MATTER-3840";
    const uint8_t nameSize = static_cast<uint8_t>(strlen(name));

    Encoding::LittleEndian::Put16(serviceData.uuid, UUID16_CHIPoBLEService.val);
    ReturnErrorOnFailure(ConfigurationMgr().GetBLEDeviceIdentificationInfo(serviceData.deviceIdInfo));

    advertisingData[0]  = BT_DATA(BT_DATA_SVC_DATA16, &serviceData, sizeof(serviceData));
    advertisingData[1]  = BT_DATA(BT_DATA_NAME_COMPLETE, name, nameSize);

    mAdvertisingRequest.priority         = CHIP_DEVICE_BLE_ADVERTISING_PRIORITY;
    mAdvertisingRequest.options          = 0;
    mAdvertisingRequest.minInterval      = mFlags.Has(Flags::kFastAdvertisingEnabled)
             ? CHIP_DEVICE_CONFIG_BLE_FAST_ADVERTISING_INTERVAL_MIN
             : CHIP_DEVICE_CONFIG_BLE_SLOW_ADVERTISING_INTERVAL_MIN;
    mAdvertisingRequest.maxInterval      = mFlags.Has(Flags::kFastAdvertisingEnabled)
             ? CHIP_DEVICE_CONFIG_BLE_FAST_ADVERTISING_INTERVAL_MAX
             : CHIP_DEVICE_CONFIG_BLE_SLOW_ADVERTISING_INTERVAL_MAX;
    mAdvertisingRequest.advertisingData  = Span<bt_data>(advertisingData);
    mAdvertisingRequest.scanResponseData = nameSize ? Span<bt_data>(scanResponseData) : Span<bt_data>{};

    mAdvertisingRequest.onStarted = [](int rc) {
        if (rc == 0)
        {
            ChipLogProgress(DeviceLayer, "NCP_adapter_log, CHIPoBLE advertising started");
        }
        else
        {
            ChipLogError(DeviceLayer, "NCP_adapter_log, Failed to start CHIPoBLE advertising: %d", rc);
        }
    };

    return CHIP_NO_ERROR;
}

CHIP_ERROR BLEManagerImpl::StartAdvertising()
{
    ChipLogError(DeviceLayer, "NCP_adapter_log, BLEManagerImpl::StartAdvertising");

    ReturnErrorOnFailure(PrepareAdvertisingRequest());

    // Register dynamically CHIPoBLE GATT service
    if (!mFlags.Has(Flags::kChipoBleGattServiceRegister))
    {
        int err = ncp_bt_gatt_service_register();

        if (err != 0)
        {
            ChipLogError(DeviceLayer, "NCP_adapter_log, Failed to register CHIPoBLE GATT service");
        }

        VerifyOrReturnError(err == 0, MapErrorZephyr(err));

        memset(&mSvcCallbacks, 0, sizeof(mSvcCallbacks));
        mSvcCallbacks.rx_write_cb       = HandleRXWrite;
        mSvcCallbacks.tx_ccc_write_cb   = HandleTXCCCWrite;
        mSvcCallbacks.tx_ind_confirm_cb = HandleTXIndicated;
 
        ncp_bt_matter_svc_cb_register(&mSvcCallbacks);

        mFlags.Set(Flags::kChipoBleGattServiceRegister);
    }

    // Initialize C3 characteristic data
#if CHIP_ENABLE_ADDITIONAL_DATA_ADVERTISING
    ReturnErrorOnFailure(PrepareC3CharData());
#endif

    // Request advertising
    ReturnErrorOnFailure(BLEAdvertisingArbiter::InsertRequest(mAdvertisingRequest));

    // Transition to the Advertising state...
    if (!mFlags.Has(Flags::kAdvertising))
    {
        mFlags.Set(Flags::kAdvertising);

        // Post a CHIPoBLEAdvertisingChange(Started) event.
        {
            ChipDeviceEvent advChange;
            advChange.Type                             = DeviceEventType::kCHIPoBLEAdvertisingChange;
            advChange.CHIPoBLEAdvertisingChange.Result = kActivity_Started;
            ReturnErrorOnFailure(PlatformMgr().PostEvent(&advChange));
        }

        if (mFlags.Has(Flags::kFastAdvertisingEnabled))
        {
            // Start timer to change advertising interval.
            DeviceLayer::SystemLayer().StartTimer(
                System::Clock::Milliseconds32(CHIP_DEVICE_CONFIG_BLE_ADVERTISING_INTERVAL_CHANGE_TIME),
                HandleBLEAdvertisementIntervalChange, this);
        }
    }

    return CHIP_NO_ERROR;
}

CHIP_ERROR BLEManagerImpl::StopAdvertising()
{
    BLEAdvertisingArbiter::CancelRequest(mAdvertisingRequest);

    // Transition to the not Advertising state...
    if (mFlags.Has(Flags::kAdvertising))
    {
        mFlags.Clear(Flags::kAdvertising);
        mFlags.Set(Flags::kFastAdvertisingEnabled, true);

        ChipLogProgress(DeviceLayer, "NCP_adapter_log, CHIPoBLE advertising stopped");

        // Post a CHIPoBLEAdvertisingChange(Stopped) event.
        {
            ChipDeviceEvent advChange;
            advChange.Type                             = DeviceEventType::kCHIPoBLEAdvertisingChange;
            advChange.CHIPoBLEAdvertisingChange.Result = kActivity_Stopped;
            ReturnErrorOnFailure(PlatformMgr().PostEvent(&advChange));
        }

        // Cancel timer event changing CHIPoBLE advertisement interval
        DeviceLayer::SystemLayer().CancelTimer(HandleBLEAdvertisementIntervalChange, this);
    }

    return CHIP_NO_ERROR;
}

CHIP_ERROR BLEManagerImpl::_SetAdvertisingEnabled(bool val)
{
    if (mFlags.Has(Flags::kAdvertisingEnabled) != val)
    {
        ChipLogDetail(DeviceLayer, "NCP_adapter_log, CHIPoBLE advertising set to %s", val ? "on" : "off");

        mFlags.Set(Flags::kAdvertisingEnabled, val);
        PlatformMgr().ScheduleWork(DriveBLEState, 0);
    }

    return CHIP_NO_ERROR;
}

CHIP_ERROR BLEManagerImpl::_SetAdvertisingMode(BLEAdvertisingMode mode)
{
    switch (mode)
    {
    case BLEAdvertisingMode::kFastAdvertising:
        mFlags.Set(Flags::kFastAdvertisingEnabled, true);
        break;
    case BLEAdvertisingMode::kSlowAdvertising:
        mFlags.Set(Flags::kFastAdvertisingEnabled, false);
        break;
    default:
        return CHIP_ERROR_INVALID_ARGUMENT;
    }

    mFlags.Set(Flags::kAdvertisingRefreshNeeded);
    PlatformMgr().ScheduleWork(DriveBLEState, 0);

    return CHIP_NO_ERROR;
}

CHIP_ERROR BLEManagerImpl::_GetDeviceName(char * buf, size_t bufSize)
{
    ChipLogProgress(DeviceLayer, "NCP_adapter_log, BLEManagerImpl::_GetDeviceName()");

    //Get device name "ncp_bt_get_name()".
    Platform::CopyString(buf, bufSize, "NCP_BLE");

    return CHIP_NO_ERROR;
}

CHIP_ERROR BLEManagerImpl::_SetDeviceName(const char * deviceName)
{
    ChipLogDetail(DeviceLayer, "NCP_adapter_log, BLEManagerImpl::_SetDeviceName()");
    
    //Set device name "ncp_bt_set_name()".

    return MapErrorZephyr(0); 
}

CHIP_ERROR BLEManagerImpl::HandleGAPConnect(const ChipDeviceEvent * event)
{
    const BleConnEventType * connEvent = &event->Platform.BleConnEvent;

    if (connEvent->HciResult == 0)
    {
        ChipLogProgress(DeviceLayer, "NCP_adapter_log, BLE connection established");
        mGAPConns++;
    }
    else
    {
        ChipLogError(DeviceLayer, "NCP_adapter_log, BLE connection failed (reason: 0x%02x)", connEvent->HciResult);
    }

    ChipLogProgress(DeviceLayer, "NCP_adapter_log, Current number of connections: %u/%u", NumConnections(), CONFIG_BT_MAX_CONN);

    mFlags.Set(Flags::kAdvertisingRefreshNeeded);
    PlatformMgr().ScheduleWork(DriveBLEState, 0);

    return CHIP_NO_ERROR;
}

CHIP_ERROR BLEManagerImpl::HandleGAPDisconnect(const ChipDeviceEvent * event)
{
    const BleConnEventType * connEvent = &event->Platform.BleConnEvent;

    ChipLogProgress(DeviceLayer, "NCP_adapter_log, BLE GAP connection terminated (reason 0x%02x)", connEvent->HciResult);

    mGAPConns--;

    // If indications were enabled for this connection, record that they are now disabled and
    // notify the BLE Layer of a disconnect.
    if (UnsetSubscribed(connEvent->BtConn))
    {
        CHIP_ERROR disconReason;
        switch (connEvent->HciResult)
        {
        case BT_HCI_ERR_REMOTE_USER_TERM_CONN:
            // Do not treat proper connection termination as an error and exit.
            VerifyOrExit(!ConfigurationMgr().IsFullyProvisioned(), );
            disconReason = BLE_ERROR_REMOTE_DEVICE_DISCONNECTED;
            break;
        case BT_HCI_ERR_LOCALHOST_TERM_CONN:
            disconReason = BLE_ERROR_APP_CLOSED_CONNECTION;
            break;
        default:
            disconReason = BLE_ERROR_CHIPOBLE_PROTOCOL_ABORT;
            break;
        }
        HandleConnectionError(connEvent->BtConn, disconReason);
    }

exit:
    ChipLogProgress(DeviceLayer, "NCP_adapter_log, Current number of connections: %u/%u", NumConnections(), CONFIG_BT_MAX_CONN);

    ChipDeviceEvent disconnectEvent;
    disconnectEvent.Type = DeviceEventType::kCHIPoBLEConnectionClosed;
    ReturnErrorOnFailure(PlatformMgr().PostEvent(&disconnectEvent));

    // Force a reconfiguration of advertising in case we switched to non-connectable mode when
    // the BLE connection was established.
    mFlags.Set(Flags::kAdvertisingRefreshNeeded);
    PlatformMgr().ScheduleWork(DriveBLEState, 0);

    return CHIP_NO_ERROR;
}

CHIP_ERROR BLEManagerImpl::HandleTXCharCCCDWrite(const ChipDeviceEvent * event)
{
    const BleCCCWriteEventType * writeEvent = &event->Platform.BleCCCWriteEvent;

    ChipLogDetail(DeviceLayer, "NCP_adapter_log, New CCCD value: 0x%04x", writeEvent->Value);

    // If the client has requested to enable indications and if it is not yet subscribed
    if (writeEvent->Value == BT_GATT_CCC_INDICATE && SetSubscribed(writeEvent->BtConn))
    {
        // Alert the BLE layer that CHIPoBLE "subscribe" has been received and increment the bt_conn reference counter.
        HandleSubscribeReceived(writeEvent->BtConn, &CHIP_BLE_SVC_ID, &chipUUID_CHIPoBLEChar_TX);

        ChipLogProgress(DeviceLayer, "NCP_adapter_log, CHIPoBLE connection established (GATT MTU: %u)", GetMTU(writeEvent->BtConn));

        // Post a CHIPoBLEConnectionEstablished event to the DeviceLayer and the application.
        {
            ChipDeviceEvent conEstEvent;
            conEstEvent.Type = DeviceEventType::kCHIPoBLEConnectionEstablished;
            ReturnErrorOnFailure(PlatformMgr().PostEvent(&conEstEvent));
        }
    }
    else
    {
        if (UnsetSubscribed(writeEvent->BtConn))
        {
            HandleUnsubscribeReceived(writeEvent->BtConn, &CHIP_BLE_SVC_ID, &chipUUID_CHIPoBLEChar_TX);
        }
    }

    return CHIP_NO_ERROR;
}

CHIP_ERROR BLEManagerImpl::HandleRXCharWrite(const ChipDeviceEvent * event)
{
    const BleC1WriteEventType * c1WriteEvent = &event->Platform.BleC1WriteEvent;

    ChipLogDetail(DeviceLayer, "NCP_adapter_log, Write request received for CHIPoBLE RX characteristic");

    HandleWriteReceived(c1WriteEvent->BtConn, &CHIP_BLE_SVC_ID, &chipUUID_CHIPoBLEChar_RX,
                        PacketBufferHandle::Adopt(c1WriteEvent->Data));

    return CHIP_NO_ERROR;
}

CHIP_ERROR BLEManagerImpl::HandleTXCharComplete(const ChipDeviceEvent * event)
{
    const BleC2IndDoneEventType * c2IndDoneEvent = &event->Platform.BleC2IndDoneEvent;

    ChipLogDetail(DeviceLayer, "NCP_adapter_log, Indication for CHIPoBLE TX characteristic done (result 0x%02x)", c2IndDoneEvent->Result);

    // Signal the BLE Layer that the outstanding indication is complete.
    HandleIndicationConfirmation(c2IndDoneEvent->BtConn, &CHIP_BLE_SVC_ID, &chipUUID_CHIPoBLEChar_TX);

    return CHIP_NO_ERROR;
}

#if CHIP_ENABLE_ADDITIONAL_DATA_ADVERTISING
CHIP_ERROR BLEManagerImpl::PrepareC3CharData()
{

    CHIP_ERROR err = CHIP_NO_ERROR;
    BitFlags<AdditionalDataFields> additionalDataFields;
    AdditionalDataPayloadGeneratorParams additionalDataPayloadParams;

#if CHIP_ENABLE_ROTATING_DEVICE_ID && defined(CHIP_DEVICE_CONFIG_ROTATING_DEVICE_ID_UNIQUE_ID)
    uint8_t rotatingDeviceIdUniqueId[ConfigurationManager::kRotatingDeviceIDUniqueIDLength] = {};
    MutableByteSpan rotatingDeviceIdUniqueIdSpan(rotatingDeviceIdUniqueId);

    err = DeviceLayer::GetDeviceInstanceInfoProvider()->GetRotatingDeviceIdUniqueId(rotatingDeviceIdUniqueIdSpan);
    SuccessOrExit(err);
    err = ConfigurationMgr().GetLifetimeCounter(additionalDataPayloadParams.rotatingDeviceIdLifetimeCounter);
    SuccessOrExit(err);
    additionalDataPayloadParams.rotatingDeviceIdUniqueId = rotatingDeviceIdUniqueIdSpan;
    additionalDataFields.Set(AdditionalDataFields::RotatingDeviceId);
#endif /* CHIP_ENABLE_ROTATING_DEVICE_ID && defined(CHIP_DEVICE_CONFIG_ROTATING_DEVICE_ID_UNIQUE_ID) */


    err = AdditionalDataPayloadGenerator().generateAdditionalDataPayload(additionalDataPayloadParams, c3CharDataBufferHandle,
                                                                         additionalDataFields);

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(DeviceLayer, "Failed to generate TLV encoded Additional Data (%s)", __func__);
    }

    return err;
}
#endif

void BLEManagerImpl::HandleBLEAdvertisementIntervalChange(System::Layer * layer, void * param)
{
    BLEMgr().SetAdvertisingMode(BLEAdvertisingMode::kSlowAdvertising);
    ChipLogProgress(DeviceLayer, "NCP_adapter_log, CHIPoBLE advertising mode changed to slow");
}

void BLEManagerImpl::_OnPlatformEvent(const ChipDeviceEvent * event)
{

    CHIP_ERROR err = CHIP_NO_ERROR;

    switch (event->Type)
    {
    case DeviceEventType::kPlatformZephyrBleConnected:
        err = HandleGAPConnect(event);
        break;

    case DeviceEventType::kPlatformZephyrBleDisconnected:
        err = HandleGAPDisconnect(event);
        break;

    case DeviceEventType::kPlatformZephyrBleCCCWrite:
        err = HandleTXCharCCCDWrite(event);
        break;

    case DeviceEventType::kPlatformZephyrBleC1WriteEvent:
        err = HandleRXCharWrite(event);
        break;

    case DeviceEventType::kPlatformZephyrBleC2IndDoneEvent:
        err = HandleTXCharComplete(event);
        break;

    default:
        break;
    }

    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(DeviceLayer, "Disabling CHIPoBLE service due to error: %" CHIP_ERROR_FORMAT, err.Format());
        mServiceMode = ConnectivityManager::kCHIPoBLEServiceMode_Disabled;
        PlatformMgr().ScheduleWork(DriveBLEState, 0);
    }

}

uint16_t BLEManagerImpl::_NumConnections(void)
{
    return mGAPConns;
}

bool BLEManagerImpl::CloseConnection(BLE_CONNECTION_OBJECT conId)
{
    ChipLogProgress(DeviceLayer, "NCP_adapter_log, Closing BLE GATT connection");

    return ncp_bt_conn_disconnect(conId, BT_HCI_ERR_REMOTE_USER_TERM_CONN) == 0;
}

uint16_t BLEManagerImpl::GetMTU(BLE_CONNECTION_OBJECT conId) const
{
    uint16_t mtuSize = ncp_bt_gatt_get_mtu(conId);
    ChipLogProgress(DeviceLayer, "NCP_adapter_log, Get mtu size %d", mtuSize);

    return mtuSize;
}

bool BLEManagerImpl::SubscribeCharacteristic(BLE_CONNECTION_OBJECT conId, const ChipBleUUID * svcId, const ChipBleUUID * charId)
{
    ChipLogDetail(DeviceLayer, "NCP_adapter_log, BLE central not implemented");

    return false;
}

bool BLEManagerImpl::UnsubscribeCharacteristic(BLE_CONNECTION_OBJECT conId, const ChipBleUUID * svcId, const ChipBleUUID * charId)
{
    ChipLogDetail(DeviceLayer, "NCP_adapter_log, BLE central not implemented");

    return false;
}

bool BLEManagerImpl::SendIndication(BLE_CONNECTION_OBJECT conId, const ChipBleUUID * svcId, const ChipBleUUID * charId,
                                    PacketBufferHandle pBuf)
{
    CHIP_ERROR err                   = CHIP_NO_ERROR;
    int status                       = 0;

    VerifyOrExit(IsSubscribed(conId) == true, err = CHIP_ERROR_INVALID_ARGUMENT);

    ChipLogDetail(DeviceLayer, "NCP_adapter_log, Sending indication for CHIPoBLE TX characteristic (len %u)", pBuf->DataLength());

    status = ncp_bt_gatt_indicate(conId, pBuf->Start(), pBuf->DataLength());
    VerifyOrExit(status == 0, err = MapErrorZephyr(status));

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(DeviceLayer, "NCP_adapter_log, SendIndication failed: %" CHIP_ERROR_FORMAT, err.Format());
    }

    return err == CHIP_NO_ERROR;
}

bool BLEManagerImpl::SendWriteRequest(BLE_CONNECTION_OBJECT conId, const ChipBleUUID * svcId, const ChipBleUUID * charId,
                                      PacketBufferHandle pBuf)
{
    ChipLogDetail(DeviceLayer, "NCP_adapter_log, BLE central not implemented");
    return false;
}

bool BLEManagerImpl::SendReadRequest(BLE_CONNECTION_OBJECT conId, const ChipBleUUID * svcId, const ChipBleUUID * charId,
                                     PacketBufferHandle pBuf)
{
    ChipLogDetail(DeviceLayer, "NCP_adapter_log, BLE central not implemented");
    return false;
}

bool BLEManagerImpl::SendReadResponse(BLE_CONNECTION_OBJECT conId, BLE_READ_REQUEST_CONTEXT requestContext,
                                      const ChipBleUUID * svcId, const ChipBleUUID * charId)
{
    ChipLogDetail(DeviceLayer, "NCP_adapter_log, BLE central not implemented");
    return false;
}

void BLEManagerImpl::NotifyChipConnectionClosed(BLE_CONNECTION_OBJECT conId)
{
    ChipLogProgress(Ble, "Got notification regarding chip connection closure");
#if CHIP_DEVICE_CONFIG_ENABLE_WPA && !CHIP_DEVICE_CONFIG_SUPPORTS_CONCURRENT_CONNECTION
    if (mState == kState_NotInitialized)
    {
        // Close BLE GATT connections to disconnect BlueZ
        CloseConnection(conId);
        // In Non-Concurrent mode start the Wi-Fi, as BLE has been stopped
        DeviceLayer::ConnectivityMgrImpl().StartNonConcurrentWiFiManagement();
    }
#endif // CHIP_DEVICE_CONFIG_SUPPORTS_CONCURRENT_CONNECTION
}

bool BLEManagerImpl::IsSubscribed(uint16_t conn)
{
    return mSubscribedConns;
}

bool BLEManagerImpl::SetSubscribed(uint16_t conn)
{
    bool isSubscribed = mSubscribedConns;
    mSubscribedConns  = true;

    return !isSubscribed;
}

bool BLEManagerImpl::UnsetSubscribed(uint16_t conn)
{
    bool isSubscribed = mSubscribedConns;
    mSubscribedConns = false;

    return isSubscribed;
}

void BLEManagerImpl::HandleRXWrite(uint16_t conId, void * buf, uint8_t len)
{
    ChipDeviceEvent event;
    PacketBufferHandle packetBuf = PacketBufferHandle::NewWithData(buf, len);

    ChipLogDetail(DeviceLayer, "NCP_adapter_log, BLEManagerImpl::HandleRXWrite, len: %d", len);
    if (!packetBuf.IsNull())
    {
        // Arrange to post a CHIPoBLERXWriteEvent event to the CHIP queue.
        event.Type                            = DeviceEventType::kPlatformZephyrBleC1WriteEvent;
        event.Platform.BleC1WriteEvent.BtConn = conId;//ncp_bt_conn_ref(conId);
        event.Platform.BleC1WriteEvent.Data   = std::move(packetBuf).UnsafeRelease();
    }

    // If we failed to allocate a buffer, post a kPlatformZephyrBleOutOfBuffersEvent event.
    else
    {
        event.Type = DeviceEventType::kPlatformZephyrBleOutOfBuffersEvent;
    }

    PlatformMgr().PostEventOrDie(&event);
}

void BLEManagerImpl::HandleTXCCCWrite(uint16_t conId, uint16_t value)
{
    ChipDeviceEvent event;

    ChipLogDetail(DeviceLayer, "NCP_adapter_log, BLEManagerImpl::HandleTXCCCWrite, VALUE: %d", value);

    if (value != BT_GATT_CCC_INDICATE && value != 0)
    {
        return;
    }

    event.Type                             = DeviceEventType::kPlatformZephyrBleCCCWrite;
    event.Platform.BleCCCWriteEvent.BtConn = conId;
    event.Platform.BleCCCWriteEvent.Value  = value;

    PlatformMgr().PostEventOrDie(&event);
}

void BLEManagerImpl::HandleTXIndicated(uint16_t conId, uint8_t err)
{
    ChipDeviceEvent event;

    ChipLogDetail(DeviceLayer, "NCP_adapter_log, BLEManagerImpl::HandleTXIndicated, err: %d", err);

    event.Type                              = DeviceEventType::kPlatformZephyrBleC2IndDoneEvent;
    event.Platform.BleC2IndDoneEvent.BtConn = conId;
    event.Platform.BleC2IndDoneEvent.Result = err;

    PlatformMgr().PostEventOrDie(&event);
}

void BLEManagerImpl::HandleConnect(uint16_t conId, uint8_t err)
{
    ChipDeviceEvent event;

    ChipLogDetail(DeviceLayer, "NCP_adapter_log, BLEManagerImpl::HandleConnect, conId: %d, err: %d", conId, err);
    PlatformMgr().LockChipStack();

    // Don't handle BLE connecting events when it is not related to CHIPoBLE
    VerifyOrExit(sInstance.mFlags.Has(Flags::kChipoBleGattServiceRegister), );

    event.Type                            = DeviceEventType::kPlatformZephyrBleConnected;
    event.Platform.BleConnEvent.BtConn    = conId;//ncp_bt_conn_ref(conId);
    event.Platform.BleConnEvent.HciResult = err;

    PlatformMgr().PostEventOrDie(&event);

exit:
    PlatformMgr().UnlockChipStack();
}

void BLEManagerImpl::HandleDisconnect(uint16_t conId, uint8_t reason)
{
    ChipDeviceEvent event;

    ChipLogDetail(DeviceLayer, "NCP_adapter_log, BLEManagerImpl::HandleDisconnect, conId: %d, reason: %d", conId, reason);
    PlatformMgr().LockChipStack();

    // Don't handle BLE disconnecting events when it is not related to CHIPoBLE
    VerifyOrExit(sInstance.mFlags.Has(Flags::kChipoBleGattServiceRegister), );

    event.Type                            = DeviceEventType::kPlatformZephyrBleDisconnected;
    event.Platform.BleConnEvent.BtConn    = conId;
    event.Platform.BleConnEvent.HciResult = reason;

    PlatformMgr().PostEventOrDie(&event);

exit:
    PlatformMgr().UnlockChipStack();
}

#if CHIP_ENABLE_ADDITIONAL_DATA_ADVERTISING
ssize_t BLEManagerImpl::HandleC3Read(struct bt_conn * conId, const struct bt_gatt_attr * attr, void * buf, uint16_t len,
                                     uint16_t offset)
{
    ChipLogDetail(DeviceLayer, "Read request received for CHIPoBLE C3 (ConnId 0x%02x)", bt_conn_index(conId));

    if (sInstance.c3CharDataBufferHandle.IsNull())
    {
        return 0;
    }

    return bt_gatt_attr_read(conId, attr, buf, len, offset, sInstance.c3CharDataBufferHandle->Start(),
                             sInstance.c3CharDataBufferHandle->DataLength());
}
#endif

} // namespace Internal
} // namespace DeviceLayer
} // namespace chip

#endif // CHIP_DEVICE_CONFIG_ENABLE_CHIPOBLE
