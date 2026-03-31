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

#include "http_routes.h"
#include "common.h"
#include "static_file_server.h"

#include "api_handlers/pairing_handler.h"
#include "api_handlers/onoff_handler.h"
#include "api_handlers/network_handler.h"
#include "api_handlers/media_handler.h"
#include "api_handlers/eevse_handler.h"
#include "api_handlers/rvc_handler.h"
#include "api_handlers/ota_handler.h"
#include "api_handlers/binding_handler.h"
#include "api_handlers/misc_handler.h"

#include <fstream>
#include <algorithm>
#include <iterator>
#include <boost/filesystem.hpp>
#include <crow/mustache.h>
#include <lib/support/logging/CHIPLogging.h>

namespace http_routes {

void registerStaticRoutes(crow::App<crow::CORSHandler>& crowApplication)
{
    CROW_ROUTE(crowApplication, "/")([](const crow::request& req, crow::response& res) {
        crow::mustache::context ctx;
        res.code = 200;
        res.add_header("Content-Type", "text/html");
        std::ifstream ifs(std::string(CROW_STATIC_DIRECTORY) + "index.html");
        std::string fileContent;
        fileContent.assign(std::istreambuf_iterator<char>(ifs),
                            std::istreambuf_iterator<char>());
        res.write(fileContent);
        res.end();
    });

    CROW_ROUTE(crowApplication, "/<string>")
    ([&](const crow::request& req, crow::response& res, std::string path) {
        crow::mustache::context ctx;
        res.code = 200;
        static_file_server::setContentTypeForFileName(res, path);
        if (path == "devices" || path == "dashboard" || path == "subscriptions" || path == "audio" || path == "help"){
            res.set_header("Content-Type", "text/html");
            std::ifstream ifs(std::string(CROW_STATIC_DIRECTORY) + "index.html");
            std::string fileContent;
            fileContent.assign(std::istreambuf_iterator<char>(ifs),
                                std::istreambuf_iterator<char>());
            res.write(fileContent);
            res.end();
        } else {
            std::ifstream ifs(std::string(CROW_STATIC_DIRECTORY) + path);
            std::string fileContent;
            fileContent.assign(std::istreambuf_iterator<char>(ifs),
                                std::istreambuf_iterator<char>());
            res.write(fileContent);
            res.end();
        }
    });

    CROW_ROUTE(crowApplication, "/assets/<string>")
    ([&](const crow::request& req, crow::response& res, std::string path) {
        crow::mustache::context ctx;
        res.code = 200;
        static_file_server::setContentTypeForFileName(res, path);
        std::ifstream ifs(std::string(CROW_STATIC_DIRECTORY) + "assets/" + path);
        std::string fileContent;
        fileContent.assign(std::istreambuf_iterator<char>(ifs),
                            std::istreambuf_iterator<char>());
        res.write(fileContent);
        res.end();
    });

    CROW_ROUTE(crowApplication, "/assets/endpoint/<string>")
    ([&](const crow::request& req, crow::response& res, std::string path) {
        crow::mustache::context ctx;
        res.code = 200;
        static_file_server::setContentTypeForFileName(res, path);
        std::ifstream ifs(std::string(CROW_STATIC_DIRECTORY) + "assets/endpoint/" + path);
        std::string fileContent;
        fileContent.assign(std::istreambuf_iterator<char>(ifs),
                            std::istreambuf_iterator<char>());
        res.write(fileContent);
        res.end();
    });

    CROW_ROUTE(crowApplication, "/assets/matteradvantages/<string>")
    ([&](const crow::request& req, crow::response& res, std::string path) {
        crow::mustache::context ctx;
        res.code = 200;
        static_file_server::setContentTypeForFileName(res, path);
        std::ifstream ifs(std::string(CROW_STATIC_DIRECTORY) + "assets/matteradvantages/" + path);
        std::string fileContent;
        fileContent.assign(std::istreambuf_iterator<char>(ifs),
                            std::istreambuf_iterator<char>());
        res.write(fileContent);
        res.end();
    });

    CROW_ROUTE(crowApplication, "/assets/download/<string>")
    ([&](const crow::request& req, crow::response& res, std::string path) {
        crow::mustache::context ctx;
        res.code = 200;
        static_file_server::setContentTypeForFileName(res, path);
        std::ifstream ifs(std::string(CROW_STATIC_DIRECTORY) + "assets/download/" + path);
        std::string fileContent;
        fileContent.assign(std::istreambuf_iterator<char>(ifs),
                            std::istreambuf_iterator<char>());
        res.write(fileContent);
        res.end();
    });

    CROW_ROUTE(crowApplication, "/media/<string>")
    ([&](const crow::request& req, crow::response& res, std::string path) {
        crow::mustache::context ctx;
        res.code = 200;
        static_file_server::setContentTypeForFileName(res, path);
        std::ifstream ifs(std::string(CROW_STATIC_DIRECTORY) + "media/" + path);
        std::string fileContent;
        fileContent.assign(std::istreambuf_iterator<char>(ifs),
                            std::istreambuf_iterator<char>());
        res.write(fileContent);
        res.end();
    });
}

void registerApiRoutes(crow::App<crow::CORSHandler>& crowApplication)
{
    CROW_ROUTE(crowApplication, "/api/string").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleApiString(req);
    });

    CROW_ROUTE(crowApplication, "/api/json").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleApiJson(req);
    });

    CROW_ROUTE(crowApplication, "/api/info").methods("GET"_method)([](const crow::request& req) {
        return api_handlers::handleApiInfo(req);
    });

    CROW_ROUTE(crowApplication, "/api/match/<int>").methods("GET"_method)([](int i) {
        return api_handlers::handleApiMatch(i);
    });

    CROW_ROUTE(crowApplication, "/api/pairing").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handlePairing(req);
    });

    CROW_ROUTE(crowApplication, "/api/get_dataset").methods("GET"_method)([]() {
        return api_handlers::handleGetDataset();
    });

    CROW_ROUTE(crowApplication, "/api/onoff_report").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleOnoffReport(req);
    });

    CROW_ROUTE(crowApplication, "/api/onoff").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleOnoff(req);
    });

    CROW_ROUTE(crowApplication, "/api/multiadmin").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleMultiadmin(req);
    });

    CROW_ROUTE(crowApplication, "/api/get_status").methods("GET"_method)([]() {
        return api_handlers::handleGetStatus();
    });

    CROW_ROUTE(crowApplication, "/api/get_network").methods("GET"_method)([]() {
        return api_handlers::handleGetNetwork();
    });

    CROW_ROUTE(crowApplication, "/api/delete_storageNode").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleDeleteStorageNode(req);
    });

    CROW_ROUTE(crowApplication, "/api/write_acl").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleWriteAcl(req);
    });

    CROW_ROUTE(crowApplication, "/api/write_binding").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleWriteBinding(req);
    });

    CROW_ROUTE(crowApplication, "/api/launcher").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleLauncher(req);
    });

    CROW_ROUTE(crowApplication, "/api/media_control").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleMediaControl(req);
    });

    CROW_ROUTE(crowApplication, "/api/media_read").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleMediaRead(req);
    });

    CROW_ROUTE(crowApplication, "/api/event_trigger").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleEventTrigger(req);
    });

    CROW_ROUTE(crowApplication, "/api/eevse_control").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleEevseControl(req);
    });

    CROW_ROUTE(crowApplication, "/api/eevse_read").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleEevseRead(req);
    });

    CROW_ROUTE(crowApplication, "/api/rvc_control").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleRvcControl(req);
    });

    CROW_ROUTE(crowApplication, "/api/rvc_read").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleRvcRead(req);
    });

    CROW_ROUTE(crowApplication, "/api/uploader").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleUploader(req);
    });

    CROW_ROUTE(crowApplication, "/api/otasoftwareupdaterequestor").methods("POST"_method)([](const crow::request& req) {
        return api_handlers::handleOtaSoftwareUpdateRequestor(req);
    });

    CROW_ROUTE(crowApplication, "/api/getAvailableNetwork").methods("GET"_method)([&](const crow::request& req) {
        return api_handlers::handleGetAvailableNetwork(req);
    });

    char* frontend_path = getenv("CHIP_TOOL_WEB_FRONTEND");
    if (frontend_path == nullptr) {
        frontend_path = (char*)"/home/matthewalgo/Matter2023Q4/examples/chip-tool/webui/frontend";
    }

    CROW_ROUTE(crowApplication, "/api/").methods("GET"_method)([frontend_path](const crow::request& req) {
        try
        {
            auto web_root_path = boost::filesystem::canonical(frontend_path);
            auto path          = boost::filesystem::canonical(web_root_path / "index.html");
            if (std::distance(web_root_path.begin(), web_root_path.end()) > std::distance(path.begin(), path.end()) ||
                !std::equal(web_root_path.begin(), web_root_path.end(), path.begin()))
                throw std::invalid_argument("Path must be within root path");
            if (boost::filesystem::is_directory(path))
                path /= "index.html";
            if (!(boost::filesystem::exists(path) && boost::filesystem::is_regular_file(path)))
                throw std::invalid_argument("File does not exist");
            ChipLogError(NotSpecified, "Path to index.html: %s", path.string().c_str());
            std::ifstream ifs(path.string());
            std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
            crow::response response(content);
            response.add_header("Access-Control-Allow-Origin", "*");
            return response;
        } catch (const std::exception &e) {
            crow::response response(400, e.what());
            response.add_header("Access-Control-Allow-Origin", "*");
            return response;
        }
    });

    CROW_ROUTE(crowApplication, "/api/{resource:.*}").methods("GET"_method)([frontend_path](const crow::request& req) {
        try
        {
            auto web_root_path = boost::filesystem::canonical(frontend_path);
            auto path          = boost::filesystem::canonical(web_root_path / req.url);
            if (std::distance(web_root_path.begin(), web_root_path.end()) > std::distance(path.begin(), path.end()) ||
                !std::equal(web_root_path.begin(), web_root_path.end(), path.begin()))
                throw std::invalid_argument("Path must be within root path");
            if (boost::filesystem::is_directory(path))
                path /= "index.html";
            if (!(boost::filesystem::exists(path) && boost::filesystem::is_regular_file(path)))
                throw std::invalid_argument("File does not exist");
            ChipLogError(NotSpecified, "Path to resource file: %s", path.string().c_str());
            std::ifstream ifs(path.string());
            std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
            crow::response response(content);
            response.add_header("Access-Control-Allow-Origin", "*");
            return response;
        } catch (const std::exception &e) {
            crow::response response(400, e.what());
            response.add_header("Access-Control-Allow-Origin", "*");
            return response;
        }
    });
}

}
