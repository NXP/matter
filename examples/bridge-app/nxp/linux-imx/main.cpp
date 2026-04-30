/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
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

#include <AppMain.h>
#include <platform/CHIPDeviceLayer.h>
#include <platform/PlatformManager.h>

#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app/AttributeAccessInterfaceRegistry.h>
#include <app/ConcreteAttributePath.h>
#include <app/EventLogging.h>
#include <app/reporting/reporting.h>
#include <app/util/af-types.h>
#include <app/util/attribute-storage.h>
#include <app/util/endpoint-config-api.h>
#include <app/util/util.h>
#include <credentials/DeviceAttestationCredsProvider.h>
#include <credentials/examples/DeviceAttestationCredsExample.h>
#include <lib/core/CHIPError.h>
#include <lib/support/CHIPMem.h>
#include <lib/support/ZclString.h>
#include <platform/CommissionableDataProvider.h>
#include <setup_payload/QRCodeSetupPayloadGenerator.h>
#include <setup_payload/SetupPayload.h>

#include <pthread.h>
#include <sys/ioctl.h>

#include "CommissionableInit.h"
#include "Device.h"
#include "main.h"
#include <app/server/Server.h>

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "zcb.h"
#include "cmd.h"
#include "Bridge.h"

using namespace chip;
using namespace chip::app;
using namespace chip::Credentials;
using namespace chip::Inet;
using namespace chip::Transport;
using namespace chip::DeviceLayer;
using namespace chip::app::Clusters;

#define SERIAL_PORT       "/dev/ttyUSB0"
#define SERIAL_BAUDRATE   1000000
#define POLL_INTERVAL_MS (100)

int verbosity = 11;        // zcb log level
uint8_t poll_prescale = 0;

// NamedPipeCommands sChipNamedPipeCommands;
// BridgeCommandDelegate sBridgeCommandDelegate;
// BridgedPowerSourceAttrAccess gPowerAttrAccess;

bool kbhit()
{
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}

void * bridge_polling_thread(void * context)
{
    Bridge* bridge = (Bridge *)context;

    while (1)
    {
        if (kbhit())
        {
            int ch = getchar();

            switch (ch)
            {
                case '1': {
                    ePermitJoinOn(0xFF);
                    printf("permit join done ! \n");
                }
                break;

                case '2': {
                    newDbPrintDevices();
                }
                break;

                case '3': {
                    eFactoryNew();
                    // bridge->test();
                }
                break;

                case 'q': {
                    delete bridge;
                    chip::Server::GetInstance().Shutdown();
                    chip::DeviceLayer::PlatformMgr().StopEventLoopTask();
                    chip::DeviceLayer::PlatformMgr().Shutdown();
                    return NULL;
                }

                default:
                    break;
            }
        }

        // Sleep to avoid tight loop reading commands
        usleep(POLL_INTERVAL_MS * 1000);
    }

    return NULL;
}

void ApplicationInit()
{
    // std::string path = std::string(LinuxDeviceOptions::GetInstance().app_pipe);

    // if ((!path.empty()) and (sChipNamedPipeCommands.Start(path, &sBridgeCommandDelegate) != CHIP_NO_ERROR))
    // {
    //     ChipLogError(NotSpecified, "Failed to start CHIP NamedPipeCommands");
    //     sChipNamedPipeCommands.Stop();
    // }

    // AttributeAccessInterfaceRegistry::Instance().Register(&gPowerAttrAccess);

    Bridge* bridge = new Bridge(SERIAL_PORT, SERIAL_BAUDRATE);
    if ( bridge->Init() != 0)
        return;

    bridge->ServiceStart();

    {
        pthread_t poll_thread;
        int res = pthread_create(&poll_thread, nullptr, bridge_polling_thread, bridge);
        if (res)
        {
            printf("Error creating polling thread: %d\n", res);
            exit(1);
        }
    }
}

void ApplicationShutdown() {}

int main(int argc, char * argv[])
{
    if (ChipLinuxAppInit(argc, argv) != 0)
    {
        return -1;
    }

    ChipLinuxAppMainLoop();
    return 0;
}