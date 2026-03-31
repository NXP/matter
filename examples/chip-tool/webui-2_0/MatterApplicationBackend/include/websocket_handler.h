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

#pragma once

#include "config/asio_no_tls.hpp"
#include "server.hpp"
#include <string>

using WsServer = websocketpp::server<websocketpp::config::asio>;
typedef WsServer::message_ptr message_ptr;

namespace websocket_handler {

void on_message(WsServer* s, websocketpp::connection_hdl hdl, message_ptr msg);
bool validate(WsServer* s, websocketpp::connection_hdl connection);
void websocket_on_http(WsServer* s, websocketpp::connection_hdl hdl);
void generateMessages(WsServer* s, websocketpp::connection_hdl hdl, message_ptr msg,
                      std::string nodeId, std::string nodeAlias);
void generateOtaMessage(WsServer* s, websocketpp::connection_hdl hdl, message_ptr msg,
                        std::string cmd);

}
