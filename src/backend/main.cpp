#include <iostream>

#include "webui.hpp"
#include "vfs.h" // Generated using: python vfs.py "/path/to/folder" "vfs.h"
#include "features/database/database.h"
#include "features/arguments/arguments.h"
#include "features/logging/logger.h"
#include "features/note/note.h"
#include "features/note/note_routes.h"

void exit(webui::window::event *e)
{
    spdlog::info("Exit handler triggered");
    (void)e; // mark as unused
    webui::exit();
}

int main(const int argc, char** argv)
{
    std::cout << "Application starting..." << std::endl;

    std::cout << "Parsing arguments..." << std::endl;
    Arguments args = init_args(argc, argv);

    std::cout << "Creating loggers..." << std::endl;
    const std::shared_ptr<spdlog::logger> logger = create_logger(args.log_level);
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

    spdlog::info("Creating webui window...");
    constexpr int windowWidth = 550;
    constexpr int windowHeight = 450;
    constexpr int windowPosX = 250;
    constexpr int windowPosY = 250;
    constexpr auto entryFile = "index.html";
    webui::window win;
    webui::set_config(multi_client, true);
    webui::set_config(use_cookies, false);
    win.set_size(windowWidth, windowHeight);
    win.set_position(windowPosX, windowPosY);
    win.set_file_handler(vfs);
    spdlog::debug("WebUI window configured: size={}x{}, pos={}x{}", windowWidth, windowHeight, windowPosX, windowPosY);

    spdlog::info("Binding route handlers to webui window...");
    win.bind("note_route_create", note_route_create);
    win.bind("note_route_get_all", note_route_get_all);
    win.bind("note_route_read_by_id", note_route_read_by_id);
    win.bind("note_route_update", note_route_update);
    win.bind("note_route_delete", note_route_delete);
    win.bind("exit", exit);
    spdlog::debug("Route handlers bound");

    spdlog::info("Showing webui window...");
    if (!win.show(entryFile)) {
        spdlog::error("Failed to open webui window");
    } else {
        spdlog::info("WebUI window shown successfully");
    }

    spdlog::info("Application has started");
    webui_wait();

    spdlog::info("Cleaning webui window...");
    webui_clean();

    spdlog::info("Program finished, exiting now");
    return 0;
}

#if defined(_MSC_VER)
#include <windows.h>
#include <shellapi.h>  // for CommandLineToArgvW

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    std::cout << "WinMain entry point" << std::endl;

    int argc;
    LPWSTR* argv_w = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (!argv_w) {
        std::cerr << "Failed to parse command line" << std::endl;
        return -1;
    }

    char** argv = new char*[argc];
    for (int i = 0; i < argc; ++i) {
        int len = WideCharToMultiByte(CP_UTF8, 0, argv_w[i], -1, nullptr, 0, nullptr, nullptr);
        argv[i] = new char[len];
        WideCharToMultiByte(CP_UTF8, 0, argv_w[i], -1, argv[i], len, nullptr, nullptr);
    }

    std::cout << "Converted command line arguments from wide to UTF-8" << std::endl;
    int result = main(argc, argv);

    for (int i = 0; i < argc; ++i)
        delete[] argv[i];
    delete[] argv;
    LocalFree(argv_w);

    std::cout << "WinMain exiting with result {}" << std::endl;
    return result;
}
#endif
