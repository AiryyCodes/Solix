cmake_minimum_required(VERSION 3.28)
project(ImGui)

file(GLOB_RECURSE IMGUI_SOURCES
    "imgui/**.cpp"
)

add_library(imgui ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC "imgui/")
