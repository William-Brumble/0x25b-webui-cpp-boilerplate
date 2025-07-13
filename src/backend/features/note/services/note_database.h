#pragma once
#include <optional>
#include <vector>

#include "features/note/models/note_model.h"

bool note_db_init_schema();
std::optional<Note> note_db_create(const std::string &pTitle,
                                   const std::string &pContent);
std::vector<Note> note_db_get_all();
std::optional<Note> note_db_read_by_id(const int64_t pId);
std::optional<Note> note_db_update(const int64_t pId,
                                   const std::string &pNewTitle,
                                   const std::string &pNewContent);
bool note_db_delete(const int64_t pId);
