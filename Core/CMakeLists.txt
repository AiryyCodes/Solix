cmake_minimum_required(VERSION 3.28)
project(Core)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CORE_SOURCES
    "Core/**.cpp"
)

add_library(core ${CORE_SOURCES})
target_include_directories(core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
