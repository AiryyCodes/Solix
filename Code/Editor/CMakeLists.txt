project(Editor)

file(GLOB_RECURSE EDITOR_SOURCES
    "**.cpp"
)

add_executable(${PROJECT_NAME} ${EDITOR_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../")

target_link_libraries(${PROJECT_NAME} PUBLIC Core Renderer)
