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

#include "api_handlers/onoff_handler.h"
#include "common.h"

#include <thread>
#include <chrono>
#include <sstream>
#include <map>

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <crow/json.h>
#include <lib/support/logging/CHIPLogging.h>

using namespace boost::property_tree;

namespace api_handlers {

crow::response handleOnoff(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        auto nodeId = std::string(x_body_decoded["nodeId"].s());
        auto endPointId = std::string(x_body_decoded["endPointId"].s());
        auto type = std::string(x_body_decoded["type"].s());
        ChipLogError(NotSpecified, "Received ON/OFF POST request for device with Node ID: %s, End Point ID: %s, Type: %s",
            std::string(nodeId).c_str(), std::string(endPointId).c_str(), std::string(type).c_str());
        const std::map<std::string, std::string> typeToVerb = {
            {"on", "switch on"},
            {"off", "switch off"},
            {"toggle", "toggle"},
        };
        std::string verb = typeToVerb.count(type) ? typeToVerb.at(type) : "perform an operation on";
        ChipLogError(NotSpecified, "Received POST request to %s the device", verb.c_str());
        std::string command;
        if (type == "on") {
            command = "onoff on " + nodeId + " " + endPointId;
        } else if (type == "off") {
            command = "onoff off " + nodeId + " " + endPointId;
        } else if (type == "toggle") {
            command = "onoff toggle " + nodeId + " " + endPointId;
        }
        wsClient.sendMessage(command);
        ChipLogError(NotSpecified, "send onoff command to chip-tool ws server");
        int sleepTime = 0;
        while (reportQueue.empty() && sleepTime < 20)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            sleepTime++;
        }
        if (sleepTime == 20) {
            root.put("result", RESPONSE_FAILURE);
            ChipLogError(NotSpecified, "Execute onoff command overtime!");
        } else {
            Json::Value resultsValue = wsClient.dequeueReport();
            int jsonObjectsize = resultsValue.size();
            if (jsonObjectsize == 0) {
                root.put("result", RESPONSE_SUCCESS);
            } else {
                root.put("result", RESPONSE_FAILURE);
                ChipLogError(NotSpecified, "Execute onoff command failed!");
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

crow::response handleOnoffReport(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        auto nodeAlias = std::string(x_body_decoded["nodeAlias"].s());
        auto nodeId = std::string(x_body_decoded["nodeId"].s());
        auto endPointId = std::string(x_body_decoded["endPointId"].s());
        ChipLogError(NotSpecified, "Received ON/OFF read POST request for device with Node ID: %s, End Point ID: %s",
            std::string(nodeId).c_str(), std::string(endPointId).c_str());
        std::string command;

        chip::NodeId nodeIdStorage = webCommissionerStorage.GetLocalKeyNodeId(nodeAlias.c_str());
        if (nodeIdStorage == 0) {
            root.put("result", RESPONSE_FAILURE);
            root.put("cause", "nodeAlias not found");
            ChipLogError(NotSpecified, "Node Alias not found in the storage");
        } else {
          command = "onoff read on-off " + nodeId + " " + endPointId;
          wsClient.sendMessage(command);
          ChipLogError(NotSpecified, "Send onoff read command to chip-tool ws server");
          int sleepTime = 0;
          while (reportQueue.empty() && sleepTime < 20)
          {
              std::this_thread::sleep_for(std::chrono::seconds(1));
              sleepTime++;
          }
          if (sleepTime == 20) {
              root.put("result", RESPONSE_FAILURE);
              ChipLogError(NotSpecified, "Generated onoff report overtime!");
          } else {
              Json::Value resultsReport = wsClient.dequeueReport();
              Json::Value resultsValue = resultsReport[0];
              if (resultsValue.isMember("error"))
              {
                  root.put("result", RESPONSE_FAILURE);
                  ChipLogError(NotSpecified, "Generated report failed!");
              } else {
                  std::stringstream report_ss;
                  report_ss << "Report from " << nodeAlias << " " << nodeId << ": " << resultsValue["endpointId"] << ". " << "Cluster: "
                            << resultsValue["clusterId"] << "; " << "On-Off" << ": " << resultsValue["value"];
                  std::string report_text = report_ss.str();
                  root.put("result", RESPONSE_SUCCESS);
                  ChipLogError(NotSpecified, "Generated report successfully: %s", report_text.c_str());
                  root.put("report", report_text);
              }
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
        ChipLogError(NotSpecified, "Error on onoff_report: %s", e.what());
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    }
}

}
