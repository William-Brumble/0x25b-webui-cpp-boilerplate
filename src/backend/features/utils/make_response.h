#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

json make_response(const bool error, const std::string &errorMessage,
                   const json &data);
json make_response(const bool error, const std::string &errorMessage);
