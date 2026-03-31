// Copyright 2024 NXP
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "api_handlers/eevse_handler.h"
#include "common.h"

#include <thread>
#include <chrono>
#include <sstream>

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <crow/json.h>
#include <lib/support/logging/CHIPLogging.h>

using namespace boost::property_tree;

namespace api_handlers {

crow::response handleEventTrigger(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        auto nodeAlias = std::string(x_body_decoded["nodeAlias"].s());
        auto nodeId = std::string(x_body_decoded["nodeId"].s());
        auto key = std::string(x_body_decoded["key"].s());
        auto type = std::string(x_body_decoded["type"].s());
        ChipLogError(NotSpecified, "Received event trigger POST request for device with Node ID: %s", std::string(nodeId).c_str());
        std::string command;
        if (type == "triggerBasic") {
            command = "generaldiagnostics test-event-trigger hex:" + key  + " 0x0099000000000000 " + nodeId + " 0";
        } else if (type == "triggerBasicClear") {
            command = "generaldiagnostics test-event-trigger hex:" + key  + " 0x0099000000000001 " + nodeId + " 0";
        } else if (type == "triggerPluggedin") {
            command = "generaldiagnostics test-event-trigger hex:" + key  + " 0x0099000000000002 " + nodeId + " 0";
        } else if (type == "triggerPluggedinClear") {
            command = "generaldiagnostics test-event-trigger hex:" + key  + " 0x0099000000000003 " + nodeId + " 0";
        } else if (type == "triggerChargeDemand") {
            command = "generaldiagnostics test-event-trigger hex:" + key  + " 0x0099000000000004 " + nodeId + " 0";
        } else if (type == "triggerChargeDemandClear") {
            command = "generaldiagnostics test-event-trigger hex:" + key  + " 0x0099000000000005 " + nodeId + " 0";
        }
        wsClient.sendMessage(command);
        ChipLogError(NotSpecified, "Send general diagnostics event trigger command to chip-tool ws server");
        int sleepTime = 0;
        while (reportQueue.empty() && sleepTime < 20)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            sleepTime++;
        }
        if (sleepTime == 20) {
            root.put("result", RESPONSE_FAILURE);
            ChipLogError(NotSpecified, "Execute general diagnostics event trigger command overtime!");
        } else {
            Json::Value resultsReport = wsClient.dequeueReport();
            Json::Value resultsValue = resultsReport[0];
            if (resultsValue.isMember("error"))
            {
                root.put("result", RESPONSE_FAILURE);
                ChipLogError(NotSpecified, "Execute general diagnostics event trigger command failed!");
            } else {
                root.put("result", RESPONSE_SUCCESS);
                ChipLogError(NotSpecified, "Execute general diagnostics event trigger command successfully");
            }
        }
        std::stringstream ss;
        write_json(ss, root);
        std::string strContent = ss.str();
        crow::response response(strContent);
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    } catch (const std::exception & e)
    {
        crow::response response(400, e.what());
        ChipLogError(NotSpecified, "Error on event_trigger: %s", e.what());
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    }
}

crow::response handleEevseControl(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        auto nodeAlias = std::string(x_body_decoded["nodeAlias"].s());
        auto nodeId = std::string(x_body_decoded["nodeId"].s());
        auto endPointId = std::string(x_body_decoded["endPointId"].s());
        auto type = std::string(x_body_decoded["type"].s());
        ChipLogError(NotSpecified, "Received EEVSE control POST request for device with Node ID: %s, End Point ID: %s",
            std::string(nodeId).c_str(), std::string(endPointId).c_str());
        std::string command;
        if (type == "enablecharging") {
            auto chargingEnabledUntil = std::string(x_body_decoded["chargingEnabledUntil"].s());
            auto minimumChargeCurrent = std::string(x_body_decoded["minimumChargeCurrent"].s());
            auto maximumChargeCurrent = std::string(x_body_decoded["maximumChargeCurrent"].s());
            command = "energyevse enable-charging " + chargingEnabledUntil + " " + minimumChargeCurrent + " " + maximumChargeCurrent + " "
                        + nodeId + " " + endPointId + " --timedInteractionTimeoutMs 3000";
        } else if (type == "write") {
            auto userMaximumChargeCurrent = std::string(x_body_decoded["userMaximumChargeCurrent"].s());
            command = "energyevse write user-maximum-charge-current " + userMaximumChargeCurrent + " " + nodeId + " " + endPointId;
        } else if (type == "disable") {
            command = "energyevse disable " + nodeId + " " + endPointId + " --timedInteractionTimeoutMs 3000";
        }
        wsClient.sendMessage(command);
        ChipLogError(NotSpecified, "Send eevse control command to chip-tool ws server");
        int sleepTime = 0;
        while (reportQueue.empty() && sleepTime < 20)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            sleepTime++;
        }
        if (sleepTime == 20) {
            root.put("result", RESPONSE_FAILURE);
            ChipLogError(NotSpecified, "Execute eevse control command overtime!");
        } else {
            Json::Value resultsReport = wsClient.dequeueReport();
            Json::Value resultsValue = resultsReport[0];
            if (resultsValue.isMember("error"))
            {
                root.put("result", RESPONSE_FAILURE);
                ChipLogError(NotSpecified, "Execute eevse control command failed!");
            } else {
                root.put("result", RESPONSE_SUCCESS);
                ChipLogError(NotSpecified, "Execute eevse control command successfully");
            }
        }
        std::stringstream ss;
        write_json(ss, root);
        std::string strContent = ss.str();
        crow::response response(strContent);
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    } catch (const std::exception & e)
    {
        crow::response response(400, e.what());
        ChipLogError(NotSpecified, "Error on eevse_control: %s", e.what());
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    }
}

crow::response handleEevseRead(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        auto nodeAlias = std::string(x_body_decoded["nodeAlias"].s());
        auto nodeId = std::string(x_body_decoded["nodeId"].s());
        auto endPointId = std::string(x_body_decoded["endPointId"].s());
        auto type = std::string(x_body_decoded["type"].s());
        ChipLogError(NotSpecified, "Received EEVSE read POST request for device with Node ID: %s, End Point ID: %s",
            std::string(nodeId).c_str(), std::string(endPointId).c_str());
        std::string command;
        if (type == "state") {
            command = "energyevse read state " + nodeId + " " + endPointId;
        } else if (type == "supplystate") {
            command = "energyevse read supply-state " + nodeId + " " + endPointId;
        } else if (type == "faultstate") {
            command = "energyevse read fault-state " + nodeId + " " + endPointId;
        } else if (type == "chargingenableduntil") {
            command = "energyevse read charging-enabled-until " + nodeId + " " + endPointId;
        } else if (type == "minimumchargecurrent") {
            command = "energyevse read minimum-charge-current " + nodeId + " " + endPointId;
        } else if (type == "maximumchargecurrent") {
            command = "energyevse read maximum-charge-current " + nodeId + " " + endPointId;
        } else if (type == "sessionid") {
            command = "energyevse read session-id " + nodeId + " " + endPointId;
        } else if (type == "sessionduration") {
            command = "energyevse read session-duration " + nodeId + " " + endPointId;
        }
        wsClient.sendMessage(command);
        ChipLogError(NotSpecified, "Send eevse read command to chip-tool ws server");
        int sleepTime = 0;
        while (reportQueue.empty() && sleepTime < 20)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            sleepTime++;
        }
        if (sleepTime == 20) {
            root.put("result", RESPONSE_FAILURE);
            ChipLogError(NotSpecified, "Execute eevse read command overtime!");
        } else {
            Json::Value resultsReport = wsClient.dequeueReport();
            Json::Value resultsValue = resultsReport[0];
            if (!resultsValue.isMember("error") && resultsValue.isMember("value") )
            {
                std::string report_text;
                std::stringstream report_ss;
                std::string value;
                if (type == "state") {
                    switch (resultsValue["value"].asInt()) {
                        case 0:
                            value = "NotPluggedIn";
                            break;
                        case 1:
                            value = "PluggedInNoDemand";
                            break;
                        case 2:
                            value = "PluggedInDemand";
                            break;
                        case 3:
                            value = "PluggedInCharging";
                            break;
                        case 6:
                            value = "Fault";
                            break;
                        default:
                            value = "Other";
                    }
                } else if (type == "supplystate") {
                    switch (resultsValue["value"].asInt()) {
                        case 0:
                            value = "Disabled";
                            break;
                        case 1:
                            value = "ChargingEnabled";
                            break;
                        case 3:
                            value = "DisabledError";
                            break;
                        case 4:
                            value = "DisabledDiagnostics";
                            break;
                        default:
                            value = "Other";
                    }
                } else if (type == "faultstate") {
                    switch (resultsValue["value"].asInt()) {
                        case 0:
                            value = "NoError";
                            break;
                        default:
                            value = "Other";
                    }
                } else if (type == "chargingenableduntil") {
                    if (resultsValue["value"].asString().empty()) {
                        value = "AlwaysEnabled";
                    } else {
                        value = resultsValue["value"].asString();
                    }
                } else {
                    value = resultsValue["value"].asString();
                }
                report_ss << "Report from " << nodeAlias << " " << nodeId << ": " << resultsValue["endpointId"] << ". "
                        << "Cluster: " << resultsValue["clusterId"] << "\r\n\r\n" << type << ": " << value;
                report_text = report_ss.str();
                root.put("report", report_text);
                ChipLogError(NotSpecified, "Generated eevse report successfully: %s", report_text.c_str());
                root.put("result", RESPONSE_SUCCESS);
            } else {
                root.put("result", RESPONSE_FAILURE);
                ChipLogError(NotSpecified, "Execute eevse read command failed!");
            }
        }
        std::stringstream ss;
        write_json(ss, root);
        std::string strContent = ss.str();
        crow::response response(strContent);
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    } catch (const std::exception & e)
    {
        crow::response response(400, e.what());
        ChipLogError(NotSpecified, "Error on eevse_read: %s", e.what());
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    }
}

}
