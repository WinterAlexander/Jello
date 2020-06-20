cmake_minimum_required(VERSION 3.17)
project(glfw_builder C CXX)

if(EXISTS glfw)
    message(STATUS "GLFW already cloned")
ELSE()
    execute_process(COMMAND git clone https://github.com/glfw/glfw)
    execute_process(COMMAND git checkout ${GLFW_VERSION} WORKING_DIRECTORY glfw --quiet)
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_BINARY_DIR}/glfw ${CMAKE_BINARY_DIR}/glfw/build)

set(GLFW_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/glfw/include PARENT_SCOPE)
