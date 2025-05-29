cmake_minimum_required(VERSION 3.28)
project(SolixEngine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)

add_subdirectory("Deps")
add_subdirectory("Code")
