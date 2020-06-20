cmake_minimum_required(VERSION 3.17)
project(glad C)

if(EXISTS glad)
    message(STATUS "glad already generated")
ELSE()
    execute_process(COMMAND glad --generator=c --profile=core --out-path=glad)
endif()


set(GLAD_PROJECT_PATH ${CMAKE_BINARY_DIR}/glad)

set(GLAD_INCLUDE_DIRS ${GLAD_PROJECT_PATH}/include PARENT_SCOPE)

file(GLOB_RECURSE GLAD_SRC_FILES "${GLAD_PROJECT_PATH}/src/*.c" "${GLAD_PROJECT_PATH}/include/*.h")

add_library(glad ${GLAD_SRC_FILES})
include_directories(${GLAD_PROJECT_PATH}/include)
target_link_libraries(glad dl)