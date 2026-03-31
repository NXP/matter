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

#include "utils.h"

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>

#include <lib/support/logging/CHIPLogging.h>

namespace utils {

std::string exec_cmd(const std::string& cmd)
{
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error: popen() failed!" << std::endl;
        exit(1);
    }
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

std::string extractMachineName(const std::string& input)
{
    size_t start = input.find("i.MX");
    if (start == std::string::npos) {
        return "Unknown";
    }

    std::string lowerInput = input;
    std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

    size_t end = lowerInput.find("board", start);
    if (end == std::string::npos) {
        end = input.size();
    }

    std::string machine = input.substr(start, end - start);

    while (!machine.empty() && std::isspace(machine.back())) {
        machine.pop_back();
    }

    return machine;
}

bool killProcesses(const std::string& processName)
{
    char buffer[128];
    std::string result = "";
    std::string cmd = "ps -aux | grep \"" + processName + "\" | grep -v grep | awk '{print $2}'";
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        ChipLogError(NotSpecified, "Error: popen() failed!");
        return false;
    }
    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result = buffer;
    }
    pclose(pipe);

    if (result.empty()) {
        return false;
    }

    ChipLogError(NotSpecified, "Get the pid number: %s of processName: %s", result.c_str(), processName.c_str());
    int pid = std::stoi(result);
    if (pid <= 0) {
        return false;
    }
    std::string command = "kill " + std::to_string(pid);
    if (system(command.c_str())) {
        ChipLogError(NotSpecified, "Failed to kill process.");
        return false;
    } else {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ChipLogError(NotSpecified, "Successfully killed process.");
        return true;
    }
}

} // namespace utils
