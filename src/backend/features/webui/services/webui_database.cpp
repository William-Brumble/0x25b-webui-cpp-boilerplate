#include <optional>
#include <spdlog/spdlog.h>
#include <sqlite3pp/sqlite3pp.h>

#include "features/database/database.h"
#include "features/webui/models/webui_model.h"

bool webui_db_init_schema() {
    spdlog::info("webui_db_init_schema called");
    try {
        sqlite3pp::command cmd(
            db,
            "CREATE TABLE webui ("
            "    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
            "    kiosk INTEGER,"
            "    size_width INTEGER,"
            "    size_height INTEGER,"
            "    pos_x INTEGER,"
            "    pos_y INTEGER"
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

std::optional<Settings> webui_db_read_first() {
    spdlog::info("webui_db_read_first called");

    sqlite3pp::query qry(db, "SELECT id, kiosk, size_width, size_height, pos_x, pos_y FROM webui LIMIT 1;");

    for (auto row : qry) {
        Settings settings;
        int kiosk, width, height, x, y;

        row.getter() >> settings.id >> kiosk >> width >> height >> x >> y;
        settings.width = width;
        settings.height = height;
        settings.x = x;
        settings.y = y;
        settings.kiosk = kiosk != 0;

        spdlog::debug("Found settings with id={}, kiosk={}, width={}, height={}, x={}, y={}",
                      settings.id, settings.kiosk, settings.width, settings.height, settings.x, settings.y);

        return settings;
    }

    spdlog::warn("No settings found");
    return std::nullopt;
}

std::optional<Settings> webui_db_read_by_id(const int64_t pId) {
    spdlog::info("webui_db_read_by_id called with id={}", pId);

    sqlite3pp::query qry(db, "SELECT id, kiosk, size_width, size_height, pos_x, pos_y FROM webui WHERE id = ?;");
    qry.bind(1, pId);

    for (auto row : qry) {
        Settings settings;
        int kiosk, width, height, x, y;

        row.getter() >> settings.id >> kiosk >> width >> height >> x >> y;
        settings.width = width;
        settings.height = height;
        settings.x = x;
        settings.y = y;

        if (kiosk) {
            settings.kiosk = true;
        } else {
            settings.kiosk = false;
        }

        spdlog::debug("Found settings with id={}, kiosk={}, width={}, height={}, x={}, y={}", settings.id, settings.kiosk, settings.width, settings.height, settings.x, settings.y);
        return settings;
    }

    spdlog::warn("No settings found with id={}", pId);
    return std::nullopt;
}

std::optional<Settings> webui_db_create(const bool pKiosk, const int64_t pWidth, const int64_t pHeight, const int64_t pX, const int64_t pY) {
    spdlog::info("webui_db_create called");
    spdlog::debug("Inserting settings with kiosk={}, width={}, height={}, x={}, y={}", pKiosk, pWidth, pHeight, pX, pY);

    sqlite3pp::query qry(db, "INSERT INTO webui (kiosk, size_width, size_height, pos_x, pos_y) VALUES (?, ?, ?, ?, ?) RETURNING id, kiosk, size_width, size_height, pos_x, pos_y;");
    qry.bind(1, pKiosk ? 1 : 0);
    qry.bind(2, pWidth);
    qry.bind(3, pHeight);
    qry.bind(4, pX);
    qry.bind(5, pY);

    for (auto row : qry) {
        Settings settings;
        int kiosk, width, height, x, y;

        row.getter() >> settings.id >> kiosk >> width >> height >> x >> y;
        settings.kiosk = kiosk != 0;
        settings.width = width;
        settings.height = height;
        settings.x = x;
        settings.y = y;

        spdlog::debug("Created settings: id={}, kiosk={}, width={}, height={}, x={}, y={}", settings.id, settings.kiosk, settings.width, settings.height, settings.x, settings.y);
        return settings;
    }

    spdlog::warn("webui_db_create returned no rows");
    return std::nullopt;
}

std::optional<Settings> webui_db_update_kiosk(const int64_t pId, const bool pKiosk) {
    spdlog::info("webui_db_update_kiosk called with id={}", pId);
    spdlog::debug("New kiosk: {}", pKiosk);

    sqlite3pp::command cmd(db, "UPDATE webui SET kiosk = ? WHERE id = ?;");
    cmd.bind(1, pKiosk);
    cmd.bind(2, pId);

    const int result = cmd.execute();
    if (result != SQLITE_OK) {
        spdlog::debug("Failed to update kiosk");
        return std::nullopt;
    }

    spdlog::debug("Update succeeded, fetching updated settings");
    return webui_db_read_by_id(pId);
}


std::optional<Settings> webui_db_update_size(const int64_t pId, const int64_t pWidth, const int64_t pHeight) {
    spdlog::info("webui_db_update_size called with id={}", pId);
    spdlog::debug("New width: {}, new height: {}", pWidth, pHeight);

    sqlite3pp::command cmd(db, "UPDATE webui SET size_width = ?, size_height = ? WHERE id = ?;");
    cmd.bind(1, pWidth);
    cmd.bind(2, pHeight);
    cmd.bind(3, pId);

    const int result = cmd.execute();
    if (result != SQLITE_OK) {
        spdlog::debug("Failed to update size");
        return std::nullopt;
    }

    spdlog::debug("Update succeeded, fetching updated settings");
    return webui_db_read_by_id(pId);
}

std::optional<Settings> webui_db_update_pos(const int64_t pId, const int64_t pX, const int64_t pY) {
    spdlog::info("webui_db_update_pos called with id={}", pId);
    spdlog::debug("New x: {}, new y: {}", pX, pY);

    sqlite3pp::command cmd(db, "UPDATE webui SET pos_x = ?, pos_y = ? WHERE id = ?;");
    cmd.bind(1, pX);
    cmd.bind(2, pY);
    cmd.bind(3, pId);

    const int result = cmd.execute();
    if (result != SQLITE_OK) {
        spdlog::debug("Failed to update pos");
        return std::nullopt;
    }

    spdlog::debug("Update succeeded, fetching updated settings");
    return webui_db_read_by_id(pId);
}
