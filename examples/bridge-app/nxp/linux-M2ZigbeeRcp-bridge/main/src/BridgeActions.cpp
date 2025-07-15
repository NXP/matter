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

#include <app/EventLogging.h>
#include <syslog.h>
#include <stdio.h>

#include "BridgeActions.h"

using namespace chip;
using namespace chip::app;
using namespace chip::Credentials;
using namespace chip::Inet;
using namespace chip::Transport;
using namespace chip::DeviceLayer;
using namespace chip::app::Clusters;

#define ACTION_NUM 4

BridgeActions::BridgeActions()
{
    ActionList.clear();
}

BridgeActions::~BridgeActions()
{

}

void BridgeActions::regist()
{
    Action *actions[ACTION_NUM];

    actions[0] = new Action(0x1001, "Start Network", Actions::ActionTypeEnum::kAutomation, 0xE001, 0x1, Actions::ActionStateEnum::kInactive, true);
    actions[1] = new Action(0x1002, "Permit Join Start", Actions::ActionTypeEnum::kAutomation, 0xE002, 0x1, Actions::ActionStateEnum::kInactive, true);
    actions[2] = new Action(0x1003, "Permit Join Stop", Actions::ActionTypeEnum::kAutomation, 0xE002, 0x1, Actions::ActionStateEnum::kInactive, true);
    actions[3] = new Action(0x1004, "Factory Reset", Actions::ActionTypeEnum::kAutomation, 0xE003, 0x1, Actions::ActionStateEnum::kInactive, true);

    for(int i = 0; i < ACTION_NUM; i++ ) {
        ActionList.push_back(actions[i]);
    }
}

void BridgeActions::unregist()
{
    for (auto it = ActionList.begin(); it != ActionList.end(); it++) {
	    if (*it != NULL) {
		    delete *it;
		    *it = NULL;
		}
	}
}

int BridgeActions::handle(uint16_t actionID, EndpointId endpointID, uint32_t invokeID, bool hasInvokeID, BridgeDevMgr* gDevMgr)
{
    syslog(LOG_INFO, "%s: BridgeActions::handle: actionID: 0x%x endpointID: 0x%x ", __FUNCTION__, actionID, endpointID);
    
    if (actionID == ActionList[0]->getActionId() && ActionList[0]->getIsVisible())
    {
        StartNetwork( true, endpointID, actionID, invokeID, hasInvokeID);
        return 1;
    }

    if (actionID == ActionList[1]->getActionId() && ActionList[1]->getIsVisible())
    {
        PermitJoinAction( true, endpointID, actionID, invokeID, hasInvokeID);
        return 1;
    }

    if (actionID == ActionList[2]->getActionId() && ActionList[1]->getIsVisible())
    {
        PermitJoinAction( false, endpointID, actionID, invokeID, hasInvokeID);
        return 1;
    }

    if (actionID == ActionList[3]->getActionId() && ActionList[2]->getIsVisible())
    {
        FactoryReset( true, endpointID, actionID, invokeID, hasInvokeID, gDevMgr);
        return 1;
    }

    return 0;
}
void BridgeActions::StartNetwork(bool actionOn, EndpointId endpointId, uint16_t actionID, uint32_t invokeID, bool hasInvokeID)
{
    if (hasInvokeID)
    {
        Actions::Events::StateChanged::Type event{ actionID, invokeID, Actions::ActionStateEnum::kActive };
        EventNumber eventNumber;
        chip::app::LogEvent(event, endpointId, eventNumber);
    }

    zboss_start_continue();

    if (hasInvokeID)
    {
        Actions::Events::StateChanged::Type event{ actionID, invokeID, Actions::ActionStateEnum::kInactive };
        EventNumber eventNumber;
        chip::app::LogEvent(event, endpointId, eventNumber);
    }
}

void BridgeActions::PermitJoinAction(bool actionOn, EndpointId endpointId, uint16_t actionID, uint32_t invokeID, bool hasInvokeID)
{
    if (hasInvokeID)
    {
        Actions::Events::StateChanged::Type event{ actionID, invokeID, Actions::ActionStateEnum::kActive };
        EventNumber eventNumber;
        chip::app::LogEvent(event, endpointId, eventNumber);
    }

    // Open Bridge permit join
    syslog(LOG_INFO, "%s: actionOn: 0x%x endpointId: 0x%x actionID: 0x%x ", __FUNCTION__, actionOn, endpointId, actionID);
    if(actionOn)
    {
        m2z_schedule_request_bdb_start_commissioning();
    }
    else
    {
        m2z_schedule_request_close_network();
    }
    //ePermitJoinOn(0xFF);

    if (hasInvokeID)
    {
        Actions::Events::StateChanged::Type event{ actionID, invokeID, Actions::ActionStateEnum::kInactive };
        EventNumber eventNumber;
        chip::app::LogEvent(event, endpointId, eventNumber);
    }
}

void BridgeActions::FactoryReset(bool actionOn, EndpointId endpointId, uint16_t actionID, uint32_t invokeID, bool hasInvokeID, BridgeDevMgr* gDevMgr)
{
    if (hasInvokeID)
    {
        Actions::Events::StateChanged::Type event{ actionID, invokeID, Actions::ActionStateEnum::kActive };
        EventNumber eventNumber;
        chip::app::LogEvent(event, endpointId, eventNumber);
    }

    //eFactoryNew();

    if (hasInvokeID)
    {
        Actions::Events::StateChanged::Type event{ actionID, invokeID, Actions::ActionStateEnum::kInactive };
        EventNumber eventNumber;
        chip::app::LogEvent(event, endpointId, eventNumber);
    }

}
