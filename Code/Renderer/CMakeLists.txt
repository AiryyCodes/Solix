project(Renderer)

file(GLOB_RECURSE RENDERER_SOURCES
    "**.cpp"
)

add_library(${PROJECT_NAME} ${RENDERER_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../")

target_link_libraries(${PROJECT_NAME} PUBLIC Core)

find_package(glfw3 REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad imgui stb)
