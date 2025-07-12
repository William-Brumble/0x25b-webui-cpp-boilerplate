#include <iostream>

#include "features/arguments/arguments.h"
#include "features/database/database.h"
#include "features/logging/logger.h"
#include "features/note/note.h"
#include "features/note/routes/note_routes.h"
#include "features/webui/routes/webui_routes.h"
#include "features/webui/state/webui_state.h"
#include "features/webui/webui.h"
#include "webui.hpp"

void exit(webui::window::event *e) {
    spdlog::info("Exit handler triggered");
    (void)e; // mark as unused
    webui::exit();
}

int main(const int argc, char **argv) {
    std::cout << "Application starting..." << std::endl;

    std::cout << "Parsing arguments..." << std::endl;
    Arguments args = init_args(argc, argv);

    std::cout << "Creating loggers..." << std::endl;
    const std::shared_ptr<spdlog::logger> logger =
        create_logger(args.log_level);
    spdlog::info("Logger created");

    spdlog::info("Initializing database...");
    if (!init_db("database.db")) {
        spdlog::error("Failed to create database");
    } else {
        spdlog::debug("Database initialized successfully");
    }

    spdlog::info("Initializing notes schema...");
    if (!note_srv_init_schema()) {
        spdlog::error("Failed to initialize notes schema");
    } else {
        spdlog::debug("Notes schema initialized successfully");
    }

    spdlog::info("Initializing webui schema...");
    if (!webui_srv_init_schema()) {
        spdlog::error("Failed to initialize webui schema");
    } else {
        spdlog::debug("WebUI schema initialized successfully");
    }

    spdlog::info("Initializing webui...");
    if (!webui_srv_init()) {
        spdlog::error("Failed to initialize webui");
    } else {
        spdlog::debug("WebUI initialized successfully");
    }

    spdlog::info("Binding route handlers to webui window...");
    // note ===================================================================
    window.win.bind("note_route_create", note_route_create);
    window.win.bind("note_route_get_all", note_route_get_all);
    window.win.bind("note_route_read_by_id", note_route_read_by_id);
    window.win.bind("note_route_update", note_route_update);
    window.win.bind("note_route_delete", note_route_delete);
    // webui ==================================================================
    window.win.bind("webui_route_read", webui_route_read);
    window.win.bind("webui_route_update_kiosk", webui_route_update_kiosk);
    window.win.bind("webui_route_update_size", webui_route_update_size);
    window.win.bind("webui_route_update_pos", webui_route_update_pos);
    window.win.bind("exit", exit);
    spdlog::debug("Route handlers bound");

    spdlog::info("Showing webui window...");
    if (!webui_srv_show_window()) {
        spdlog::error("Failed to open webui window");
    } else {
        spdlog::info("WebUI window shown successfully");
    }

    spdlog::info("Application has started");
    webui_srv_wait();

    spdlog::info("Cleaning webui window...");
    webui_srv_clean();

    spdlog::info("Program finished, exiting now");
    return 0;
}

#if defined(_MSC_VER)
#include <shellapi.h> // for CommandLineToArgvW
#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     PSTR lpCmdLine, int nCmdShow) {
    std::cout << "WinMain entry point" << std::endl;

    int argc;
    LPWSTR *argv_w = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (!argv_w) {
        std::cerr << "Failed to parse command line" << std::endl;
        return -1;
    }

    char **argv = new char *[argc];
    for (int i = 0; i < argc; ++i) {
        int len = WideCharToMultiByte(CP_UTF8, 0, argv_w[i], -1, nullptr, 0,
                                      nullptr, nullptr);
        argv[i] = new char[len];
        WideCharToMultiByte(CP_UTF8, 0, argv_w[i], -1, argv[i], len, nullptr,
                            nullptr);
    }

    std::cout << "Converted command line arguments from wide to UTF-8"
              << std::endl;
    int result = main(argc, argv);

    for (int i = 0; i < argc; ++i)
        delete[] argv[i];
    delete[] argv;
    LocalFree(argv_w);

    std::cout << "WinMain exiting with result {}" << std::endl;
    return result;
}
#endif
