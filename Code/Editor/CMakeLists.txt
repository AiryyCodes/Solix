project(Editor)

file(GLOB_RECURSE EDITOR_SOURCES
    "**.cpp"
)

add_custom_target(link_target ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/Resources ${CMAKE_BINARY_DIR}/Resources)

add_executable(${PROJECT_NAME} ${EDITOR_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../")

target_link_libraries(${PROJECT_NAME} PUBLIC Core Renderer UI)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
