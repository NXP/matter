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

#include <string>
#include <json/json.h>

#include "WebSocketClient.h"
#include <controller/ExamplePersistentStorage.h>
#include "commands/common/Commands.h"

// Response constants
#define RESPONSE_SUCCESS "successful"
#define RESPONSE_FAILURE "failed"

// Static directory configuration
#ifndef CROW_FRONTEND_LOCATION
#define CROW_STATIC_DIRECTORY "/usr/share/chip-tool-web/frontend2/"
#elif defined(CROW_FRONTEND_LOCATION)
#define CROW_STATIC_DIRECTORY CROW_FRONTEND_LOCATION
#endif

// Global variables (extern declarations)
extern WebSocketClient wsClient;
extern PersistentStorage webCommissionerStorage;
extern Commands commands;
extern bool initialized;
