cmake_minimum_required(VERSION 3.28)
project(Editor)

file(GLOB_RECURSE EDITOR_SOURCES
    "Source/**.cpp"
)

add_executable(editor ${EDITOR_SOURCES})
target_include_directories(editor PUBLIC "Source")
