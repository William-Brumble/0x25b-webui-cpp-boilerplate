cmake_minimum_required(VERSION 3.15)
project(webui-wrapper LANGUAGES CXX)

add_subdirectory(webui)

add_library(webui::webui ALIAS webui)

target_include_directories(webui
        INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/webui/include>
)

set_target_properties(webui PROPERTIES
        INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/webui/include>
)
