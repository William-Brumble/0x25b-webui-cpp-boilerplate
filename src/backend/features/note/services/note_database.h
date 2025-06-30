#pragma once
#include <optional>
#include <vector>

#include "features/note/models/note_model.h"

bool note_db_init_schema();
std::optional<Note> note_db_create(const std::string& title, const std::string& content);
std::vector<Note> note_db_get_all();
std::optional<Note> note_db_read_by_id(const int id);
std::optional<Note> note_db_update(const int id, const std::string& new_title, const std::string& new_content);
bool note_db_delete(const int id);
