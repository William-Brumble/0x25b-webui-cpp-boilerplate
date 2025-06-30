#include <iostream>
#include <webui.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "features/note/models/note_model.h"
#include "note.h"
#include "features/utils/make_response.h"
#include "features/utils/validate_field.h"

using json = nlohmann::json;

void note_route_create(webui::window::event* event)
{
    spdlog::info("note_route_create called");

    json request;
    std::string payload = event->get_string();
    spdlog::debug("Payload received: {}", payload);

    try {
        request = json::parse(payload);
    } catch (const json::parse_error& err) {
        spdlog::error("JSON parse error: {}", err.what());
        const json res = make_response(true, err.what());
        event->return_string(res.dump());
        return;
    }

    if (!validate_field(request, "title", json::value_t::string))
    {
        spdlog::warn("Missing or invalid type for: title");
        event->return_string(make_response(true, "Missing or invalid type for: title").dump());
        return;
    }

    if (!validate_field(request, "content", json::value_t::string))
    {
        spdlog::warn("Missing or invalid type for: content");
        event->return_string(make_response(true, "Missing or invalid type for: content").dump());
        return;
    }

    const std::string title = request["title"].get<std::string>();
    const std::string content = request["content"].get<std::string>();
    spdlog::debug("Creating note with title: {}, content length: {}", title, content.size());

    std::optional<Note> note = note_srv_create(title, content);

    if (!note)
    {
        spdlog::error("Failed to create note");
        event->return_string(make_response(true, "Failed to create note").dump());
        return;
    }

    spdlog::info("Note created with ID: {}", note->id);

    json response_data;
    response_data["id"] = note->id;
    response_data["title"] = note->title;
    response_data["content"] = note->content;
    response_data["createdAt"] = note->created_at;

    const json res = make_response(false, "", response_data);
    event->return_string(res.dump());
}

void note_route_get_all(webui::window::event* event)
{
    spdlog::info("note_route_get_all called");

    std::vector<Note> notes = note_srv_get_all();
    spdlog::debug("Fetched {} notes", notes.size());

    json response_data = json::array();
    for (const Note& note : notes) {
        json json_note = json::object();
        json_note["id"] = note.id;
        json_note["title"] = note.title;
        json_note["content"] = note.content;
        json_note["createdAt"] = note.created_at;

        response_data.push_back(json_note);
    }

    const json res = make_response(false, "", response_data);
    event->return_string(res.dump());
}

void note_route_read_by_id(webui::window::event* event)
{
    spdlog::info("note_route_read_by_id called");

    json request;
    std::string payload = event->get_string();
    spdlog::debug("Payload received: {}", payload);

    try {
        request = json::parse(payload);
    } catch (const json::parse_error& err) {
        spdlog::error("JSON parse error: {}", err.what());
        const json res = make_response(true, err.what());
        event->return_string(res.dump());
        return;
    }

    if (!validate_field(request, "id", json::value_t::number_integer))
    {
        spdlog::warn("Missing or invalid type for: id");
        event->return_string(make_response(true, "Missing or invalid type for: id").dump());
        return;
    }

    const int id = request["id"].get<int>();
    spdlog::debug("Reading note with ID: {}", id);

    std::optional<Note> note = note_srv_read_by_id(id);

    if (!note)
    {
        spdlog::error("Note with ID {} not found", id);
        event->return_string(make_response(true, "Failed to read note").dump());
        return;
    }

    spdlog::info("Note retrieved: ID {}", note->id);

    json response_data;
    response_data["id"] = note->id;
    response_data["title"] = note->title;
    response_data["content"] = note->content;
    response_data["createdAt"] = note->created_at;

    const json res = make_response(false, "", response_data);
    event->return_string(res.dump());
}

void note_route_update(webui::window::event* event)
{
    spdlog::info("note_route_update called");

    json request;
    std::string payload = event->get_string();
    spdlog::debug("Payload received: {}", payload);

    try {
        request = json::parse(payload);
    } catch (const json::parse_error& err) {
        spdlog::error("JSON parse error: {}", err.what());
        const json res = make_response(true, err.what());
        event->return_string(res.dump());
        return;
    }

    if (!validate_field(request, "id", json::value_t::number_integer))
    {
        spdlog::warn("Missing or invalid type for: id");
        event->return_string(make_response(true, "Missing or invalid type for: id").dump());
        return;
    }

    if (!validate_field(request, "title", json::value_t::string))
    {
        spdlog::warn("Missing or invalid type for: title");
        event->return_string(make_response(true, "Missing or invalid type for: title").dump());
        return;
    }

    if (!validate_field(request, "content", json::value_t::string))
    {
        spdlog::warn("Missing or invalid type for: content");
        event->return_string(make_response(true, "Missing or invalid type for: content").dump());
        return;
    }

    const int id = request["id"].get<int>();
    const std::string title = request["title"].get<std::string>();
    const std::string content = request["content"].get<std::string>();
    spdlog::debug("Updating note ID {} with title: {}, content length: {}", id, title, content.size());

    std::optional<Note> note = note_srv_update(id, title, content);

    if (!note)
    {
        spdlog::error("Failed to update note ID: {}", id);
        event->return_string(make_response(true, "Failed to update note").dump());
        return;
    }

    spdlog::info("Note updated successfully: ID {}", note->id);

    json response_data;
    response_data["id"] = note->id;
    response_data["title"] = note->title;
    response_data["content"] = note->content;
    response_data["createdAt"] = note->created_at;

    const json res = make_response(false, "", response_data);
    event->return_string(res.dump());
}

void note_route_delete(webui::window::event* event)
{
    spdlog::info("note_route_delete called");

    json request;
    std::string payload = event->get_string();
    spdlog::debug("Payload received: {}", payload);

    try {
        request = json::parse(payload);
    } catch (const json::parse_error& err) {
        spdlog::error("JSON parse error: {}", err.what());
        const json res = make_response(true, err.what());
        event->return_string(res.dump());
        return;
    }

    if (!validate_field(request, "id", json::value_t::number_integer))
    {
        spdlog::warn("Missing or invalid type for: id");
        event->return_string(make_response(true, "Missing or invalid type for: id").dump());
        return;
    }

    const int id = request["id"].get<int>();
    spdlog::debug("Attempting to delete note with ID: {}", id);

    const bool success = note_srv_delete(id);
    if (!success)
    {
        spdlog::error("Failed to delete note with ID: {}", id);
        event->return_string(make_response(true, "Failed to delete note").dump());
        return;
    }

    spdlog::info("Note deleted successfully: ID {}", id);

    const json res = make_response(false, "");
    event->return_string(res.dump());
}
