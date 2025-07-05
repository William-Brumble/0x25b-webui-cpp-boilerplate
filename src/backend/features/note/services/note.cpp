#include <vector>
#include <string>
#include <optional>
#include <spdlog/spdlog.h>  // Added for logging

#include "features/note/services/note_database.h"
#include "features/note/services/note.h"
#include "features/note/models/note_model.h"

bool note_srv_init_schema() {
    spdlog::info("note_srv_init_schema called");
    const bool result = note_db_init_schema();
    spdlog::debug("Schema initialization result: {}", result);
    return result;
}

std::optional<Note> note_srv_create(const std::string& title, const std::string& content) {
    spdlog::info("note_srv_create called");
    spdlog::debug("Creating note with title: {}, content length: {}", title, content.size());
    return note_db_create(title, content);
}

std::vector<Note> note_srv_get_all() {
    spdlog::info("note_srv_get_all called");
    auto notes = note_db_get_all();
    spdlog::debug("Retrieved {} notes", notes.size());
    return notes;
}

std::optional<Note> note_srv_read_by_id(const int64_t id) {
    spdlog::info("note_srv_read_by_id called with ID: {}", id);
    return note_db_read_by_id(id);
}

std::optional<Note> note_srv_update(const int64_t id, const std::string& new_title, const std::string& new_content) {
    spdlog::info("note_srv_update called with ID: {}", id);
    spdlog::debug("New title: {}, new content length: {}", new_title, new_content.size());
    return note_db_update(id, new_title, new_content);
}

bool note_srv_delete(const int64_t id) {
    spdlog::info("note_srv_delete called with ID: {}", id);
    return note_db_delete(id);
    spdlog::debug("Delete success");
}
