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

#include "api_handlers/rvc_handler.h"
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

crow::response handleRvcControl(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        auto nodeAlias = std::string(x_body_decoded["nodeAlias"].s());
        auto nodeId = std::string(x_body_decoded["nodeId"].s());
        auto endPointId = std::string(x_body_decoded["endPointId"].s());
        auto cluster = std::string(x_body_decoded["cluster"].s());
        auto type = std::string(x_body_decoded["type"].s());
        ChipLogError(NotSpecified, "Received RVC control POST request for device with Node ID: %s, End Point ID: %s, Cluster: %s",
            std::string(nodeId).c_str(), std::string(endPointId).c_str(), std::string(cluster).c_str());
        std::string command;
        if (cluster == "rvcrunmode") {
            if (type == "change-to-mode") {
                auto newMode = std::to_string(x_body_decoded["newMode"].i());
                command = "rvcrunmode change-to-mode " + newMode + " " + nodeId + " " + endPointId;
            }
        } else if (cluster == "rvccleanmode") {
            if (type == "change-to-mode") {
                auto newMode = std::to_string(x_body_decoded["newMode"].i());
                command = "rvccleanmode change-to-mode " + newMode + " " + nodeId + " " + endPointId;
            }
        } else if (cluster == "rvcoperationalstate") {
            if (type == "go-home") {
                command = "rvcoperationalstate go-home " + nodeId + " " + endPointId;
            } else if (type == "pause") {
                command = "rvcoperationalstate pause " + nodeId + " " + endPointId;
            } else if (type == "resume") {
                command = "rvcoperationalstate resume " + nodeId + " " + endPointId;
            }
        } else if (cluster == "servicearea") {
            if (type == "select-areas") {
                auto areaId = std::string(x_body_decoded["areaId"].s());
                command = "servicearea select-areas '[" + areaId + "]' " + nodeId + " " + endPointId;
            } else if (type == "skip-area") {
                auto areaId = std::string(x_body_decoded["areaId"].s());
                command = "servicearea skip-area " + areaId + " " + nodeId + " " + endPointId;
            }
        }
        if (command.empty()) {
            root.put("result", RESPONSE_FAILURE);
            root.put("cause", "unsupported cluster/type combination");
            ChipLogError(NotSpecified, "Unsupported RVC control cluster/type: %s/%s", cluster.c_str(), type.c_str());
            std::stringstream ss;
            write_json(ss, root);
            std::string strContent = ss.str();
            crow::response response(strContent);
            response.add_header("Access-Control-Allow-Origin", "*");
            return response;
        }
        wsClient.sendMessage(command);
        ChipLogError(NotSpecified, "Send RVC control command to chip-tool ws server");
        int sleepTime = 0;
        while (reportQueue.empty() && sleepTime < 20)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            sleepTime++;
        }
        if (sleepTime == 20) {
            root.put("result", RESPONSE_FAILURE);
            root.put("cause", "command execution timeout");
            ChipLogError(NotSpecified, "Execute RVC control command overtime!");
        } else {
            Json::Value resultsReport = wsClient.dequeueReport();
            if (!resultsReport.isArray() || resultsReport.empty()) {
                root.put("result", RESPONSE_FAILURE);
                root.put("cause", "empty or malformed results from chip-tool");
                ChipLogError(NotSpecified, "Execute RVC control command failed: empty or malformed results!");
            } else {
                Json::Value resultsValue = resultsReport[0];
                if (resultsValue.isMember("error"))
                {
                    root.put("result", RESPONSE_FAILURE);
                    root.put("cause", resultsValue["error"].asString());
                    ChipLogError(NotSpecified, "Execute RVC control command failed: %s", resultsValue["error"].asString().c_str());
                } else if (resultsValue.isMember("value")) {
                    Json::Value valueObj = resultsValue["value"];
                    int statusCode = -1;
                    std::string statusText;
                    if (cluster == "rvcrunmode" || cluster == "rvccleanmode") {
                        if (valueObj.isMember("0")) {
                            statusCode = valueObj["0"].asInt();
                        }
                        if (valueObj.isMember("1")) {
                            statusText = valueObj["1"].asString();
                        }
                    } else if (cluster == "rvcoperationalstate") {
                        // OperationalCommandResponse: field 0 = ErrorStateStruct
                        // ErrorStateStruct: field 0 = errorStateID, field 1 = errorStateLabel, field 2 = errorStateDetails
                        if (valueObj.isMember("0") && valueObj["0"].isMember("0")) {
                            statusCode = valueObj["0"]["0"].asInt();
                        }
                        if (valueObj.isMember("0") && valueObj["0"].isMember("1")) {
                            statusText = valueObj["0"]["1"].asString();
                        }
                    } else if (cluster == "servicearea") {
                        // SelectAreasResponse / SkipAreaResponse: field 0 = status, field 1 = statusText
                        if (valueObj.isMember("0")) {
                            statusCode = valueObj["0"].asInt();
                        }
                        if (valueObj.isMember("1")) {
                            statusText = valueObj["1"].asString();
                        }
                    }
                    if (statusCode == 0) {
                        root.put("result", RESPONSE_SUCCESS);
                        ChipLogError(NotSpecified, "Execute RVC control command successfully");
                    } else {
                        root.put("result", RESPONSE_FAILURE);
                        if (!statusText.empty()) {
                            root.put("cause", statusText);
                        }
                        ChipLogError(NotSpecified, "Execute RVC control command failed with status code: %d", statusCode);
                    }
                } else {
                    root.put("result", RESPONSE_SUCCESS);
                    ChipLogError(NotSpecified, "Execute RVC control command successfully");
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
        ChipLogError(NotSpecified, "Error on rvc_control: %s", e.what());
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    }
}

crow::response handleRvcRead(const crow::request& req)
{
    try
    {
        ptree root;
        auto x_body_decoded = crow::json::load(req.body);
        auto nodeAlias = std::string(x_body_decoded["nodeAlias"].s());
        auto nodeId = std::string(x_body_decoded["nodeId"].s());
        auto endPointId = std::string(x_body_decoded["endPointId"].s());
        auto cluster = std::string(x_body_decoded["cluster"].s());
        auto attribute = std::string(x_body_decoded["attribute"].s());
        ChipLogError(NotSpecified, "Received RVC read POST request for device with Node ID: %s, End Point ID: %s, Cluster: %s",
            std::string(nodeId).c_str(), std::string(endPointId).c_str(), std::string(cluster).c_str());
        std::string command;
        if (cluster == "rvcrunmode") {
            if (attribute == "current-mode") {
                command = "rvcrunmode read current-mode " + nodeId + " " + endPointId;
            } else if (attribute == "supported-modes") {
                command = "rvcrunmode read supported-modes " + nodeId + " " + endPointId;
            }
        } else if (cluster == "rvccleanmode") {
            if (attribute == "current-mode") {
                command = "rvccleanmode read current-mode " + nodeId + " " + endPointId;
            } else if (attribute == "supported-modes") {
                command = "rvccleanmode read supported-modes " + nodeId + " " + endPointId;
            }
        } else if (cluster == "rvcoperationalstate") {
            if (attribute == "operational-state") {
                command = "rvcoperationalstate read operational-state " + nodeId + " " + endPointId;
            } else if (attribute == "operational-error") {
                command = "rvcoperationalstate read operational-error " + nodeId + " " + endPointId;
            }
        } else if (cluster == "servicearea") {
            if (attribute == "supported-maps") {
                command = "servicearea read supported-maps " + nodeId + " " + endPointId;
            } else if (attribute == "supported-areas") {
                command = "servicearea read supported-areas " + nodeId + " " + endPointId;
            } else if (attribute == "selected-areas") {
                command = "servicearea read selected-areas " + nodeId + " " + endPointId;
            } else if (attribute == "current-area") {
                command = "servicearea read current-area " + nodeId + " " + endPointId;
            }
        }
        if (command.empty()) {
            root.put("result", RESPONSE_FAILURE);
            root.put("cause", "unsupported cluster/type combination");
            ChipLogError(NotSpecified, "Unsupported RVC read cluster/attribute: %s/%s", cluster.c_str(), attribute.c_str());
            std::stringstream ss;
            write_json(ss, root);
            std::string strContent = ss.str();
            crow::response response(strContent);
            response.add_header("Access-Control-Allow-Origin", "*");
            return response;
        }
        wsClient.sendMessage(command);
        ChipLogError(NotSpecified, "Send RVC read command to chip-tool ws server");
        int sleepTime = 0;
        while (reportQueue.empty() && sleepTime < 20)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            sleepTime++;
        }
        if (sleepTime == 20) {
            root.put("result", RESPONSE_FAILURE);
            root.put("cause", "command execution timeout");
            ChipLogError(NotSpecified, "Execute RVC read command overtime!");
        } else {
            Json::Value resultsReport = wsClient.dequeueReport();
            if (!resultsReport.isArray() || resultsReport.empty()) {
                root.put("result", RESPONSE_FAILURE);
                root.put("cause", "empty or malformed results from chip-tool");
                ChipLogError(NotSpecified, "Execute RVC read command failed: empty or malformed results!");
            } else {
                Json::Value resultsValue = resultsReport[0];
                if (!resultsValue.isMember("error") && resultsValue.isMember("value"))
                {
                    Json::Value valueObj = resultsValue["value"];
                    std::string valueStr;

                    if ((cluster == "rvcrunmode" || cluster == "rvccleanmode") && attribute == "supported-modes") {
                        // ModeOptionStruct: field 0 = label, field 1 = mode, field 2 = modeTags[]
                        std::stringstream modeSs;
                        modeSs << "\nSupportedModes: " << valueObj.size() << " entries";
                        for (Json::ArrayIndex i = 0; i < valueObj.size(); i++) {
                            std::string modeName = valueObj[i]["0"].asString();
                            int modeId = valueObj[i]["1"].asInt();
                            modeSs << "\n  [" << (i + 1) << "]: Label: " << modeName << ", Mode: " << modeId;
                            if (valueObj[i].isMember("2") && valueObj[i]["2"].isArray()) {
                                modeSs << ", ModeTags: ";
                                const Json::Value& tags = valueObj[i]["2"];
                                for (Json::ArrayIndex j = 0; j < tags.size(); j++) {
                                    if (j > 0) {
                                        modeSs << " | ";
                                    }
                                    int tagValue = tags[j].isMember("1") ? tags[j]["1"].asInt() : 0;
                                    modeSs << tagValue;
                                }
                            }
                        }
                        valueStr = modeSs.str();
                    } else if (cluster == "rvcrunmode" && attribute == "current-mode") {
                        int modeValue = valueObj.asInt();
                        switch (modeValue) {
                            case 0:
                                valueStr = "Idle";
                                break;
                            case 1:
                                valueStr = "Cleaning";
                                break;
                            case 2:
                                valueStr = "Mapping";
                                break;
                            default:
                                valueStr = "Unknown(" + std::to_string(modeValue) + ")";
                        }
                    } else if (cluster == "rvccleanmode" && attribute == "current-mode") {
                        int modeValue = valueObj.asInt();
                        switch (modeValue) {
                            case 0:
                                valueStr = "Quick";
                                break;
                            case 1:
                                valueStr = "Auto";
                                break;
                            case 2:
                                valueStr = "Deep Clean";
                                break;
                            case 3:
                                valueStr = "Quiet";
                                break;
                            case 4:
                                valueStr = "Max Vac";
                                break;
                            case 5:
                                valueStr = "Vacuum Then Mop";
                                break;
                            default:
                                valueStr = "Unknown(" + std::to_string(modeValue) + ")";
                        }
                    } else if (cluster == "rvcoperationalstate" && attribute == "operational-state") {
                        int stateValue = valueObj.asInt();
                        switch (stateValue) {
                            case 0:
                                valueStr = "Stopped";
                                break;
                            case 1:
                                valueStr = "Running";
                                break;
                            case 2:
                                valueStr = "Paused";
                                break;
                            case 3:
                                valueStr = "Error";
                                break;
                            case 64:
                                valueStr = "SeekingCharger";
                                break;
                            case 65:
                                valueStr = "Charging";
                                break;
                            case 66:
                                valueStr = "Docked";
                                break;
                            case 67:
                                valueStr = "EmptyingDustBin";
                                break;
                            case 68:
                                valueStr = "CleaningMop";
                                break;
                            case 69:
                                valueStr = "FillingWaterTank";
                                break;
                            case 70:
                                valueStr = "UpdatingMaps";
                                break;
                            default:
                                valueStr = "Unknown(" + std::to_string(stateValue) + ")";
                        }
                    } else if (cluster == "rvcoperationalstate" && attribute == "operational-error") {
                        // ErrorStateStruct: field 0 = errorStateID
                        int errorCode = 0;
                        if (valueObj.isMember("0")) {
                            errorCode = valueObj["0"].asInt();
                        }
                        switch (errorCode) {
                            case 0:
                                valueStr = "NoError";
                                break;
                            case 1:
                                valueStr = "UnableToStartOrResume";
                                break;
                            case 2:
                                valueStr = "UnableToCompleteOperation";
                                break;
                            case 3:
                                valueStr = "CommandInvalidInState";
                                break;
                            case 64:
                                valueStr = "FailedToFindChargingDock";
                                break;
                            case 65:
                                valueStr = "Stuck";
                                break;
                            case 66:
                                valueStr = "DustBinMissing";
                                break;
                            case 67:
                                valueStr = "DustBinFull";
                                break;
                            case 68:
                                valueStr = "WaterTankEmpty";
                                break;
                            case 69:
                                valueStr = "WaterTankMissing";
                                break;
                            case 70:
                                valueStr = "WaterTankLidOpen";
                                break;
                            case 71:
                                valueStr = "MopCleaningPadMissing";
                                break;
                            case 72:
                                valueStr = "LowBattery";
                                break;
                            case 73:
                                valueStr = "CannotReachTargetArea";
                                break;
                            case 74:
                                valueStr = "DirtyWaterTankFull";
                                break;
                            case 75:
                                valueStr = "DirtyWaterTankMissing";
                                break;
                            case 76:
                                valueStr = "WheelsJammed";
                                break;
                            case 77:
                                valueStr = "BrushJammed";
                                break;
                            case 78:
                                valueStr = "NavigationSensorObscured";
                                break;
                            default:
                                valueStr = "Unknown(" + std::to_string(errorCode) + ")";
                        }
                    } else if (cluster == "servicearea" && attribute == "supported-maps") {
                        std::stringstream mapSs;
                        mapSs << "\nSupportedMaps: " << valueObj.size() << " entries";
                        for (Json::ArrayIndex i = 0; i < valueObj.size(); i++) {
                            unsigned int mapId = valueObj[i]["0"].asUInt();
                            std::string mapName = valueObj[i]["1"].asString();
                            mapSs << "\n  [" << (i + 1) << "]: MapID: " << mapId << ", Name: " << mapName;
                        }
                        valueStr = mapSs.str();
                    } else if (cluster == "servicearea" && attribute == "supported-areas") {
                        // AreaStruct: field 0 = areaID, field 1 = mapID, field 2 = AreaInfoStruct
                        // AreaInfoStruct: field 0 = LocationDescriptorStruct, field 1 = LandmarkInfoStruct
                        // LocationDescriptorStruct: field 0 = locationName, field 1 = floorNumber, field 2 = areaType
                        // LandmarkInfoStruct: field 0 = landmarkTag, field 1 = relativePositionTag
                        std::stringstream areaSs;
                        areaSs << "\nSupportedAreas: " << valueObj.size() << " entries";
                        for (Json::ArrayIndex i = 0; i < valueObj.size(); i++) {
                            unsigned int areaId = valueObj[i]["0"].asUInt();
                            unsigned int mapId = valueObj[i]["1"].asUInt();
                            areaSs << "\n  [" << (i + 1) << "]: AreaID: " << areaId << ", MapID: " << mapId;
                            if (valueObj[i].isMember("2")) {
                                const Json::Value& areaInfo = valueObj[i]["2"];
                                if (areaInfo.isMember("0") && !areaInfo["0"].isNull()) {
                                    const Json::Value& locDesc = areaInfo["0"];
                                    areaSs << ", LocationName: " << (locDesc.isMember("0") ? locDesc["0"].asString() : "");
                                    areaSs << ", FloorNumber: " << (locDesc.isMember("1") && !locDesc["1"].isNull() ? std::to_string(locDesc["1"].asInt()) : "null");
                                    areaSs << ", AreaType: " << (locDesc.isMember("2") && !locDesc["2"].isNull() ? std::to_string(locDesc["2"].asInt()) : "null");
                                } else {
                                    areaSs << ", LocationInfo: null";
                                }
                                if (areaInfo.isMember("1") && !areaInfo["1"].isNull()) {
                                    const Json::Value& landmark = areaInfo["1"];
                                    areaSs << ", LandmarkTag: " << (landmark.isMember("0") ? std::to_string(landmark["0"].asInt()) : "null");
                                    areaSs << ", RelativePositionTag: " << (landmark.isMember("1") && !landmark["1"].isNull() ? std::to_string(landmark["1"].asInt()) : "null");
                                } else {
                                    areaSs << ", LandmarkInfo: null";
                                }
                            }
                        }
                        valueStr = areaSs.str();
                    } else if (cluster == "servicearea" && attribute == "selected-areas") {
                        std::stringstream idsSs;
                        if (valueObj.isArray() && valueObj.size() > 0) {
                            idsSs << "\nSelectedAreas: " << valueObj.size() << " entries";
                            for (Json::ArrayIndex i = 0; i < valueObj.size(); i++) {
                                idsSs << "\n  [" << (i + 1) << "]: " << valueObj[i].asUInt();
                            }
                        } else {
                            idsSs << "empty";
                        }
                        valueStr = idsSs.str();
                    } else if (cluster == "servicearea" && attribute == "current-area") {
                        if (valueObj.isNull()) {
                            valueStr = "null";
                        } else {
                            valueStr = "AreaID: " + std::to_string(valueObj.asUInt());
                        }
                    } else {
                        Json::StreamWriterBuilder writer;
                        writer["indentation"] = "";
                        valueStr = Json::writeString(writer, valueObj);
                    }

                    std::string displayCluster = cluster;
                    if (cluster == "rvcrunmode") displayCluster = "MsrRunmode";
                    else if (cluster == "rvccleanmode") displayCluster = "MsrCleanmode";
                    else if (cluster == "rvcoperationalstate") displayCluster = "MsrOperationalstate";
                    else if (cluster == "servicearea") displayCluster = "Servicearea";

                    std::stringstream reportSs;
                    reportSs << "Report from " << nodeAlias << " " << nodeId
                             << ": " << resultsValue["endpointId"].asInt()
                             << ", Cluster: " << resultsValue["clusterId"].asInt()
                             << ", " << displayCluster << " " << attribute << ": " << valueStr;
                    std::string reportText = reportSs.str();
                    root.put("result", RESPONSE_SUCCESS);
                    root.put("report", reportText);
                    ChipLogError(NotSpecified, "Execute RVC read command successfully");
                } else {
                    root.put("result", RESPONSE_FAILURE);
                    if (resultsValue.isMember("error")) {
                        root.put("cause", resultsValue["error"].asString());
                        ChipLogError(NotSpecified, "Execute RVC read command failed: %s", resultsValue["error"].asString().c_str());
                    } else {
                        ChipLogError(NotSpecified, "Execute RVC read command failed!");
                    }
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
        ChipLogError(NotSpecified, "Error on rvc_read: %s", e.what());
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    }
}

}
