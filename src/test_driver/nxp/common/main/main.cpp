/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
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

#include <platform/CHIPDeviceLayer.h>
#include <lib/support/UnitTestRegistration.h>
#include <nlunit-test.h>
#include <lib/support/CHIPMem.h>
#include <lib/support/CHIPPlatformMemory.h>
#include <platform/CHIPDeviceLayer.h>
#include <platform/KeyValueStoreManager.h>
#include <mbedtls/platform.h>

#if configAPPLICATION_ALLOCATED_HEAP
uint8_t __attribute__((section(".heap"))) ucHeap[configTOTAL_HEAP_SIZE];
#endif

#ifndef MAIN_TASK_SIZE
#define MAIN_TASK_SIZE ((configSTACK_DEPTH_TYPE)24576 / sizeof(portSTACK_TYPE))
#endif

using namespace ::chip::DeviceLayer;

void main_task(void *pvParameters)
{
    chip::Platform::MemoryInit();
    chip::DeviceLayer::PlatformManagerImpl().ServiceInit();

    chip::RunRegisteredUnitTests();
}


extern "C" int main(int argc, char * argv[])
{
    TaskHandle_t taskHandle;

    PlatformMgrImpl().HardwareInit();

    if (xTaskCreate(&main_task, "main_task", MAIN_TASK_SIZE, NULL, configMAX_PRIORITIES - 4, &taskHandle) != pdPASS)
    {
        ChipLogError(DeviceLayer, "Failed to start main task");
        assert(false);
    }

    ChipLogProgress(DeviceLayer, "Starting FreeRTOS scheduler");
    vTaskStartScheduler();
}
