/*
 *
 *    Copyright (c) 2025 Project CHIP Authors
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
#pragma once

#include <pthread.h>

#include "Device.h"
#include "newDb.h"
#include "zcb.h"

using namespace chip;
using namespace chip::app;

class BridgeOnOff : public DeviceOnOff
{
public:
    BridgeOnOff(const char*  szDeviceName, 
                std::string  szLocation, 
                ZigbeeDev_t* ZigbeeDev,
                size_t       ClusterSize
            );
    ~BridgeOnOff();

    DataVersion *DataVersions;

    void GetOnOff();
    void SetOnOff(bool aOn, bool Sync);  //Sync state with real device
};


class BridgeTempSensor : public DeviceTempSensor
{
public:
    BridgeTempSensor(
        const char * szDeviceName,
        std::string  szLocation,
        ZigbeeDev_t* ZigbeeDev,
        int16_t      min, 
        int16_t      max, 
        int16_t      measuredValue,
        size_t       ClusterSize
    );
    ~BridgeTempSensor();

    int StartMonitor(void);
    int DestoryMonitor(void);

    int timeout;
    DataVersion *DataVersions;

private:
    pthread_t    Monitor_thread;
    static void* Monitor(void *context);
};