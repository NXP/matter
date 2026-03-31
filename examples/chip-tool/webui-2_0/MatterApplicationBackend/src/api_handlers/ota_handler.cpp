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

#include "api_handlers/ota_handler.h"
#include "common.h"

#include <thread>
#include <chrono>
#include <sstream>
#include <fstream>

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <crow/json.h>
#include <crow/multipart.h>
#include <lib/support/logging/CHIPLogging.h>

using namespace boost::property_tree;

namespace api_handlers {

crow::response handleUploader(const crow::request& req)
{
    try
    {
        ptree root;
        crow::multipart::message msg(req);
        for (const auto& part : msg.parts) {
            const auto& disposition = part.get_header_object("Content-Disposition");
            auto it = disposition.params.find("filename");

            if (it != disposition.params.end()) {
                const std::string& filename = it->second;
                std::string otaFileSavePath = "/root/" + std::string(filename) ;
                std::ofstream ofs(otaFileSavePath, std::ios::binary);
                if (!ofs) {
                    ChipLogError(NotSpecified, "Uploaded OTA file save failed!");
                    root.put("result", RESPONSE_FAILURE);
                } else {
                    ofs.write(part.body.data(), part.body.size());
                    ofs.close();
                    ChipLogError(NotSpecified, "Uploaded OTA file save as: %s", otaFileSavePath.c_str());
                    root.put("result", RESPONSE_SUCCESS);
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
        ChipLogError(NotSpecified, "Error on uploader: %s", e.what());
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    }
}

crow::response handleOtaSoftwareUpdateRequestor(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        auto otaProviderNodeId = std::string(x_body_decoded["otaProviderNodeId"].s());
        auto otaRequestorNodeId = std::string(x_body_decoded["otaRequestorNodeId"].s());
        std::string command;
        command = "otasoftwareupdaterequestor announce-otaprovider " + otaProviderNodeId + " 0 0 0 " + otaRequestorNodeId + " 0";
        wsClient.sendMessage(command);
        ChipLogError(NotSpecified, "Send otasoftwareupdaterequestor command to chip-tool ws server");
        int sleepTime = 0;
        while (reportQueue.empty() && sleepTime < 20)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            sleepTime++;
        }
        if (sleepTime == 20) {
            root.put("result", RESPONSE_FAILURE);
            ChipLogError(NotSpecified, "Execute otasoftwareupdaterequestor command overtime!");
        } else {
            Json::Value resultsReport = wsClient.dequeueReport();
            Json::Value resultsValue = resultsReport[0];
            if (resultsValue.isMember("error"))
            {
                root.put("result", RESPONSE_FAILURE);
            } else {
                root.put("result", RESPONSE_SUCCESS);
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
        ChipLogError(NotSpecified, "Error on otasoftwareupdaterequestor: %s", e.what());
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    }
}

}
