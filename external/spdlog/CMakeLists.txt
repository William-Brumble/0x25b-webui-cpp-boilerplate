cmake_minimum_required(VERSION 3.15)
project(Spdlog LANGUAGES CXX)

add_library(spdlog INTERFACE)

add_library(spdlog::spdlog ALIAS spdlog)

target_include_directories(spdlog
        INTERFACE SYSTEM $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_compile_features(spdlog INTERFACE cxx_std_17)