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

#include "common.h"
#include "http_routes.h"
#include "websocket_handler.h"

#include <thread>
#include <chrono>

#include "config/asio_no_tls.hpp"
#include "server.hpp"

#include <crow/app.h>
#include <crow/mustache.h>
#include <crow/middlewares/cors.h>

#include "commands/common/Commands.h"
#include "commands/example/ExampleCredentialIssuerCommands.h"
#include "commands/clusters/ReportCommand.h"
#include "commands/discover/Commands.h"
#include "commands/icd/ICDCommand.h"
#include "commands/group/Commands.h"
#include "commands/interactive/Commands.h"
#include "commands/pairing/Commands.h"
#include "commands/payload/Commands.h"
#include "commands/storage/Commands.h"

#include <lib/support/logging/CHIPLogging.h>
#include <zap-generated/cluster/Commands.h>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

WebSocketClient wsClient;
PersistentStorage webCommissionerStorage;
Commands commands;
bool initialized = false;

std::queue<Json::Value> reportQueue;
std::queue<Json::Value> subscribeReportQueue;
std::mutex reportQueueMutex;
std::mutex subscribeReportQueueMutex;

static ExampleCredentialIssuerCommands credIssuerCommands;

static int chipToolInit()
{
    if (initialized)
        return 0;

    initialized = true;
    registerCommandsDiscover(commands, &credIssuerCommands);
    registerCommandsICD(commands, &credIssuerCommands);
    registerCommandsInteractive(commands, &credIssuerCommands);
    registerCommandsPayload(commands);
    registerCommandsPairing(commands, &credIssuerCommands);
    registerCommandsGroup(commands, &credIssuerCommands);
    registerClusters(commands, &credIssuerCommands);
    registerCommandsStorage(commands);
    ChipLogError(NotSpecified, "chipToolInit successfuly");
    return 0;
}

static void enableChipServer()
{
    while (true)
    {
        char * args[] = { (char*)"chip-tool", (char*)"interactive", (char*)"server", (char*)"--port", (char*)"9008" };
        ChipLogError(NotSpecified, "starting the chip-tool interactive servr.");
        int ret = commands.Run(5, args);
        ChipLogError(NotSpecified, "One interactive loop done!!!");
        if (ret)
        {
            ChipLogError(NotSpecified, "interactive return error %d", ret);
            break;
        }
    }
}

static void wsClientConecting()
{
    while (true)
    {
        std::string wsconnetion = wsClient.connection_staus();
        if (wsconnetion != "Closed"){
            ChipLogError(NotSpecified, "The connection between wsClient and chip-tool interactive wsServer is work well.");
        }
        else {
            ChipLogError(NotSpecified, "The connection between wsClient and chip-tool interactive wsServer disconnect and retry connect.");
            wsClient.connect("ws://localhost:9008");
        }
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}

int main()
{
    chipToolInit();
    webCommissionerStorage.Init("web");
    constexpr int SERVER_PORT = 8889;
    constexpr int WS_PORT = 9002;

    std::thread chip_server(enableChipServer);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    wsClient.connect("ws://localhost:9008");
    std::thread wsc(wsClientConecting);

    crow::App<crow::CORSHandler> crowApplication;
    auto& cors = crowApplication.get_middleware<crow::CORSHandler>();

    cors.global()
        .origin("*")
        .methods("GET"_method, "POST"_method, "OPTIONS"_method, "PUT"_method)
        .headers("Content-Type", "Access-Control-Allow-Origin", "Access-Control-Allow-Methods", "Access-Control-Allow-Headers", "Access-Control-Allow-Credentials")
        .allow_credentials();

    crow::mustache::set_global_base(CROW_STATIC_DIRECTORY);

    ChipLogError(NotSpecified, "Using the static directory: %s", CROW_STATIC_DIRECTORY);

    http_routes::registerStaticRoutes(crowApplication);
    http_routes::registerApiRoutes(crowApplication);

    std::thread server_thread([&crowApplication, &SERVER_PORT]() {
        crowApplication.loglevel(crow::LogLevel::Debug);
        crowApplication.port(SERVER_PORT);
        crowApplication.multithreaded().run_async();
    });

    WsServer wsserver;

    try {
        wsserver.set_access_channels(websocketpp::log::alevel::all);
        wsserver.clear_access_channels(websocketpp::log::alevel::frame_payload);

        wsserver.init_asio();
        wsserver.set_http_handler(bind(&websocket_handler::websocket_on_http, &wsserver, ::_1));

        wsserver.set_message_handler(bind(&websocket_handler::on_message, &wsserver, ::_1, ::_2));
        wsserver.set_validate_handler(bind(&websocket_handler::validate, &wsserver, ::_1));

        wsserver.listen(WS_PORT);

        wsserver.start_accept();

        ChipLogError(NotSpecified, "WebSocket server started on port %d", WS_PORT);
        wsserver.run();

    }
    catch (websocketpp::exception const & e)
    {
        ChipLogError(NotSpecified, "WebSocket connection disconnected because: %s", e.what());
    }
    catch (...)
    {
        ChipLogError(NotSpecified, "WebSocket connection disconnected because other exception");
    }

    server_thread.join();
    chip_server.join();
    wsc.join();

    return 0;
}
