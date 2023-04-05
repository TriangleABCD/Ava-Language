cmake_minimum_required(VERSION 3.10)

project(ava_parser)

include_directories(./include)

add_compile_options(-std=c++17 -Wall)

aux_source_directory(./src SRC)

add_executable(ava_parser ${SRC})

set(CMAKE_BUILD_TYPE Debug)