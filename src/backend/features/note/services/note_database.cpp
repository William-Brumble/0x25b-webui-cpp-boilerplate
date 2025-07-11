#include <vector>
#include <string>
#include <optional>
#include <sqlite3pp/sqlite3pp.h>
#include <spdlog/spdlog.h>

#include "features/note/services/note_database.h"
#include "features/database/database.h"
#include "features/note/models/note_model.h"

bool note_db_init_schema() {
    spdlog::info("note_db_init_schema called");
    try {
        sqlite3pp::command cmd(
            db,
            "CREATE TABLE IF NOT EXISTS notes ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "title TEXT NOT NULL, "
            "content TEXT NOT NULL, "
            "created_at TEXT NOT NULL DEFAULT (datetime('now'))"
            ");"
        );
        cmd.execute();
        spdlog::debug("Schema creation command executed successfully");
        return true;
    } catch (const std::exception& e) {
        const std::string errorMsg =  "Failed to create table: " + std::string(e.what());
        spdlog::error(errorMsg);
        return false;
    }
}

std::optional<Note> note_db_create(const std::string& pTitle, const std::string& pContent) {
    spdlog::info("note_db_create called");
    spdlog::debug("Inserting note with title: {}, content length: {}", pTitle, pContent.size());

    sqlite3pp::query qry(db, "INSERT INTO notes (title, content) VALUES (?, ?) RETURNING id, title, content, created_at;");
    qry.bind(1, pTitle, sqlite3pp::nocopy);
    qry.bind(2, pContent, sqlite3pp::nocopy);

    for (auto row : qry) {
        Note note;
        std::string r_title, r_content, r_created_at;

        row.getter() >> note.id >> r_title >> r_content >> r_created_at;
        note.title = std::move(r_title);
        note.content = std::move(r_content);
        note.created_at = std::move(r_created_at);

        spdlog::debug("Note created: id={}, title={}", note.id, note.title);
        return note;
    }

    spdlog::warn("note_db_create returned no rows");
    return std::nullopt;
}

std::vector<Note> note_db_get_all() {
    spdlog::info("note_db_get_all called");

    std::vector<Note> notes;

    sqlite3pp::query qry(db, "SELECT id, title, content, created_at FROM notes ORDER BY created_at DESC;");
    for (auto row : qry) {
        Note note;
        std::string title, content, created_at;

        row.getter() >> note.id >> title >> content >> created_at;
        note.title = std::move(title);
        note.content = std::move(content);
        note.created_at = std::move(created_at);

        notes.emplace_back(std::move(note));
    }

    spdlog::debug("Retrieved {} notes", notes.size());
    return notes;
}

std::optional<Note> note_db_read_by_id(const int64_t pId) {
    spdlog::info("note_db_read_by_id called with id={}", pId);

    sqlite3pp::query qry(db, "SELECT id, title, content, created_at FROM notes WHERE id = ?;");
    qry.bind(1, static_cast<long long>(pId));

    for (auto row : qry) {
        Note note;
        std::string title, content, created_at;

        row.getter() >> note.id >> title >> content >> created_at;
        note.title = std::move(title);
        note.content = std::move(content);
        note.created_at = std::move(created_at);

        spdlog::debug("Found note with id={}, title={}", note.id, note.title);
        return note;
    }

    spdlog::warn("No note found with id={}", pId);
    return std::nullopt;
}

std::optional<Note> note_db_update(const int64_t pId, const std::string& pNewTitle, const std::string& pNewContent) {
    spdlog::info("note_db_update called with id={}", pId);
    spdlog::debug("New title: {}, new title length: {}", pNewTitle, pNewTitle.size());
    spdlog::debug("New content: {}, new content length: {}", pNewContent, pNewContent.size());

    sqlite3pp::command cmd(db, "UPDATE notes SET title = ?, content = ? WHERE id = ?;");
    cmd.bind(1, pNewTitle, sqlite3pp::nocopy);
    cmd.bind(2, pNewContent, sqlite3pp::nocopy);
    cmd.bind(3, static_cast<long long>(pId));

    const int result = cmd.execute();
    if (result != SQLITE_OK) {
        spdlog::debug("Failed to update note");
        return std::nullopt;
    }

    spdlog::debug("Update succeeded, fetching updated note");
    return note_db_read_by_id(pId);
}

bool note_db_delete(const int64_t pId) {
    spdlog::info("note_db_delete called with id={}", pId);

    sqlite3pp::command cmd(db, "DELETE FROM notes WHERE id = ?;");
    cmd.bind(1, static_cast<long long>(pId));

    const int result = cmd.execute();
    if (result != SQLITE_OK) {
        return false;
    }

    spdlog::debug("Delete result for id {}", pId);
    return true;
}
