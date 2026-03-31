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

#include "storage_utils.h"
#include "common.h"

#include <fstream>
#include <string>

#include <lib/support/logging/CHIPLogging.h>

namespace storage_utils {

Json::Value getStorageKeyNodeID()
{
    Json::Value storageNodes(Json::arrayValue);
    const char * storageWebDirectory = webCommissionerStorage.GetDirectory();
    std::string storageWebFile = std::string(storageWebDirectory) + "/chip_tool_config.web.ini";
    std::ifstream ifs(storageWebFile, std::ios::in);
    if (!ifs.is_open())
    {
        ChipLogError(NotSpecified, "Failed to open storage file chip_tool_config.web.ini.");
        return Json::Value();
    }
    std::string line;
    std::getline(ifs, line);
    while(std::getline(ifs, line))
    {
        size_t equalsPos = line.find('=');
        if (equalsPos != std::string::npos)
        {
            std::string storageNodeAlias = line.substr(0, equalsPos);
            chip::NodeId storageNodeId = webCommissionerStorage.GetLocalKeyNodeId(storageNodeAlias.c_str());
            Json::Value storageNode(Json::objectValue);
            storageNode["storageNodeAlias"] = storageNodeAlias.c_str();
            storageNode["storageNodeId"] = static_cast<int>(storageNodeId);
            storageNodes.append(storageNode);
        }
    }
    ifs.close();

    ChipLogError(NotSpecified, "Get web local storage node alias and nodeID successfully.");
    return storageNodes;
}

} // namespace storage_utils
