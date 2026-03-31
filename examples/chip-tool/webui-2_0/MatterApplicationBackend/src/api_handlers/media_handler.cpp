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

#include "api_handlers/media_handler.h"
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

crow::response handleLauncher(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        auto nodeId = std::string(x_body_decoded["nodeId"].s());
        auto endPointId = std::string(x_body_decoded["endPointId"].s());
        auto type = std::string(x_body_decoded["type"].s());
        auto catalogVendorID = std::string(x_body_decoded["launchConf"]["catalogVendorID"].s());
        auto applicationID = std::string(x_body_decoded["launchConf"]["applicationID"].s());
        std::string launchConf= "'{\"catalogVendorID\": " +  catalogVendorID + ", \"applicationID\": \"" + applicationID + "\"}'";
        std::string command;
        if (type == "launch") {
            command = "applicationlauncher launch-app " + nodeId + " " + endPointId + " --Application " + launchConf;
            ChipLogError(NotSpecified, "Received POST request to Launch App");
        } else if (type == "stop") {
            command = "applicationlauncher stop-app " + nodeId + " " + endPointId + " --Application " + launchConf;
            ChipLogError(NotSpecified, "Received POST request to Stop App");
        }
        wsClient.sendMessage(command);
        ChipLogError(NotSpecified, "send launcher command to chip-tool ws server");
        int sleepTime = 0;
        while (reportQueue.empty() && sleepTime < 20)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            sleepTime++;
        }
        if (sleepTime == 20) {
            root.put("result", RESPONSE_FAILURE);
            ChipLogError(NotSpecified, "Execute launcher command overtime!!");
        } else {
            Json::Value resultsReport = wsClient.dequeueReport();
            Json::Value resultsValue = resultsReport[0];
            if (resultsValue.isMember("error"))
            {
                root.put("result", RESPONSE_FAILURE);
                ChipLogError(NotSpecified, "Execute launcher command failed!");
            } else {
                root.put("result", RESPONSE_SUCCESS);
                ChipLogError(NotSpecified, "Execute launcher command successfully");
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

crow::response handleMediaControl(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        auto nodeId = std::string(x_body_decoded["nodeId"].s());
        auto endPointId = std::string(x_body_decoded["endPointId"].s());
        auto type = std::string(x_body_decoded["type"].s());
        ChipLogError(NotSpecified, "Received POST request for media control" );
        std::string command;
        if (type == "play") {
            command = "mediaplayback play " + nodeId + " " + endPointId;
        } else if (type == "pause") {
            command = "mediaplayback pause " + nodeId + " " + endPointId;
        } else if (type == "stop") {
            command = "mediaplayback stop " + nodeId + " " + endPointId;
        } else if (type == "startover") {
            command = "mediaplayback start-over " + nodeId + " " + endPointId;
        } else if (type == "previous") {
            command = "mediaplayback previous " + nodeId + " " + endPointId;
        } else if (type == "next") {
            command = "mediaplayback next " + nodeId + " " + endPointId;
        } else if (type == "rewind") {
            command = "mediaplayback rewind " + nodeId + " " + endPointId;
        } else if (type == "fastforward") {
            command = "mediaplayback fast-forward " + nodeId + " " + endPointId;
        }
        wsClient.sendMessage(command);
        ChipLogError(NotSpecified, "Send media control command to chip-tool ws server");
        int sleepTime = 0;
        while (reportQueue.empty() && sleepTime < 20)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            sleepTime++;
        }
        if (sleepTime == 20) {
            root.put("result", RESPONSE_FAILURE);
            ChipLogError(NotSpecified, "Execute media control command overtime!");
        } else {
            Json::Value resultsReport = wsClient.dequeueReport();
            Json::Value resultsValue = resultsReport[0];
            if (resultsValue.isMember("error"))
            {
                root.put("result", RESPONSE_FAILURE);
                ChipLogError(NotSpecified, "Execute media control command failed!");
            } else {
                root.put("result", RESPONSE_SUCCESS);
                ChipLogError(NotSpecified, "Execute media control command successfully");
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

crow::response handleMediaRead(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        auto nodeAlias  = std::string(x_body_decoded["nodeAlias"].s());
        auto nodeId = std::string(x_body_decoded["nodeId"].s());
        auto endPointId = std::string(x_body_decoded["endPointId"].s());
        auto type = std::string(x_body_decoded["type"].s());
        ChipLogError(NotSpecified, "Received POST request for media control" );
        std::string command;
        if (type == "currentstate") {
            command = "mediaplayback read current-state " + nodeId + " " + endPointId;
        } else if (type == "starttime") {
            command = "mediaplayback read start-time " + nodeId + " " + endPointId;
        } else if (type == "duration") {
            command = "mediaplayback read duration " + nodeId + " " + endPointId;
        } else if (type == "sampledposition") {
            command = "mediaplayback read sampled-position " + nodeId + " " + endPointId;
        } else if (type == "playbackspeed") {
            command = "mediaplayback read playback-speed " + nodeId + " " + endPointId;
        }
        wsClient.sendMessage(command);
        ChipLogError(NotSpecified, "Send media read command to chip-tool ws server");
        int sleepTime = 0;
        while (reportQueue.empty() && sleepTime < 46)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            sleepTime++;
        }
        if (sleepTime == 46) {
            root.put("result", RESPONSE_FAILURE);
            ChipLogError(NotSpecified, "Execute media read command overtime!");
        } else {
            Json::Value resultsReport = wsClient.dequeueReport();
            Json::Value resultsValue = resultsReport[0];
            if (!resultsValue.isMember("error") && resultsValue.isMember("value") )
            {
                std::string report_text;
                std::stringstream report_ss;
                std::string value;
                if (type == "currentstate")
                {
                    switch (resultsValue["value"].asInt())
                    {
                        case 0:
                            value = "Play";
                            break;
                        case 1:
                            value = "Pause";
                            break;
                        case 2:
                            value = "Stop";
                            break;
                        default:
                            value = "Unknown";
                    }
                } else if (type == "sampledposition")
                {
                    Json::Value positionValue = resultsValue["value"];
                    if(positionValue.isMember("1"))
                        value = positionValue["1"].asString();
                    else
                        value ="Unknown";
                } else
                {
                    value = resultsValue["value"].asString();
                }
                report_ss << "Report from " << nodeAlias << " " << nodeId << ": " << resultsValue["endpointId"] << ". "
                        << "Cluster: " << resultsValue["clusterId"] << "\r\n\r\n" << type << ": " << value;
                report_text = report_ss.str();
                root.put("report", report_text);
                ChipLogError(NotSpecified, "Generated media app report successfully: %s", report_text.c_str());
                root.put("result", RESPONSE_SUCCESS);
            } else {
                root.put("result", RESPONSE_FAILURE);
                ChipLogError(NotSpecified, "Execute media read command failed!");
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

}
