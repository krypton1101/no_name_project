cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(PROJECT_NAME no_name_project)
project(${PROJECT_NAME})

# add_executable(${PROJECT_NAME} src/main.cpp
#     src/Renderer/ShaderProgram.cpp src/Renderer/ShaderProgram.h
#     src/Resources/ResourceManager.h src/Resources/ResourceManager.cpp)

add_executable(${PROJECT_NAME} src/testmain.cpp 
    src/Math/Vector/Vector.h src/Math/Vector/Vector.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# GLFW properties
# set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# GLFW, GLAD linking
# add_subdirectory(external/glfw)
# add_subdirectory(external/glad)
# target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)