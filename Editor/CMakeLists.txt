cmake_minimum_required(VERSION 3.28)
project(Editor)

file(GLOB_RECURSE EDITOR_SOURCES
    "Editor/**.cpp"
)

add_executable(editor ${EDITOR_SOURCES})
target_include_directories(editor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Qt6 REQUIRED COMPONENTS Core Gui)
target_link_libraries(editor PRIVATE Qt6::Core Qt6::Gui)

target_link_libraries(editor PRIVATE core)
