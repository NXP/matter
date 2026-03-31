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

#include "api_handlers/misc_handler.h"

#include <sstream>

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace boost::property_tree;

namespace api_handlers {

crow::response handleApiString(const crow::request& req)
{
    crow::response response(req.body);
    response.add_header("Access-Control-Allow-Origin", "*");
    return response;
}

crow::response handleApiJson(const crow::request& req)
{
    try
    {
        ptree pt;
        std::istringstream iss(req.body);
        read_json(iss, pt);

        auto name = pt.get<std::string>("firstName") + " " + pt.get<std::string>("lastName");
        crow::response response(name);
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    }
    catch(const std::exception &e)
    {
        crow::response response(400, e.what());
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    }
}

crow::response handleApiInfo(const crow::request& req)
{
    std::ostringstream stream;
    ptree pt;
    for(auto &field : req.headers)
        pt.put(field.first, field.second);
    pt.put("Server", "CrowServer");

    std::stringstream ss;
    write_json(ss, pt);
    std::string strContent = ss.str();
    crow::response response(strContent);
    return response;
}

crow::response handleApiMatch(int i)
{
    crow::response response(std::to_string(i));
    response.add_header("Access-Control-Allow-Origin", "*");
    return response;
}

}
