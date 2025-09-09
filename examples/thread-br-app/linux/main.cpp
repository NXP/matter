/*
 *    Copyright (c) 2023 Project CHIP Authors
 *    Copyright 2025 NXP
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

#include <thread-br-delegate-impl.h>
#include <app/clusters/thread-border-router-management-server/thread-border-router-management-server.h>
#include <AppMain.h>
#include <lib/core/CHIPSafeCasts.h>
#include <lib/support/CodeUtils.h>
#include <lib/support/Span.h>

#include <optional>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;

ByteSpan ByteSpanFromCharSpan(CharSpan span)
{
    return ByteSpan(Uint8::from_const_char(span.data()), span.size());
}

void ApplicationInit() {}

void ApplicationShutdown() {}

int main(int argc, char * argv[])
{
    VerifyOrReturnValue(ChipLinuxAppInit(argc, argv) == 0, -1);
    ChipLinuxAppMainLoop();
    return 0;
}

std::optional<ThreadBorderRouterManagement::ServerInstance> gThreadBorderRouterManagementServer;
ThreadBorderRouterManagement::ThreadBorderRouterDelegate gThreadBorderRouterDelegate{};

void emberAfThreadBorderRouterManagementClusterInitCallback(EndpointId endpoint)
{
    VerifyOrDie(!gThreadBorderRouterManagementServer);
    gThreadBorderRouterManagementServer.emplace(endpoint, &gThreadBorderRouterDelegate, Server::GetInstance().GetFailSafeContext())
        .Init();
}
