project(UI)

file(GLOB_RECURSE UI_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/**.cpp"
)

add_library(${PROJECT_NAME} ${UI_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../")

target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
