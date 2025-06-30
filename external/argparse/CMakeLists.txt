cmake_minimum_required(VERSION 3.15)
project(Argparse LANGUAGES CXX)

add_library(argparse INTERFACE)

add_library(argparse::argparse ALIAS argparse)

target_include_directories(argparse
        INTERFACE SYSTEM $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_compile_features(argparse INTERFACE cxx_std_17)