cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(PROJECT_NAME no_name_project)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.cpp)

# GLFW properties
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# GLFW, GLAD linking
add_subdirectory(external/glfw)
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw)