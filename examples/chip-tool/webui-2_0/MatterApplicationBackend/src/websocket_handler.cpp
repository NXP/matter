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

#include "websocket_handler.h"
#include "common.h"
#include "utils.h"

#include <thread>
#include <chrono>
#include <sstream>
#include <unistd.h>

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <lib/support/logging/CHIPLogging.h>

using namespace boost::property_tree;

namespace websocket_handler {

void generateMessages(WsServer* s, websocketpp::connection_hdl hdl, message_ptr msg,
                      std::string nodeId, std::string nodeAlias)
{
    std::string report_text;
    while (true)
    {
        if(!subscribeReportQueue.empty())
        {
            Json::Value resultsValue = wsClient.dequeueSubscribeReport();
            Json::Value arryValue = resultsValue[0];
            std::stringstream report_ss;
            report_ss << "Subscribe Report from " << nodeAlias << " " << nodeId << ": " << arryValue["endpointId"] << ". " << "Cluster: "
                    << arryValue["clusterId"] << "\r\n\r\n" << "On-Off" << ": " << arryValue["value"];
            report_text = report_ss.str();
            ChipLogError(NotSpecified, "Receive subscribe message: %s", report_text.c_str());
            try
            {
                s->send(hdl, report_text, msg->get_opcode());
                ChipLogError(NotSpecified, "WebSocket server send subscribe report msg: %s", report_text.c_str());
            }
            catch (websocketpp::exception const & e)
            {
                ChipLogError(NotSpecified, "WebSocket server send subscribe report msg failed because %s", e.what());
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void generateOtaMessage(WsServer* s, websocketpp::connection_hdl hdl, message_ptr msg, std::string cmd)
{
    char buffer[128];
    std::string result = "";
    std::string otaReport = "";
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        otaReport = "OTA Report: chip-ota-provider-app start failed";
        try
        {
            s->send(hdl, otaReport, msg->get_opcode());
        }
        catch (websocketpp::exception const & e)
        {
            ChipLogError(NotSpecified, "WebSocket server send ota report msg failed because %s", e.what());
        }
        return;
    }

    auto start_time = std::chrono::steady_clock::now();
    const std::string expectedStartLog = "Updating services using commissioning mode 1";

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result = buffer;
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
        if (elapsed_seconds > 5)
        {
            ChipLogError(NotSpecified, "Run chip-ota-provider-app command: %s failed.", cmd.c_str());
            otaReport = "OTA Report: chip-ota-provider-app start failed";
            try
            {
                s->send(hdl, otaReport, msg->get_opcode());
            }
            catch (websocketpp::exception const & e)
            {
                ChipLogError(NotSpecified, "WebSocket server send ota report msg failed because %s", e.what());
            }
            utils::killProcesses(cmd);
            pclose(pipe);
            return;
        }
        if (result.find(expectedStartLog) != std::string::npos)
        {
            ChipLogError(NotSpecified, "Run chip-ota-provider-app command: %s successfully.", cmd.c_str());
            otaReport = "OTA Report: chip-ota-provider-app start successfully";
            try
            {
                s->send(hdl, otaReport, msg->get_opcode());
            }
            catch (websocketpp::exception const & e)
            {
                ChipLogError(NotSpecified, "WebSocket server send ota report msg failed because %s", e.what());
            }
            break;
        }
    }

    const std::string initReceived     = "OutputEvent type: InitReceived";
    const std::string AckEofReceived   = "OutputEvent type: AckEOFReceived";
    const std::string internalError    = "OutputEvent type: InternalError";
    const std::string transferTimeout  = "OutputEvent type: TransferTimeout";
    const std::string unknown          = "OutputEvent type: Unknown";

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result = buffer;
        if (result.find(initReceived) != std::string::npos)
        {
            otaReport = "OTA Report: chip-ota-provider-app start OTA file transfer";
            try
            {
                s->send(hdl, otaReport, msg->get_opcode());
            }
            catch (websocketpp::exception const & e)
            {
                ChipLogError(NotSpecified, "WebSocket server send ota report message failed because %s", e.what());
            }
        }
        if (result.find(AckEofReceived) != std::string::npos)
        {
            otaReport = "OTA Report: chip-ota-provider-app ota transfer successfully";
            try
            {
                s->send(hdl, otaReport, msg->get_opcode());
            }
            catch (websocketpp::exception const & e)
            {
                ChipLogError(NotSpecified, "WebSocket server send ota report message failed because %s", e.what());
            }
            break;
        }
        else if (result.find(internalError) != std::string::npos || result.find(transferTimeout) != std::string::npos || result.find(unknown) != std::string::npos)
        {
            otaReport = "OTA Report: chip-ota-provider-app transfer failed";
            try
            {
                s->send(hdl, otaReport, msg->get_opcode());
            }
            catch (websocketpp::exception const & e)
            {
                ChipLogError(NotSpecified, "WebSocket server send ota report message failed because %s", e.what());
            }
            break;
        }
    }
    utils::killProcesses(cmd);
    pclose(pipe);
    return;
}

void on_message(WsServer* s, websocketpp::connection_hdl hdl, message_ptr msg)
{
    ChipLogError(NotSpecified, "WebSocket server receive message: %s", msg->get_payload().c_str());
    std::string command = msg->get_payload();
    Json::Value jsonObject(Json::objectValue);
    Json::Reader reader;
    if (reader.parse(command, jsonObject))
    {
        std::string commandType = jsonObject["command"].asString();
        if (commandType =="onoff subscribe on-off") {
            std::string minInterval = jsonObject["minInterval"].asString();
            std::string maxInterval = jsonObject["maxInterval"].asString();
            std::string nodeAlias   = jsonObject["nodeAlias"].asString();
            std::string nodeId      = jsonObject["nodeId"].asString();
            std::string endPointId  = jsonObject["endPointId"].asString();
            ChipLogError(NotSpecified, "Received WebSockets request for subscribe with Node ID: %s, Endpoint ID: %s", nodeId.c_str(), endPointId.c_str());
            std::string subscribeCommand = "onoff subscribe on-off " + minInterval + " " + maxInterval + " " + nodeId + " " + endPointId;
            wsClient.sendMessage(subscribeCommand);
            ChipLogError(NotSpecified, "Send subscribe websocket command to chip-tool ws server.");
            int sleepTime = 0;
            while (reportQueue.empty() && sleepTime < 20)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                sleepTime++;
            }
            if (sleepTime == 20) {
                ChipLogError(NotSpecified, "Receive websocket command to chip-tool ws server overtime!");
            } else {
                Json::Value resultsValue = wsClient.dequeueReport();
                Json::Value arryValue = resultsValue[0];
                std::stringstream report_ss;
                std::string report_text;
                ChipLogError(NotSpecified, "Received subscribe report from chip-tool ws server: %s", arryValue.toStyledString().c_str());
                report_ss << "Subscribe Report from " << nodeAlias << " " << nodeId << ": " << arryValue["endpointId"] << ". " << "Cluster: "
                        << arryValue["clusterId"] << "\r\n\r\n" << "On-Off" << ": " << arryValue["value"];
                report_text = report_ss.str();
                ChipLogError(NotSpecified, "Generated report successfully: %s", report_text.c_str());
                try
                {
                    s->send(hdl, report_text, msg->get_opcode());
                    ChipLogError(NotSpecified, "WebSocket server send subscribe report msg: %s", report_text.c_str());
                }
                catch (websocketpp::exception const & e)
                {
                    ChipLogError(NotSpecified, "WebSocket server send subscribe report msg failed because %s", e.what());
                }
                std::thread generator(generateMessages, s, hdl, msg, nodeId, nodeAlias);
                generator.detach();
            }
        } else if (commandType =="ota provider") {
            std::string discriminator      = jsonObject["discriminator"].asString();
            std::string filePath           = jsonObject["filePath"].asString();
            std::string otaCommand         = "chip-ota-provider-app --discriminator " + discriminator + " --filepath " + filePath;
            ChipLogError(NotSpecified, "Received chip-ota-provider-app from chip-tool ws server");
            if (access(filePath.c_str(), F_OK) == 0) {
                std::thread otaProviderProcess(generateOtaMessage, s, hdl, msg, otaCommand);
                otaProviderProcess.detach();
            } else {
                try {
                    ChipLogError(NotSpecified, "Ota file does not exits %s", filePath.c_str());
                    std::string report_text = "OTA Report: ota file does not exits";
                    s->send(hdl, report_text, msg->get_opcode());
                    ChipLogError(NotSpecified, "WebSocket server send subscribe report msg: %s", report_text.c_str());
                } catch (websocketpp::exception const & e) {
                    ChipLogError(NotSpecified, "WebSocket server send subscribe report msg failed because %s", e.what());
                }
            }
        }
    }
}

bool validate(WsServer* s, websocketpp::connection_hdl connection)
{
    s->get_con_from_hdl(connection)->append_header("Access-Control-Allow-Origin", "*");
    s->get_con_from_hdl(connection)->append_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    s->get_con_from_hdl(connection)->append_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    s->get_con_from_hdl(connection)->append_header("Access-Control-Allow-Credentials", "true");
    return true;
}

void websocket_on_http(WsServer* s, websocketpp::connection_hdl hdl)
{
    auto con = s->get_con_from_hdl(hdl);
    con->set_status(websocketpp::http::status_code::ok);
    con->append_header("access-control-allow-origin", "*");
    con->append_header("content-type", "application/json; charset=UTF-8");
    ptree body;
    body.put("websocket", true);
    body.put("origins", "*:*");
    body.put("cookie_needed", false);
    std::ostringstream oss;
    write_json(oss, body);
    std::string body_str = oss.str();
    con->set_body(body_str);
}

}
