/*
 *
 *    Copyright (c) 2021-2023 Project CHIP Authors
 *    Copyright (c) 2021 Google LLC.
 *    Copyright 2023-2024 NXP
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

#include "AppTask.h"
#include "CHIPDeviceManager.h"
#include "ICDUtil.h"
#include <app/InteractionModelEngine.h>
#include <app/util/attribute-storage.h>

#if CHIP_DEVICE_CONFIG_ENABLE_CHIPOBLE
#include "BLEApplicationManager.h"
#endif

using namespace chip;

void ThermostatApp::AppTask::PreInitMatterStack()
{
    ChipLogProgress(DeviceLayer, "Welcome to NXP thermostat Demo App");
}

void ThermostatApp::AppTask::PostInitMatterStack()
{
#if CHIP_DEVICE_CONFIG_ENABLE_CHIPOBLE
#ifdef  APP_BT_DEVICE_NAME
    chip::DeviceLayer::ConnectivityMgr().SetBLEDeviceName(APP_BT_DEVICE_NAME);
#endif
    /* BLEApplicationManager implemented per platform or left blank */
    chip::NXP::App::BleAppMgr().Init();
#endif
    chip::app::InteractionModelEngine::GetInstance()->RegisterReadHandlerAppCallback(&chip::NXP::App::GetICDUtil());
}

// This returns an instance of this class.
ThermostatApp::AppTask & ThermostatApp::AppTask::GetDefaultInstance()
{
    static ThermostatApp::AppTask sAppTask;
    return sAppTask;
}

chip::NXP::App::AppTaskBase & chip::NXP::App::GetAppTask()
{
    return ThermostatApp::AppTask::GetDefaultInstance();
}
