/*
 *
 *    Copyright (c) 2021-2022 Project CHIP Authors
 *    Copyright (c) 2019 Google LLC.
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

#include "BridgeDev.h"

#include <crypto/RandUtils.h>
#include <cstdio>
#include <platform/CHIPDeviceLayer.h>

#include <string>
#include <sys/types.h>

using namespace chip;
using namespace chip::app::Clusters::Actions;

// -----------------------------------------------------------------------------------------
// BridgeOnOff
// -----------------------------------------------------------------------------------------
BridgeOnOff::BridgeOnOff( 
            const char*  szDeviceName, 
            std::string  szLocation, 
            ZigbeeDev_t* ZigbeeDev,
            size_t       ClusterSize) : DeviceOnOff(szDeviceName, szLocation)
{
    if (ZigbeeDev == nullptr) {
        throw std::invalid_argument("BridgeOnOff: ZigbeeDev is null");
    }

    this->SetZigbee(*ZigbeeDev);
    DataVersions = new DataVersion[ClusterSize];
}

BridgeOnOff::~BridgeOnOff()
{
    delete[] DataVersions;
}


void BridgeOnOff::GetOnOff()
{
    newdb_zcb_t zcb;
    newDbGetZcbSaddr(this->GetZigbeeSaddr(), &zcb);

    if( eReadOnoff( uint16_t(zcb.saddr)) == 0)
    {
        this->SetReachable(true);
        if ( strcmp(zcb.info, "off") == 0) {
            mOn = false;
        } else {
            mOn =true;
        }
    } else {
        this->SetReachable(false);
    }
}


void BridgeOnOff::SetOnOff(bool aOn, bool Sync)
{
    int result;
    bool changed;
    struct timespec ts;

    if (!Sync) {
        goto done;
    }

    clock_gettime(CLOCK_REALTIME, &ts);
    // timeout time is 2s
    ts.tv_sec += 2;

    changed = aOn ^ mOn;

    if (changed)
    {
        if(eOnOff(uint16_t(this->GetZigbeeSaddr()), aOn) != 0)
        {
            ChipLogProgress(DeviceLayer, "Send Device[%s]: %s cmd Failed", mName, aOn ? "ON" : "OFF");
            aOn = !aOn;
            goto done;
        }

        pthread_mutex_lock(&device_mutex);
        while(mOn != aOn) {
            result = pthread_cond_timedwait(&device_cond, &device_mutex, &ts);
            if(result == ETIMEDOUT) {
                ChipLogProgress(DeviceLayer, "Timeout waiting for response from Device[%s]", mName);
                SetReachable(false);
                break;
            } else {
                ChipLogProgress(DeviceLayer, "Set Device[%s]: Success", mName);
            }
        }
        pthread_mutex_unlock(&device_mutex);
    }

done:
    DeviceOnOff::SetOnOff(aOn);
    ChipLogProgress(DeviceLayer, "Device[%s]: %s", mName, mOn ? "ON" : "OFF");
}


// -----------------------------------------------------------------------------------------
// BridgeTempSensor
// -----------------------------------------------------------------------------------------
BridgeTempSensor::BridgeTempSensor(
        const char * szDeviceName, 
        std::string  szLocation,
        ZigbeeDev_t* ZigbeeDev,
        int16_t      min, 
        int16_t      max, 
        int16_t      measuredValue,
        size_t       ClusterSize 
    ): DeviceTempSensor(szDeviceName, szLocation, min, max, measuredValue)
{
    if (ZigbeeDev == nullptr) {
        throw std::invalid_argument("BridgeTempSensor: ZigbeeDev is null");
    }

    this->SetZigbee(*ZigbeeDev);
    DataVersions = new DataVersion[ClusterSize];
}

BridgeTempSensor::~BridgeTempSensor()
{
    delete[] DataVersions;
}

int BridgeTempSensor::StartMonitor(void)
{
    int res = pthread_create(&Monitor_thread, nullptr, Monitor, (void*)this);
    if (res)
    {
        printf("Error creating TempSensorDevice[%s] Monitor: %d\n", mName, res);
        return -1;
    }

    return 0;
}

int BridgeTempSensor::DestoryMonitor(void)
{
    pthread_cancel(Monitor_thread);
    if(pthread_join(Monitor_thread, NULL) == 0)
    {
        printf("[%s] Monitor exit !\n", mName);
    }

    return 0;
}

void* BridgeTempSensor::Monitor(void *context)
{
    BridgeTempSensor *Sensor = static_cast<BridgeTempSensor*>(context);

    int result;
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += Sensor->timeout;

    while( 1 ) {
        pthread_mutex_lock(&Sensor->device_mutex);
        while(Sensor->mReachable == true) {
            result = pthread_cond_timedwait(&Sensor->device_cond, &Sensor->device_mutex, &ts);
            if(result == ETIMEDOUT) {
                Sensor->SetReachable(false);
            } else {
                clock_gettime(CLOCK_REALTIME, &ts);
                ts.tv_sec += Sensor->timeout;
            }
        }

        while(Sensor->mReachable == false) {
            result = pthread_cond_wait(&Sensor->device_cond, &Sensor->device_mutex);
            if(result == 0) {
                Sensor->SetReachable(true);
                clock_gettime(CLOCK_REALTIME, &ts);
                ts.tv_sec += Sensor->timeout;
            }
        }
        pthread_mutex_unlock(&Sensor->device_mutex);
    }

}