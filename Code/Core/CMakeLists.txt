project(Core)

file(GLOB_RECURSE CORE_SOURCES
    "**.cpp"
)

add_library(${PROJECT_NAME} ${CORE_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../")

find_package(fmt REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt)
