#include <webui.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "features/webui/routes/webui_routes.h"
#include "features/webui/webui.h"
#include "features/webui/models/webui_model.h"
#include "features/utils/make_response.h"
#include "features/utils/validate_field.h"

using json = nlohmann::json;

void webui_route_read(webui::window::event *e)
{
    spdlog::info("webui_route_read called");

    std::optional<Settings> settings = webui_srv_read();

    if (!settings)
    {
        spdlog::error("Failed to read settings");
        e->return_string(make_response(true, "Failed to read settings").dump());
        return;
    }

    json response_data;
    response_data["id"] = settings->id;
    response_data["kiosk"] = settings->kiosk;
    response_data["width"] = settings->width;
    response_data["height"] = settings->height;
    response_data["x"] = settings->x;
    response_data["y"] = settings->y;

    spdlog::debug("Returning settings id={}, kiosk={}, width={}, height={}, x={}, y={}", settings->id, settings->kiosk, settings->width, settings->height, settings->x, settings->y);

    const json res = make_response(false, "", response_data);
    e->return_string(res.dump());
}

void webui_route_update_kiosk(webui::window::event *e) {
    spdlog::info("webui_route_set_kiosk called");

    json request;
    std::string payload = e->get_string();
    spdlog::debug("Payload received: {}", payload);

    try {
        request = json::parse(payload);
    } catch (const json::parse_error& err) {
        spdlog::error("JSON parse error: {}", err.what());
        const json res = make_response(true, err.what());
        e->return_string(res.dump());
        return;
    }

    if (!validate_field(request, "kiosk", json::value_t::boolean))
    {
        spdlog::warn("Missing or invalid type for: kiosk");
        e->return_string(make_response(true, "Missing or invalid type for: kiosk").dump());
        return;
    }

    const bool kiosk = request["kiosk"].get<bool>();
    spdlog::debug("Setting kiosk mode to {}", kiosk);

    std::optional<Settings> settings = webui_srv_update_kiosk(kiosk);

    if (!settings)
    {
        spdlog::error("Failed to update kiosk mode");
        e->return_string(make_response(true, "Failed to update kiosk mode").dump());
        return;
    }

    json response_data;
    response_data["id"] = settings->id;
    response_data["kiosk"] = settings->kiosk;
    response_data["width"] = settings->width;
    response_data["height"] = settings->height;
    response_data["x"] = settings->x;
    response_data["y"] = settings->y;

    spdlog::debug("Returning settings id={}, kiosk={}, width={}, height={}, x={}, y={}", settings->id, settings->kiosk, settings->width, settings->height, settings->x, settings->y);

    const json res = make_response(false, "", response_data);
    e->return_string(res.dump());
}

void webui_route_update_size(webui::window::event *e)
{
    spdlog::info("webui_route_set_size called");

    json request;
    std::string payload = e->get_string();
    spdlog::debug("Payload received: {}", payload);

    try {
        request = json::parse(payload);
    } catch (const json::parse_error& err) {
        spdlog::error("JSON parse error: {}", err.what());
        const json res = make_response(true, err.what());
        e->return_string(res.dump());
        return;
    }

    if (!validate_field(request, "width", json::value_t::number_unsigned))
    {
        spdlog::warn("Missing or invalid type for: width");
        e->return_string(make_response(true, "Missing or invalid type for: width").dump());
        return;
    }

    if (!validate_field(request, "height", json::value_t::string))
    {
        spdlog::warn("Missing or invalid type for: height");
        e->return_string(make_response(true, "Missing or invalid type for: height").dump());
        return;
    }

    const int64_t width = request["width"].get<int64_t>();
    const int64_t height = request["height"].get<int64_t>();
    spdlog::debug("Setting size with width: {}, height: {}", width, height);

    std::optional<Settings> settings = webui_srv_update_size(width, height);

    if (!settings)
    {
        spdlog::error("Failed to update size");
        e->return_string(make_response(true, "Failed to update size").dump());
        return;
    }

    json response_data;
    response_data["id"] = settings->id;
    response_data["kiosk"] = settings->kiosk;
    response_data["width"] = settings->width;
    response_data["height"] = settings->height;
    response_data["x"] = settings->x;
    response_data["y"] = settings->y;

    spdlog::debug("Returning settings id={}, kiosk={}, width={}, height={}, x={}, y={}", settings->id, settings->kiosk, settings->width, settings->height, settings->x, settings->y);

    const json res = make_response(false, "", response_data);
    e->return_string(res.dump());
}

void webui_route_update_pos(webui::window::event *e)
{
    spdlog::info("webui_route_set_pos called");

    json request;
    std::string payload = e->get_string();
    spdlog::debug("Payload received: {}", payload);

    try {
        request = json::parse(payload);
    } catch (const json::parse_error& err) {
        spdlog::error("JSON parse error: {}", err.what());
        const json res = make_response(true, err.what());
        e->return_string(res.dump());
        return;
    }

    if (!validate_field(request, "x", json::value_t::number_unsigned))
    {
        spdlog::warn("Missing or invalid type for: x");
        e->return_string(make_response(true, "Missing or invalid type for: x").dump());
        return;
    }

    if (!validate_field(request, "y", json::value_t::string))
    {
        spdlog::warn("Missing or invalid type for: y");
        e->return_string(make_response(true, "Missing or invalid type for: y").dump());
        return;
    }

    const int64_t x = request["x"].get<int64_t>();
    const int64_t y = request["y"].get<int64_t>();
    spdlog::debug("Setting pos with x: {}, y: {}", x, y);

    std::optional<Settings> settings = webui_srv_update_pos(x, y);

    if (!settings)
    {
        spdlog::error("Failed to update pos");
        e->return_string(make_response(true, "Failed to update pos").dump());
        return;
    }

    json response_data;
    response_data["id"] = settings->id;
    response_data["kiosk"] = settings->kiosk;
    response_data["width"] = settings->width;
    response_data["height"] = settings->height;
    response_data["x"] = settings->x;
    response_data["y"] = settings->y;

    spdlog::debug("Returning settings id={}, kiosk={}, width={}, height={}, x={}, y={}", settings->id, settings->kiosk, settings->width, settings->height, settings->x, settings->y);

    const json res = make_response(false, "", response_data);
    e->return_string(res.dump());
}
