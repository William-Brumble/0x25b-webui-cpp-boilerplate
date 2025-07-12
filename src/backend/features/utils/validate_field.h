#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool validate_field(const json &request, const std::string &key,
                    const json::value_t expected_type);
