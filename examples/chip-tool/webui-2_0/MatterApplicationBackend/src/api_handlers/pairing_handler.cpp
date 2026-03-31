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

#include "api_handlers/pairing_handler.h"
#include "common.h"

#include <thread>
#include <chrono>
#include <sstream>

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <crow/json.h>
#include <lib/support/logging/CHIPLogging.h>
#include <controller/CommissioningWindowOpener.h>

using namespace boost::property_tree;

namespace api_handlers {

crow::response handlePairing(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        auto nodeId = std::string(x_body_decoded["nodeId"].s());
        auto type = std::string(x_body_decoded["type"].s());
        auto nodeAlias = std::string(x_body_decoded["nodeAlias"].s());
        ChipLogError(NotSpecified, "Received POST request for pairing with Node ID: %s, Type: %s, Node Alias: %s",
            std::string(nodeId).c_str(), std::string(type).c_str(), std::string(nodeAlias).c_str());
        if(type != "unpair" && webCommissionerStorage.SyncDoesKeyExist(std::string(nodeAlias).c_str())){
            root.put("result", RESPONSE_FAILURE);
            root.put("cause", "repeat nodeAlias");
        } else {
            std::string command;
            if (type == "onnetwork") {
                auto pinCode = std::string(x_body_decoded["pinCode"].s());
                command = "pairing onnetwork-commissioning-mode " + nodeId + " " + pinCode;
            } else if (type == "onnetwork-long") {
                auto pinCode = std::string(x_body_decoded["pinCode"].s());
                auto discriminator = std::string(x_body_decoded["discriminator"].s());
                command = "pairing onnetwork-long " + nodeId + " " + pinCode + " " + discriminator;
            }
            else if (type == "ble-wifi") {
                auto ssId = std::string(x_body_decoded["ssId"].s());
                auto password = std::string(x_body_decoded["password"].s());
                auto pinCode = std::string(x_body_decoded["pinCode"].s());
                auto discriminator = std::string(x_body_decoded["discriminator"].s());
                command = "pairing ble-wifi " + nodeId + " " + ssId + " " + password + " " + pinCode + " " + discriminator;
            } else if (type == "ble-thread") {
                auto dataset = std::string(x_body_decoded["dataset"].s());
                auto pinCode = std::string(x_body_decoded["pinCode"].s());
                auto discriminator = std::string(x_body_decoded["discriminator"].s());
                command = "pairing ble-thread " + nodeId + " hex:" + dataset + " " + pinCode + " " + discriminator;
            } else if (type == "qrcode") {
                auto payload = std::string(x_body_decoded["payload"].s());
                command = "pairing code " + nodeId + " " + payload;
            } else if (type == "unpair") {
                command = "pairing unpair " + nodeId;
            }
            ChipLogError(NotSpecified, "Received POST request for pairing with command: %s", command.c_str());
            wsClient.sendMessage(command);
            ChipLogError(NotSpecified, "Send pairing command to chip-tool ws server.");
            int sleepTime = 0;
            while (reportQueue.empty() && sleepTime < 125)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                sleepTime++;
            }
            if (!reportQueue.empty()) {
                Json::Value resultsReport = wsClient.dequeueReport();
                int resultsReportSize = resultsReport.size();
                if (resultsReportSize == 0) {
                    root.put("result", RESPONSE_SUCCESS);
                    chip::NodeId nodeIdStorage = std::stoul(nodeId);
                    const char * nodeAliasStorage = nodeAlias.c_str();
                    if (type == "unpair") {
                        webCommissionerStorage.SyncDeleteKeyValue(nodeAlias.c_str());
                    } else {
                        webCommissionerStorage.SetLocalKeyNodeId(nodeAliasStorage, nodeIdStorage);
                    }
                } else {
                    root.put("result", RESPONSE_FAILURE);
                    ChipLogError(NotSpecified, "Recieved response meaasge after sending pairing command, but pairing failed!");
                }
            } else {
                root.put("result", RESPONSE_FAILURE);
                ChipLogError(NotSpecified, "Execute pairing command overtime!");
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
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    }
}

crow::response handleMultiadmin(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        auto nodeId = std::string(x_body_decoded["nodeId"].s());
        auto option = std::string(x_body_decoded["option"].s());
        auto windowTimeout = std::string(x_body_decoded["windowTimeout"].s());
        auto iteration = std::string(x_body_decoded["iteration"].s());
        auto discriminator = std::string(x_body_decoded["discriminator"].s());
        ChipLogError(NotSpecified, "Received POST request to open commissioning window");
        std::string command;
        command = "pairing open-commissioning-window " + nodeId + " " + option + " " + windowTimeout + " " + iteration + " " + discriminator;
        wsClient.sendMessage(command);
        ChipLogError(NotSpecified, "send multiadmin command to chip-tool ws server");
        int sleepTime = 0;
        while (reportQueue.empty() && sleepTime < 20)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            sleepTime++;
        }
        if (sleepTime == 20) {
            root.put("result", RESPONSE_FAILURE);
            ChipLogError(NotSpecified, "Execute multiadmin command overtime!");
        } else {
            Json::Value resultsValue = wsClient.dequeueReport();
            int jsonObjectsize = resultsValue.size();
            if (jsonObjectsize == 0) {
                if(option == "1") {
                    std::string payload = GetCtwPayloadValue();
                    std::string qrCode = GetCtwQRCode();
                    root.put("payload", payload);
                    root.put("qrCode", qrCode);
                }
                root.put("result", RESPONSE_SUCCESS);
            } else {
                root.put("result", RESPONSE_FAILURE);
                ChipLogError(NotSpecified, "Execute multiadmin command failed!");
            }
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

crow::response handleDeleteStorageNode(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        auto nodeAlias = std::string(x_body_decoded["nodeAlias"].s());
        ChipLogError(NotSpecified, "Received POST request to delete storage node with node alias: %s", nodeAlias.c_str());
        auto start_time = std::chrono::steady_clock::now();
        try
        {
            webCommissionerStorage.SyncDeleteKeyValue(nodeAlias.c_str());
            root.put("result", RESPONSE_SUCCESS);
        } catch (const std::exception & e)
        {
            ChipLogError(NotSpecified, "Delete storage node with nodeAlias: %s failed", nodeAlias.c_str());
            root.put("result", RESPONSE_FAILURE);
        }
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
        if (elapsed_seconds > 60) {
            root.put("result", RESPONSE_FAILURE);
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

}
