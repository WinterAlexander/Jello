cmake_minimum_required(VERSION 3.17)
project(glm_builder C CXX)

if(EXISTS ${CMAKE_BINARY_DIR}/glm)
    message(STATUS "GLM already cloned")
ELSE()
    execute_process(COMMAND git clone https://github.com/g-truc/glm)
    execute_process(COMMAND git checkout ${GLM_VERSION} --quiet WORKING_DIRECTORY glm)
endif()

add_subdirectory(${CMAKE_BINARY_DIR}/glm ${CMAKE_BINARY_DIR}/glm/build)

set(GLM_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/glm/ PARENT_SCOPE)
