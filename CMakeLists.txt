cmake_minimum_required(VERSION 3.3)
project(PaperGraph)
include(ExternalProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

set(INCLUDE_DIRECTORIES src util inc shapes)

file(GLOB SOURCE_FILES
        "src/*.h"
        "src/*.cpp"
        "util/*.h"
        "util/*.cpp"
        "shapes/*.cpp"
        "inc/glm/*.hpp"
        )

include_directories(${INCLUDE_DIRECTORIES})

add_executable(PaperGraph ${SOURCE_FILES})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw-3.2.1)
target_link_libraries(PaperGraph glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(PaperGraph ${OPENGL_gl_LIBRARY})

find_package(GLEW REQUIRED)
target_link_libraries(PaperGraph ${GLEW_LIBRARIES})

add_custom_command(TARGET PaperGraph PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:PaperGraph>/shaders)