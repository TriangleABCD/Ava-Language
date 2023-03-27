cmake_minimum_required(VERSION 3.10)

project(ava)

include_directories(./include)

add_compile_options(-std=c++11 -Wall)

aux_source_directory(./src SRC)

add_executable(ava ${SRC})

set(CMAKE_BUILD_TYPE Debug)



