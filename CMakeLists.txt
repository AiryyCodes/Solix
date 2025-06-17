cmake_minimum_required(VERSION 3.28)
project(SolixEngine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(TARGET_DEBUG)
endif()

add_custom_target(solix_link_resources ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Solix
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${CMAKE_BINARY_DIR}/Solix/Resources
)

add_subdirectory("Deps")
add_subdirectory("Code")
