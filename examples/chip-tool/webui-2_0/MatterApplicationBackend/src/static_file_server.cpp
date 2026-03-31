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

#include "static_file_server.h"
#include "common.h"

#include <fstream>
#include <iostream>
#include <crow/mustache.h>

namespace static_file_server {

void setContentTypeForFileName(crow::response& res, const std::string& fileName)
{
    if (fileName.find(".html") != std::string::npos) {
        res.add_header("Content-Type", "text/html");
    } else if (fileName.find(".css") != std::string::npos) {
        res.add_header("Content-Type", "text/css");
    } else if (fileName.find(".js") != std::string::npos) {
        res.add_header("Content-Type", "application/javascript");
    } else if (fileName.find(".png") != std::string::npos) {
        res.add_header("Content-Type", "image/png");
    } else if (fileName.find(".jpg") != std::string::npos) {
        res.add_header("Content-Type", "image/jpeg");
    } else if (fileName.find(".ico") != std::string::npos) {
        res.add_header("Content-Type", "image/x-icon");
    } else if (fileName.find(".woff2") != std::string::npos) {
        res.add_header("Content-Type", "font/woff2");
    } else if (fileName.find(".ttf") != std::string::npos) {
        res.add_header("Content-Type", "font/ttf");
    } else {
        res.add_header("Content-Type", "text/plain");
    }
}

void addCrowRouteForStaticFileServer(crow::App<crow::CORSHandler>& crowApplication, const std::string& path)
{
    std::string routePath = "/" + path;
    crowApplication.route_dynamic((const char*)routePath.c_str())
    ([path](const crow::request& req, crow::response& res) {
        crow::mustache::context ctx;
        res.code = 200;
        setContentTypeForFileName(res, path);
        std::ifstream ifs(std::string(CROW_STATIC_DIRECTORY) + path);
        std::string fileContent;
        std::cout << "GET: Got a file from static file server on path:" << path << "\n";
        fileContent.assign(std::istreambuf_iterator<char>(ifs),
                            std::istreambuf_iterator<char>());
        res.write(fileContent);
        res.end();
    });
}

void addCrowRouteForStaticFileServer(crow::App<crow::CORSHandler>& crowApplication, std::string path) {
    path.insert(0, "/");
    crowApplication.route_dynamic((const char*)path.c_str())
    ([path](const crow::request& req, crow::response& res) {
        crow::mustache::context ctx;
        res.code = 200;
        setContentTypeForFileName(res, path);
        std::ifstream ifs(std::string(CROW_STATIC_DIRECTORY) + path);
        std::string fileContent;
        std::cout << "GET: Got a file from static file server on path:" << path << "\n";
        fileContent.assign(std::istreambuf_iterator<char>(ifs),
                            std::istreambuf_iterator<char>());
        res.write(fileContent);
        res.end();
    });
}

void MatterServerApplicationBlueprint(crow::Blueprint& bp)
{
    CROW_BP_ROUTE(bp, "static/")([](const crow::request& req, crow::response& res) {
        crow::mustache::context ctx;
        res.code = 200;
        std::ifstream ifs("index.html");
        std::string fileContent;
        fileContent.assign(std::istreambuf_iterator<char>(ifs),
                            std::istreambuf_iterator<char>());
        res.write(fileContent);
        res.end();
    });
}

}
