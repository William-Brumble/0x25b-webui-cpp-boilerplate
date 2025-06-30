cmake_minimum_required(VERSION 3.15)
project(Sqlite3 LANGUAGES CXX)

add_library(sqlite3 STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sqlite3/shell.c
        ${CMAKE_CURRENT_SOURCE_DIR}/sqlite3/sqlite3.c
)

add_library(sqlite3::sqlite3 ALIAS sqlite3)

# Mark includes as SYSTEM for consumers (e.g., program)
target_include_directories(sqlite3
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sqlite3>
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sqlite3>
)

set_target_properties(sqlite3 PROPERTIES
        INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sqlite3>
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(sqlite3 PRIVATE -w)
elseif (MSVC)
    target_compile_options(sqlite3 PRIVATE /w)
endif()

target_compile_features(sqlite3 PUBLIC cxx_std_17)
