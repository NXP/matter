/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2021-2023 Google LLC.
 *    Copyright 2024 NXP
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

#if CONFIG_APP_FREERTOS_OS
#include "AppTaskFreeRTOS.h"
#else
#include "AppTaskZephyr.h"
#endif

#include "LightingManager.h"
#include "FreeRTOS.h"
#include "timers.h"
#include <platform/CHIPDeviceLayer.h>

namespace LightingApp{
#if CONFIG_APP_FREERTOS_OS
class AppTask : public chip::NXP::App::AppTaskFreeRTOS
#else
class AppTask : public chip::NXP::App::AppTaskZephyr
#endif
{
public:
    ~AppTask() override{};
    void PostInitMatterStack(void) override;
    void PreInitMatterStack(void) override;
	void AppMatter_RegisterCustomCliCommands(void) override;
    // This returns an instance of this class.
    static AppTask & GetDefaultInstance();
	void UpdateClusterState(void);

private:
    static AppTask sAppTask;
	
	static void ActionInitiated(LightingManager::Action_t aAction, int32_t aActor);
	static void ActionCompleted(LightingManager::Action_t aAction);
	
	enum Function_t
    {
        kFunction_NoneSelected   = 0,
        kFunction_SoftwareUpdate = 0,
        kFunction_FactoryReset,
        kFunctionTurnOnTurnOff,

        kFunction_Invalid
    } Function;

    Function_t mFunction;
};
} // namespace LightingApp

/**
 * Returns the application-specific implementation of the AppTaskBase object.
 *
 * Applications can use this to gain access to features of the AppTaskBase
 * that are specific to the selected application.
 */
chip::NXP::App::AppTaskBase & GetAppTask();
