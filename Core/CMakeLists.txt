cmake_minimum_required(VERSION 3.28)
project(Core)

file(GLOB_RECURSE CORE_SOURCES
    "Source/**.cpp"
)

add_executable(core ${CORE_SOURCES})
target_include_directories(core PUBLIC "Source")
