/*
 *    Copyright (c) 2023 Project CHIP Authors
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

#include <app-common/zap-generated/attribute-type.h>

#include "BridgeConfig.h"
#include "BridgeMgr.h"
#include "ZcbMessage.h"
#include "newDb.h"
#include "zcb.h"
#include "ZigbeeConstant.h"
#include "ZigbeeDevices.h"

// define global variable
ZcbMsg_t ZcbMsg = {
    .AnnounceStart = false,
    .HandleMask = true,
    .bridge_mutex = PTHREAD_MUTEX_INITIALIZER,
    .bridge_cond =  PTHREAD_COND_INITIALIZER,
    .msg_type = BRIDGE_UNKNOW,
};

int ZcbNodesNum = 0;
Device* BridgeDevMgr::gDevices[CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT + 1];

BridgeDevMgr::BridgeDevMgr()
{
    gFirstDynamicEndpointId = 0;
    gFirstDynamicEndpointId = 0;
}

BridgeDevMgr::~BridgeDevMgr()
{
    eZCB_SendMsg(BRIDGE_LEAVE, NULL, NULL);
    pthread_join(this->ZcbMonitor_thread, NULL);
    RemoveAllDevice();
    printf("free BridgeDevMgr ! \n");
}


void BridgeDevMgr::AddOnOffNode(ZigbeeDev_t *ZigbeeDev)
{
    std::string onoff_label = "Zigbee Light ";
    BridgeOnOff *Light = new BridgeOnOff(
        (onoff_label + std::to_string(ZigbeeDev->zcb.saddr)).c_str(),
        "Office",
        ZigbeeDev,
        MATTER_ARRAY_SIZE(bridgedLightClusters)
    );

    Light->SetChangeCallback(&HandleDeviceOnOffStatusChanged);

#if !CHIP_CONFIG_USE_ENDPOINT_UNIQUE_ID
    AddDeviceEndpoint(
        Light,
        &bridgedLightEndpoint,
        Span<const EmberAfDeviceType>(gBridgedOnOffDeviceTypes),
        Span<DataVersion>(Light->DataVersions, MATTER_ARRAY_SIZE(bridgedLightClusters)),
        1
    );
#else
    AddDeviceEndpoint(
        Light,
        &bridgedLightEndpoint,
        Span<const EmberAfDeviceType>(gBridgedOnOffDeviceTypes),
        Span<DataVersion>(Light->DataVersions, MATTER_ARRAY_SIZE(bridgedLightClusters)),
        ""_span, 1
    );
#endif

    Light->GetOnOff();
}

void BridgeDevMgr::AddTempSensorNode(ZigbeeDev_t *ZigbeeDev)
{
    std::string sensor_label = "Zigbee TempSensor ";
    BridgeTempSensor *TempSensor = new BridgeTempSensor(
            (sensor_label + std::to_string(ZigbeeDev->zcb.saddr)).c_str(),
            "Office",
            ZigbeeDev,
            minMeasuredValue, maxMeasuredValue, initialMeasuredValue,
            MATTER_ARRAY_SIZE(bridgedTempSensorClusters)
    );

    TempSensor->SetChangeCallback(&HandleDeviceTempSensorStatusChanged);

    if(TempSensor->StartMonitor()) {
        delete TempSensor;
        TempSensor = NULL;
    }

#if !CHIP_CONFIG_USE_ENDPOINT_UNIQUE_ID
    AddDeviceEndpoint(
        TempSensor,
        &bridgedTempSensorEndpoint,
        Span<const EmberAfDeviceType>(gBridgedTempSensorDeviceTypes),
        Span<DataVersion>(TempSensor->DataVersions, MATTER_ARRAY_SIZE(bridgedTempSensorClusters)),
        1
    );
#else
    AddDeviceEndpoint(
        TempSensor,
        &bridgedTempSensorEndpoint,
        Span<const EmberAfDeviceType>(gBridgedTempSensorDeviceTypes),
        Span<DataVersion>(TempSensor->DataVersions, MATTER_ARRAY_SIZE(bridgedTempSensorClusters)),
        ""_span, 1
    );
#endif
}

void BridgeDevMgr::AddNewZcbNode(newdb_zcb_t zcb)
{
    ZigbeeDev_t ZigbeeDevice;

    ZigbeeDevice.zcb = zcb;
    newDbGetDevice( ZigbeeDevice.zcb.mac, &ZigbeeDevice.dev);

    AddZcbNode(&ZigbeeDevice);
}

int BridgeDevMgr::AddZcbNode(ZigbeeDev_t* ZigbeeDev)
{
    if (ZigbeeDev->zcb.uSupportedClusters.sClusterBitmap.hasOnOff) {
        AddOnOffNode(ZigbeeDev);
        return 1;
    }

    if (ZigbeeDev->zcb.uSupportedClusters.sClusterBitmap.hasTemperatureSensing) {
        AddTempSensorNode(ZigbeeDev);
        return 1;
    }

    return 0;
}

void BridgeDevMgr::MapZcbNodes()
{
    ZigbeeDev_t* ZigbeeDevList[CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT];
    newDbGetZigbeeDeviceList(ZigbeeDevList, CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT, &ZcbNodesNum);

    for(int i = 0; i < ZcbNodesNum; i++ ) {
        AddZcbNode(ZigbeeDevList[i]);
    }

    newDbfreeZigbeeDeviceList(ZigbeeDevList, ZcbNodesNum);
}

void BridgeDevMgr::start()
{
    // Set starting endpoint id where dynamic endpoints will be assigned, which
    // will be the next consecutive endpoint id after the last fixed endpoint.
    gFirstDynamicEndpointId = static_cast<chip::EndpointId>(
        static_cast<int>(emberAfEndpointFromIndex(static_cast<uint16_t>(emberAfFixedEndpointCount() - 1))) + 1);
    gCurrentEndpointId = gFirstDynamicEndpointId;
    MapZcbNodes();

    // ChipLogProgress(DeviceLayer, "gFirstDynamicEndpointId: %d", gFirstDynamicEndpointId);

    // Disable last fixed endpoint, which is used as a placeholder for all of the
    // supported clusters so that ZAP will generated the requisite code.
    emberAfEndpointEnableDisable(emberAfEndpointFromIndex(static_cast<uint16_t>(emberAfFixedEndpointCount() - 1)), false);

    // start monitor
    start_threads();
}


int BridgeDevMgr::start_threads()
{
    int res = pthread_create(&ZcbMonitor_thread, nullptr, ZcbMonitor, (void*)this);
    if (res)
    {
        printf("Error creating polling thread: %d\n", res);
        return -1;
    }

    return 0;
}

void* BridgeDevMgr::ZcbMonitor(void *context)
{
    BridgeDevMgr *ThisMgr = (BridgeDevMgr *)context;
    while( 1 )
    {
        pthread_mutex_lock(&ZcbMsg.bridge_mutex);
        while(ZcbMsg.HandleMask) {
            if (pthread_cond_wait(&ZcbMsg.bridge_cond, &ZcbMsg.bridge_mutex) == 0) {
                switch (ZcbMsg.msg_type)
                {
                    case BRIDGE_ADD_DEV: {
                        ThisMgr->AddNewZcbNode(ZcbMsg.zcb);
                        ZcbMsg.zcb = {0};
                        ZcbMsg.msg_type = BRIDGE_UNKNOW;
                        }
                        break;

                    case BRIDGE_REMOVE_DEV: {
                        ThisMgr->RemoveDevice(gDevices[ZcbMsg.zcb.matterIndex]);
                        ZcbMsg.zcb = {0};
                        ZcbMsg.msg_type = BRIDGE_UNKNOW;
                        }
                        break;

                    case BRIDGE_FACTORY_RESET: {
                        sleep(1);
                        ThisMgr->RemoveAllDevice();
                        ZcbMsg.zcb = {0};
                        ZcbMsg.msg_type = BRIDGE_UNKNOW;
                        }
                        break;

                    case BRIDGE_WRITE_ATTRIBUTE: {
                        ZcbAttribute_t *Data = (ZcbAttribute_t*)ZcbMsg.msg_data;
                        ThisMgr->WriteAttributeToDynamicEndpoint(ZcbMsg.zcb, Data->u16ClusterID, Data->u16AttributeID, Data->u64Data, ZCL_INT16S_ATTRIBUTE_TYPE);
                        free(Data);
                        ZcbMsg.zcb = {0};
                        ZcbMsg.msg_type = BRIDGE_UNKNOW;
                        }
                        break;

                    case BRIDGE_LEAVE: {
                        printf("Bridge Monitor exit ! \n");
                        return NULL;
                    }

                    default:
                        break;
                }
            }

        }

        ZcbMsg.HandleMask = true;
        pthread_mutex_unlock(&ZcbMsg.bridge_mutex);
    }
}

void BridgeDevMgr::RemoveAllDevice()
{
    for (uint16_t i = 0; i < CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT; i++ ) {
        if ( gDevices[i] != NULL) {
            RemoveDevice(gDevices[i]);
        }
    }

    memset(gDevices, 0, sizeof(Device*) * CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT);
    gCurrentEndpointId = gFirstDynamicEndpointId;
}

void BridgeDevMgr::RemoveDevice(Device *dev)
{
    RemoveDeviceEndpoint(dev);
    if ( dev->GetZigbee()->zcb.uSupportedClusters.sClusterBitmap.hasOnOff ) {
        RemoveOnOffNode(static_cast<BridgeOnOff *>(dev));
    }

    if ( dev->GetZigbee()->zcb.uSupportedClusters.sClusterBitmap.hasTemperatureSensing ) {
        RemoveTempMeasurementNode(static_cast<BridgeTempSensor *>(dev));
    }

}

void BridgeDevMgr::RemoveOnOffNode(BridgeOnOff* dev)
{
    delete dev;
    dev = nullptr;
}

void BridgeDevMgr::RemoveTempMeasurementNode(BridgeTempSensor* dev)
{
    dev->DestoryMonitor();
    delete dev;
    dev = nullptr;
}

// -----------------------------------------------------------------------------------------
// Device Management
// -----------------------------------------------------------------------------------------

int BridgeDevMgr::AddDeviceEndpoint(
        Device* dev,
        EmberAfEndpointType* ep,
        const Span<const EmberAfDeviceType> & deviceTypeList,
        const Span<DataVersion> & dataVersionStorage,
#if CHIP_CONFIG_USE_ENDPOINT_UNIQUE_ID
        chip::CharSpan epUniqueId,
#endif
        chip::EndpointId parentEndpointId)
{
    uint8_t index = 0;

    if (dev->IsReachable() == true)
    {
        ChipLogProgress(DeviceLayer, "The endpoints has been added!");
        return -1;
    }

    // mCurrentEndpointId = gFirstDynamicEndpointId;

    while (index < CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT)
    {
        if (nullptr == gDevices[index] )
        {
            gDevices[index] = dev;
            CHIP_ERROR err;
            while (1)
            {
                // Todo: Update this to schedule the work rather than use this lock
                DeviceLayer::StackLock lock;
                dev->SetEndpointId(gCurrentEndpointId);
                dev->SetParentEndpointId(parentEndpointId);
                err =
                    emberAfSetDynamicEndpoint(index, gCurrentEndpointId, ep, dataVersionStorage, deviceTypeList, parentEndpointId);

                if (err == CHIP_NO_ERROR)
                {
                    dev->SetReachable(true);
                    dev->GetZigbee()->zcb.matterIndex = index;
                    newDbSetZcbMapID(&dev->GetZigbee()->zcb, index);
                    newDbSetZcb(&dev->GetZigbee()->zcb);
                    ChipLogProgress(DeviceLayer, "Added device %s Saddr %x to dynamic endpoint %d (index=%d)", dev->GetName(),
                                    dev->GetZigbeeSaddr(), gCurrentEndpointId, index);
                    return index;
                }
                if (err != CHIP_ERROR_ENDPOINT_EXISTS)
                {
                    return -1;
                }
                // Handle wrap condition
                if (++gCurrentEndpointId < gFirstDynamicEndpointId)
                {
                    gCurrentEndpointId = gFirstDynamicEndpointId;
                }
            }
        }
        index++;
    }
    ChipLogProgress(DeviceLayer, "Failed to add dynamic endpoint: No endpoints available!");
    return -1;
}

int BridgeDevMgr::RemoveDeviceEndpoint(Device * dev)
{
    uint8_t index = 0;
    while (index < CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT)
    {
        if (gDevices[index] == dev)
        {
            // Todo: Update this to schedule the work rather than use this lock
            DeviceLayer::StackLock lock;
            // Silence complaints about unused ep when progress logging
            // disabled.
            [[maybe_unused]] EndpointId ep   = emberAfClearDynamicEndpoint(index);
            gDevices[index]                  = nullptr;
            ChipLogProgress(DeviceLayer, "Removed device %s from dynamic endpoint %d (index=%d)", dev->GetName(), ep, index);
            return index;
        }
        index++;
    }
    return -1;
}

// -----------------------------------------------------------------------------------------
// Device callback
// -----------------------------------------------------------------------------------------
void CallReportingCallback(intptr_t closure)
{
    auto path = reinterpret_cast<app::ConcreteAttributePath *>(closure);
    MatterReportingAttributeChangeCallback(*path);
    Platform::Delete(path);
}

void ScheduleReportingCallback(Device * dev, ClusterId cluster, AttributeId attribute)
{
    auto * path = Platform::New<app::ConcreteAttributePath>(dev->GetEndpointId(), cluster, attribute);
    PlatformMgr().ScheduleWork(CallReportingCallback, reinterpret_cast<intptr_t>(path));
}

void HandleDeviceStatusChanged(Device * dev, Device::Changed_t itemChangedMask)
{
    if (itemChangedMask & Device::kChanged_Reachable)
    {
        ScheduleReportingCallback(dev, BridgedDeviceBasicInformation::Id, BridgedDeviceBasicInformation::Attributes::Reachable::Id);
    }

    if (itemChangedMask & Device::kChanged_Name)
    {
        ScheduleReportingCallback(dev, BridgedDeviceBasicInformation::Id, BridgedDeviceBasicInformation::Attributes::NodeLabel::Id);
    }
}

Protocols::InteractionModel::Status HandleReadBridgedDeviceBasicAttribute(Device * dev, chip::AttributeId attributeId, uint8_t * buffer,
                                                    uint16_t maxReadLength)
{
    using namespace BridgedDeviceBasicInformation::Attributes;

    ChipLogProgress(DeviceLayer, "HandleReadBridgedDeviceBasicAttribute: attrId=%d, maxReadLength=%d", attributeId, maxReadLength);

    if ((attributeId == Reachable::Id) && (maxReadLength == 1))
    {
        *buffer = dev->IsReachable() ? 1 : 0;
    }
    else if ((attributeId == NodeLabel::Id) && (maxReadLength == 32))
    {
        MutableByteSpan zclNameSpan(buffer, maxReadLength);
        MakeZclCharString(zclNameSpan, dev->GetName());
    }
    else if ((attributeId == ClusterRevision::Id) && (maxReadLength == 2))
    {
        uint16_t rev = ZCL_BRIDGED_DEVICE_BASIC_INFORMATION_CLUSTER_REVISION;
        memcpy(buffer, &rev, sizeof(rev));
    }
    else if ((attributeId == FeatureMap::Id) && (maxReadLength == 4))
    {
        uint32_t featureMap = ZCL_BRIDGED_DEVICE_BASIC_INFORMATION_FEATURE_MAP;
        memcpy(buffer, &featureMap, sizeof(featureMap));
    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }

    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status HandleReadOnOffAttribute(DeviceOnOff * dev, chip::AttributeId attributeId, uint8_t * buffer, uint16_t maxReadLength)
{
    ChipLogProgress(DeviceLayer, "HandleReadOnOffAttribute: attrId=%d, maxReadLength=%d", attributeId, maxReadLength);
    BridgeOnOff *Light = static_cast<BridgeOnOff *>(dev);

    if ((attributeId == OnOff::Attributes::OnOff::Id) && (maxReadLength == 1))
    {
        Light->GetOnOff();
        if(dev->IsReachable())
        {
            *buffer = dev->IsOn() ? 1 : 0;
        }
        else
        {
            return Protocols::InteractionModel::Status::Failure;
        }
    }
    else if ((attributeId == OnOff::Attributes::ClusterRevision::Id) && (maxReadLength == 2))
    {
        uint16_t rev = ZCL_ON_OFF_CLUSTER_REVISION;
        memcpy(buffer, &rev, sizeof(rev));
    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }

    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status HandleReadTempMeasurementAttribute(DeviceTempSensor * dev, chip::AttributeId attributeId, uint8_t * buffer,
                                                 uint16_t maxReadLength)
{
    using namespace TemperatureMeasurement::Attributes;

    if ((attributeId == MeasuredValue::Id) && (maxReadLength == 2))
    {
        int16_t measuredValue = dev->GetMeasuredValue();
        memcpy(buffer, &measuredValue, sizeof(measuredValue));
    }
    else if ((attributeId == MinMeasuredValue::Id) && (maxReadLength == 2))
    {
        int16_t minValue = dev->mMin;
        memcpy(buffer, &minValue, sizeof(minValue));
    }
    else if ((attributeId == MaxMeasuredValue::Id) && (maxReadLength == 2))
    {
        int16_t maxValue = dev->mMax;
        memcpy(buffer, &maxValue, sizeof(maxValue));
    }
    else if ((attributeId == FeatureMap::Id) && (maxReadLength == 4))
    {
        uint32_t featureMap = ZCL_TEMPERATURE_SENSOR_FEATURE_MAP;
        memcpy(buffer, &featureMap, sizeof(featureMap));
    }
    else if ((attributeId == ClusterRevision::Id) && (maxReadLength == 2))
    {
        uint16_t clusterRevision = ZCL_TEMPERATURE_SENSOR_CLUSTER_REVISION;
        memcpy(buffer, &clusterRevision, sizeof(clusterRevision));
    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }

    return Protocols::InteractionModel::Status::Success;
}

void BridgeDevMgr::HandleDeviceOnOffStatusChanged(DeviceOnOff * dev, DeviceOnOff::Changed_t itemChangedMask)
{
    if (itemChangedMask & (DeviceOnOff::kChanged_Reachable | DeviceOnOff::kChanged_Name | DeviceOnOff::kChanged_Location))
    {
        HandleDeviceStatusChanged(static_cast<Device *>(dev), (Device::Changed_t) itemChangedMask);
    }

    if (itemChangedMask & DeviceOnOff::kChanged_OnOff)
    {
        ScheduleReportingCallback(dev, OnOff::Id, OnOff::Attributes::OnOff::Id);
    }
}

void BridgeDevMgr::HandleDeviceTempSensorStatusChanged(DeviceTempSensor * dev, DeviceTempSensor::Changed_t itemChangedMask)
{
    if (itemChangedMask &
        (DeviceTempSensor::kChanged_Reachable | DeviceTempSensor::kChanged_Name | DeviceTempSensor::kChanged_Location))
    {
        HandleDeviceStatusChanged(static_cast<Device *>(dev), (Device::Changed_t) itemChangedMask);
    }
    if (itemChangedMask & DeviceTempSensor::kChanged_MeasurementValue)
    {
        ScheduleReportingCallback(dev, TemperatureMeasurement::Id, TemperatureMeasurement::Attributes::MeasuredValue::Id);
    }
}


Protocols::InteractionModel::Status HandleWriteOnOffAttribute(DeviceOnOff * dev, chip::AttributeId attributeId, uint8_t * buffer)
{
    ChipLogProgress(DeviceLayer, "HandleWriteOnOffAttribute: attrId=%d", attributeId);
    BridgeOnOff *Light = static_cast<BridgeOnOff *>(dev);

    if ((attributeId == OnOff::Attributes::OnOff::Id) && (dev->IsReachable()))
    {
        if (*buffer)
        {
            Light->SetOnOff(true, true);
        }
        else
        {
            Light->SetOnOff(false, true);
        }
    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }

    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status emberAfExternalAttributeReadCallback(EndpointId endpoint, ClusterId clusterId,
                                                   const EmberAfAttributeMetadata * attributeMetadata, uint8_t * buffer,
                                                   uint16_t maxReadLength)
{
    uint16_t endpointIndex = emberAfGetDynamicIndexFromEndpoint(endpoint);

    Protocols::InteractionModel::Status ret = Protocols::InteractionModel::Status::Failure;

    if ((endpointIndex < CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT) && (BridgeDevMgr::gDevices[endpointIndex] != nullptr))
    {
        Device * dev = BridgeDevMgr::gDevices[endpointIndex];

        if (clusterId == BridgedDeviceBasicInformation::Id)
        {
            ret = HandleReadBridgedDeviceBasicAttribute(dev, attributeMetadata->attributeId, buffer, maxReadLength);
        }
        else if (clusterId == OnOff::Id)
        {
            ret = HandleReadOnOffAttribute(static_cast<DeviceOnOff *>(dev), attributeMetadata->attributeId, buffer, maxReadLength);
        }
        else if (clusterId == TemperatureMeasurement::Id)
        {
            ret = HandleReadTempMeasurementAttribute(static_cast<DeviceTempSensor *>(dev), attributeMetadata->attributeId, buffer,
                                                     maxReadLength);
        }
    }

    return ret;
}

Protocols::InteractionModel::Status emberAfExternalAttributeWriteCallback(EndpointId endpoint, ClusterId clusterId,
                                                    const EmberAfAttributeMetadata * attributeMetadata, uint8_t * buffer)
{
    uint16_t endpointIndex = emberAfGetDynamicIndexFromEndpoint(endpoint);

    Protocols::InteractionModel::Status ret = Protocols::InteractionModel::Status::Failure;

    ChipLogProgress(DeviceLayer, "emberAfExternalAttributeWriteCallback: ep=%d endpointIndex=%d", endpoint,endpointIndex);

    if (endpointIndex < CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT)
    {
        Device * dev = BridgeDevMgr::gDevices[endpointIndex];

        if ((dev->IsReachable()) && (clusterId == OnOff::Id))
        {
            ret = HandleWriteOnOffAttribute(static_cast<DeviceOnOff *>(dev), attributeMetadata->attributeId, buffer);
        }

    }

    return ret;
}


// -----------------------------------------------------------------------------------------
//  zcb node report attribute to Bridge
// -----------------------------------------------------------------------------------------
bool BridgeDevMgr::WriteAttributeToDynamicEndpoint(newdb_zcb_t zcb, uint16_t u16ClusterID, uint16_t u16AttributeID, uint64_t u64Data, uint8_t u8DataType)
{
    if ( gDevices[zcb.matterIndex] == NULL) {
        ChipLogProgress(DeviceLayer, "Not found the device !");
        return false;
    }

    switch(u16ClusterID) {
    case E_ZB_CLUSTERID_ONOFF:{
        BridgeOnOff *Light = static_cast<BridgeOnOff *>(gDevices[zcb.matterIndex]);
        if (Light->IsReachable() == false)
            Light->SetReachable(true);
        Light->SetOnOff(static_cast<bool>(u64Data), true);
        return true;
    }

    case E_ZB_CLUSTERID_MEASUREMENTSENSING_TEMP: {
        BridgeTempSensor *TempSensor = static_cast<BridgeTempSensor *>(gDevices[zcb.matterIndex]);
        if (TempSensor->IsReachable() == false)
            TempSensor->SetReachable(true);
        TempSensor->SetMeasuredValue(static_cast<int16_t>(u64Data));
        return true;
    }

    default:
        ChipLogProgress(DeviceLayer, "Got attribute 0x%04x in cluster 0x%04x, but not writed",
                                                                            u16AttributeID, u16ClusterID);
        break;
    }

    return false;
}