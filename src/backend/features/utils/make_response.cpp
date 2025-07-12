#include <nlohmann/json.hpp>

#include "features/utils/make_response.h"

using json = nlohmann::json;

json make_response(const bool error, const std::string &errorMessage,
                   const json &data) {
    json response;
    response["error"] = error;
    response["errorMessage"] = errorMessage;
    response["data"] = data;
    return response;
}

json make_response(const bool error, const std::string &errorMessage) {
    json response = make_response(error, errorMessage, json::object());
    return response;
}
