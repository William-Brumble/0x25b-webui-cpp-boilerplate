#pragma once
#include <optional>
#include <vector>

#include "features/note/models/note_model.h"

bool note_srv_init_schema();
std::optional<Note> note_srv_create(const std::string& title, const std::string& content);
std::vector<Note> note_srv_get_all();
std::optional<Note> note_srv_read_by_id(const int64_t id);
std::optional<Note> note_srv_update(const int64_t id, const std::string& new_title, const std::string& new_content);
bool note_srv_delete(const int64_t id);
