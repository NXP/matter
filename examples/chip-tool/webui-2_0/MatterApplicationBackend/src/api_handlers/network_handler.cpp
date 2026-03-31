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

#include "api_handlers/network_handler.h"
#include "common.h"
#include "utils.h"
#include "storage_utils.h"

#include <thread>
#include <chrono>
#include <sstream>

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <crow/json.h>
#include <lib/support/logging/CHIPLogging.h>
#include "commands/clusters/ReportCommand.h"

using namespace boost::property_tree;

namespace api_handlers {

crow::response handleGetDataset()
{
    try
    {
        ChipLogError(NotSpecified, "Received GET request for get OpDataset");
        std::string output = utils::exec_cmd("ot-ctl dataset active -x");
        std::string opdataset = "";
        size_t pos = output.find("\r\nDone");
        if (pos != std::string::npos) {
            opdataset = output.substr(0, pos);
        }

        ptree root;
        if (opdataset != "") {
            root.put("result", RESPONSE_SUCCESS);
            root.put("message", "OpDataset obtained");
            root.put("dataset", opdataset);
        } else {
            root.put("result", RESPONSE_FAILURE);
            root.put("message", "OpDataset not found");
        }

        std::stringstream ss;
        write_json(ss, root);
        std::string strContent = ss.str();
        crow::response response(strContent);
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    } catch (const std::exception &e)
    {
        crow::response response(400, e.what());
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    }
}

crow::response handleGetStatus()
{
    try
    {
        Json::Value root(Json::objectValue);
        ChipLogError(NotSpecified, "Received GET request for get status");
        try{
            Json::Value storageNodes = storage_utils::getStorageKeyNodeID();
            Json::Value nodeList(Json::arrayValue);
            for (const auto& storageNode : storageNodes)
            {
                std::string storageNodeAlias = storageNode["storageNodeAlias"].asString();
                std::string storageNodeId    = storageNode["storageNodeId"].asString();
                std::string command          = "descriptor read device-type-list " + storageNodeId + " 0xFFFF";
                Json::Value nodeInfo(Json::objectValue);
                nodeInfo["nodeAlias"] = storageNodeAlias;
                nodeInfo["nodeId"]    = storageNodeId;

                wsClient.sendMessage(command);
                ChipLogError(NotSpecified, "Send read device-type-list command to chip-tool WS server");
                int sleepTime = 0;
                while (reportQueue.empty() && sleepTime < 50)
                {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    sleepTime++;
                }
                if (!reportQueue.empty()) {
                    Json::Value resultsReport = wsClient.dequeueReport();
                    Json::Value endpointInfo(Json::objectValue);
                    for (const auto& report : resultsReport) {
                        if (!report.isMember("endpointId") || !report.isMember("value")) {
                            continue;
                        }
                        std::string endpointId = report["endpointId"].asString();
                        const auto& values = report["value"];
                        Json::Value endpointClusters(Json::arrayValue);
                        for (const auto& value : values) {
                            if (!value.isMember("0")) {
                                continue;
                            }
                            std::string clusterType = DeviceTypeIdToText(value["0"].asInt());
                            endpointClusters.append(clusterType);
                        }
                        endpointInfo[endpointId] = endpointClusters;
                    }
                    nodeInfo["endpointInfo"] = endpointInfo;
                } else {
                    ChipLogError(NotSpecified, "Execute read device-type-list command failed, no result response!");
                    continue;
                }
                nodeList.append(nodeInfo);
            }
            root["nodeList"] = nodeList;
            root["result"] = RESPONSE_SUCCESS;
        } catch (const std::exception & e)
        {
            ChipLogError(NotSpecified, "GET request for get status failed");
            root["result"] = RESPONSE_FAILURE;
        }
        std::string strContent = root.toStyledString();
        crow::response response(strContent);
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    } catch (const std::exception & e)
    {
        crow::response response(400, e.what());
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    }
}

crow::response handleGetNetwork()
{
    try
    {
        Json::Value root(Json::objectValue);
        ChipLogError(NotSpecified, "Received GET request for get network");
        try{
            std::string output = utils::exec_cmd("cat /sys/devices/soc0/machine");
            std::string machine = utils::extractMachineName(output);
            root["machine"] = machine;
            Json::Value storageNodes = storage_utils::getStorageKeyNodeID();
            Json::Value nodeList(Json::arrayValue);
            for (const auto& storageNode : storageNodes)
            {
                std::string storageNodeAlias = storageNode["storageNodeAlias"].asString();
                std::string storageNodeId    = storageNode["storageNodeId"].asString();
                std::string command          = "networkcommissioning read feature-map " + storageNodeId + " 0";
                Json::Value nodeInfo(Json::objectValue);
                nodeInfo["nodeAlias"] = storageNodeAlias;
                nodeInfo["nodeId"]    = storageNodeId;
                wsClient.sendMessage(command);
                ChipLogError(NotSpecified, "Send networkcommissioning read feature-map command to chip-tool WS server");
                int sleepTime = 0;
                while (reportQueue.empty() && sleepTime < 50)
                {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    sleepTime++;
                }
                if (!reportQueue.empty()) {
                    Json::Value resultsReport = wsClient.dequeueReport();
                    Json::Value resultsValue = resultsReport[0];
                    std::string value;
                    if (resultsValue.isMember("error"))
                    {
                        value = "Offline";
                        ChipLogError(NotSpecified, "Execute networkcommissioning read feature-map command failed!");
                    } else
                    {
                        switch (resultsValue["value"].asInt())
                        {
                            case 1:
                                value = "WiFi";
                                break;
                            case 2:
                                value = "Thread";
                                break;
                            case 4:
                                value = "Ethernet";
                                break;
                            default:
                                value = "Unknown";
                        }
                    }
                    nodeInfo["networkType"] = value;
                    ChipLogError(NotSpecified, "Execute networkcommissioning read feature-map command successfully!");
                } else
                {
                    continue;
                    ChipLogError(NotSpecified, "Execute networkcommissioning read feature-map command overtime!");
                }
                nodeList.append(nodeInfo);
            }
            root["nodeList"] = nodeList;
            root["result"] = RESPONSE_SUCCESS;
        } catch (const std::exception & e)
        {
            ChipLogError(NotSpecified, "GET request for get network failed!");
            root["result"] = RESPONSE_FAILURE;
        }
        std::string strContent = root.toStyledString();
        crow::response response(strContent);
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    } catch (const std::exception & e)
    {
        crow::response response(400, e.what());
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    }
}

crow::response handleGetAvailableNetwork(const crow::request& req)
{
    std::thread work_thread([req] {
        std::string json_string = "{\"result\":[{\"ch\":13,\"ha\":\"18B43000003D2785\",\"nn\":\"NEST-PAN-C1E7\",\"pi\":\"0xC19B\","
                                 "\"xp\":\"EEA74CE1EDFA2E8A\"}]}";
    });
    work_thread.detach();
    crow::response response("Work done");
    response.add_header("Access-Control-Allow-Origin", "*");
    return response;
}

}
