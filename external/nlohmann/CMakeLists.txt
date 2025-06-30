cmake_minimum_required(VERSION 3.15)
project(Nlohmann LANGUAGES CXX)

add_library(nlohmann INTERFACE)

add_library(nlohmann::nlohmann ALIAS nlohmann)

target_include_directories(nlohmann
        INTERFACE SYSTEM $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_compile_features(nlohmann INTERFACE cxx_std_17)