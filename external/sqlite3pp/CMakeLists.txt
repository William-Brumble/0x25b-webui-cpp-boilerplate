cmake_minimum_required(VERSION 3.15)
project(Sqlite3PP LANGUAGES CXX)

add_library(sqlite3pp STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sqlite3pp/sqlite3pp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sqlite3pp/sqlite3ppext.cpp
)

add_library(sqlite3pp::sqlite3pp ALIAS sqlite3pp)

target_include_directories(sqlite3pp
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_target_properties(sqlite3pp PROPERTIES
        INTERFACE_SYSTEM_INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_compile_features(sqlite3pp PUBLIC cxx_std_17)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(sqlite3pp PRIVATE -w)
elseif (MSVC)
    target_compile_options(sqlite3pp PRIVATE /w)
endif()

target_link_libraries(sqlite3pp PUBLIC sqlite3::sqlite3)
