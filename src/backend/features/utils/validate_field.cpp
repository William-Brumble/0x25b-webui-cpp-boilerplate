#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool validate_field(const json &request, const std::string &key,
                    const json::value_t expected_type) {
    if (!request.contains(key)) {
        return false;
    }

    if (request[key].type() != expected_type) {
        return false;
    }

    return true;
}
