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

#include "api_handlers/binding_handler.h"
#include "common.h"

#include <thread>
#include <chrono>
#include <sstream>
#include <array>

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <crow/json.h>
#include <lib/support/logging/CHIPLogging.h>

using namespace boost::property_tree;

namespace api_handlers {

crow::response handleWriteAcl(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        std::array<std::string, 2> aclConfString;
        for(int i = 0; i < 2; i++)
        {
            std::string aclConfKey = "aclConf" + std::to_string(i + 1);
            auto fabricIndex = std::string(x_body_decoded[aclConfKey]["fabricIndex"].s());
            auto privilege = std::string(x_body_decoded[aclConfKey]["privilege"].s());
            auto authMode = std::string(x_body_decoded[aclConfKey]["authMode"].s());
            auto subjects = std::string(x_body_decoded[aclConfKey]["subjects"].s());
            auto targets = std::string(x_body_decoded[aclConfKey]["targets"].s());
            aclConfString[i] = "{\"fabricIndex\": " +  fabricIndex + ", \"privilege\": " + privilege + ", \"authMode\": " + authMode +
                               ", \"subjects\": " + subjects + ", \"targets\": " + targets + "}";
        }
        auto nodeId = std::string(x_body_decoded["nodeId"].s());
        auto endpointId = std::string(x_body_decoded["endpointId"].s());
        ChipLogError(NotSpecified, "Received POST request to Write ACL");
        std::string command;
        command = "accesscontrol write acl '[" + aclConfString[0] +"," + aclConfString[1] + "]'" + nodeId + " " + endpointId;
        wsClient.sendMessage(command);
        ChipLogError(NotSpecified, "send write_acl command to chip-tool ws server");
        int sleepTime = 0;
        while (reportQueue.empty() && sleepTime < 20)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            sleepTime++;
        }
        if (sleepTime == 20) {
            root.put("result", RESPONSE_FAILURE);
            ChipLogError(NotSpecified, "Execute write acl command overtime!");
        } else {
            Json::Value resultsValue = wsClient.dequeueReport();
            int jsonObjectsize = resultsValue.size();
            if (jsonObjectsize == 0) {
                root.put("result", RESPONSE_SUCCESS);
            } else {
                root.put("result", RESPONSE_FAILURE);
                ChipLogError(NotSpecified, "Execute write acl command failed!");
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

crow::response handleWriteBinding(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        auto fabricIndex = std::string(x_body_decoded["bindingConf"]["fabricIndex"].s());
        auto node = std::string(x_body_decoded["bindingConf"]["node"].s());
        auto endpoint = std::string(x_body_decoded["bindingConf"]["endpoint"].s());
        auto cluster = std::string(x_body_decoded["bindingConf"]["cluster"].s());
        std::string bindingConf = "{\"fabricIndex\": " +  fabricIndex + ", \"node\": " + node
                                + ", \"endpoint\": " + endpoint + ", \"cluster\": " + cluster + "}";
        auto nodeId = std::string(x_body_decoded["nodeId"].s());
        auto endpointId = std::string(x_body_decoded["endpointId"].s());
        ChipLogError(NotSpecified, "Received POST request to Write Binding");
        std::string command;
        command ="binding write binding '[" + bindingConf + "]'" + nodeId + " " + endpointId;
        wsClient.sendMessage(command);
        ChipLogError(NotSpecified, "send write_binding command to chip-tool ws server");
        int sleepTime = 0;
        while (reportQueue.empty() && sleepTime < 20)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            sleepTime++;
        }
        if (sleepTime == 20) {
            root.put("result", RESPONSE_FAILURE);
            ChipLogError(NotSpecified, "Execute write binding command overtime!");
        } else {
            Json::Value resultsValue = wsClient.dequeueReport();
            int jsonObjectsize = resultsValue.size();
            if (jsonObjectsize == 0) {
                root.put("result", RESPONSE_SUCCESS);
            } else {
                root.put("result", RESPONSE_FAILURE);
                ChipLogError(NotSpecified, "Execute write binding command failed!");
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

}
