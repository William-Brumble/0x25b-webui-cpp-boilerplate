#include <vector>
#include <string>
#include <optional>
#include <spdlog/spdlog.h>

#include "features/note/note.h"
#include "features/note/services/note_database.h"
#include "features/note/models/note_model.h"

bool note_srv_init_schema() {
    spdlog::info("note_srv_init_schema called");
    const bool result = note_db_init_schema();
    spdlog::debug("Schema initialization result: {}", result);
    return result;
}

std::optional<Note> note_srv_create(const std::string& pTitle, const std::string& pContent) {
    spdlog::info("note_srv_create called");
    spdlog::debug("Creating note with title: {}, content length: {}", pTitle, pContent.size());
    return note_db_create(pTitle, pContent);
}

std::vector<Note> note_srv_get_all() {
    spdlog::info("note_srv_get_all called");
    auto notes = note_db_get_all();
    spdlog::debug("Retrieved {} notes", notes.size());
    return notes;
}

std::optional<Note> note_srv_read_by_id(const int64_t pId) {
    spdlog::info("note_srv_read_by_id called with ID: {}", pId);
    return note_db_read_by_id(pId);
}

std::optional<Note> note_srv_update(const int64_t pId, const std::string& pNewTitle, const std::string& pNewContent) {
    spdlog::info("note_srv_update called with ID: {}", pId);
    spdlog::debug("New title: {}, new content length: {}", pNewTitle, pNewContent.size());
    return note_db_update(pId, pNewTitle, pNewContent);
}

bool note_srv_delete(const int64_t pId) {
    spdlog::info("note_srv_delete called with ID: {}", pId);
    return note_db_delete(pId);
}
