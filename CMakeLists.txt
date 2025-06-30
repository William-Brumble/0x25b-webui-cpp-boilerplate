cmake_minimum_required(VERSION 3.15)

# Project metadata
project(program VERSION 1.0 LANGUAGES C CXX)

# Allow custom build types like "Frontend"
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo;MinSizeRel;Frontend" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_FRONTEND "-O0 -g -DFRONTEND_MODE" CACHE STRING "Flags used for the Frontend build type")

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# === frontend build & VFS ====================================================
find_package(Python3 REQUIRED)

set(FRONTEND_DIR ${PROJECT_SOURCE_DIR}/src/frontend)
set(FRONTEND_BUILD_DIR ${FRONTEND_DIR}/dist)
set(VFS_SCRIPT ${PROJECT_SOURCE_DIR}/src/backend/vfs.py)
set(VFS_OUTPUT ${PROJECT_SOURCE_DIR}/src/backend/vfs.h)

# Always define the frontend build target (for manual use)
add_custom_target(frontend
        COMMAND ${CMAKE_COMMAND} -E echo "Running frontend build..."
        COMMAND npm install
        COMMAND npm run build
        COMMAND ${CMAKE_COMMAND} -E echo "Generating vfs.h..."
        COMMAND ${Python3_EXECUTABLE} ${VFS_SCRIPT} ${FRONTEND_BUILD_DIR} ${VFS_OUTPUT}
        WORKING_DIRECTORY ${FRONTEND_DIR}
        COMMENT "Building frontend and embedding assets"
)

# Only build C++ backend if not in Frontend-only mode
if(NOT CMAKE_BUILD_TYPE STREQUAL "Frontend")

    # Check that VFS output and frontend build assets exist before building
    if(NOT EXISTS "${VFS_OUTPUT}")
        message(FATAL_ERROR "Missing required file: ${VFS_OUTPUT}. Run `cmake --build . --target frontend` first.")
    endif()

    # Source files
    file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)

    # Executable target
    add_executable(program ${SOURCES})
    target_include_directories(program PRIVATE ${PROJECT_SOURCE_DIR}/src/backend)

    # Warnings
    if (MSVC)
        target_compile_options(program PRIVATE /W4 /permissive-)
    else()
        target_compile_options(program PRIVATE -Wall -Wextra -Wpedantic)
    endif()

    # External libraries
    add_subdirectory(external/nlohmann)
    add_subdirectory(external/argparse)
    add_subdirectory(external/spdlog)
    add_subdirectory(external/webui)
    add_subdirectory(external/sqlite3)
    add_subdirectory(external/sqlite3pp)

    # Linking
    target_link_libraries(program PRIVATE
            argparse::argparse
            nlohmann::nlohmann
            spdlog::spdlog
            sqlite3pp::sqlite3pp
            webui::webui
            ws2_32
    )
endif()
