cmake_minimum_required(VERSION 3.17)
project(Jello)

find_package(Threads REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated -pthread)
endif()

set(CMAKE_CXX_STANDARD 20)
set(GLFW_VERSION 3.3.2)
set(GTEST_VERSION release-1.10.0)
set(GLAD_VERSION v0.1.33)
set(GLM_VERSION 0.9.9.8)

file(GLOB_RECURSE JELLO_SRC_FILES "src/*.cpp" "include/*.h")

add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

include_directories(include)
include_directories(${GLAD_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})

add_library(Jello_lib ${JELLO_SRC_FILES})
add_executable(Jello ${JELLO_SRC_FILES})

target_link_libraries(Jello dl)
target_link_libraries(Jello_lib dl)

target_link_libraries(Jello glfw)
target_link_libraries(Jello_lib glfw)

target_link_libraries(Jello glad)
target_link_libraries(Jello_lib glad)

target_link_libraries(Jello glm)
target_link_libraries(Jello_lib glm)

add_subdirectory(lib/gtest)
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB_RECURSE JELLO_TEST_SRC_FILES "tests/*.cpp")

add_executable(Jello_tests ${JELLO_TEST_SRC_FILES})
add_dependencies(Jello_tests googletest Jello_lib)

target_link_libraries(Jello_tests dl)
target_link_libraries(Jello_tests glfw)

if(NOT WIN32 OR MINGW)
    target_link_libraries(Jello_tests
            ${GTEST_LIBS_DIR}/libgtest.a
            ${GTEST_LIBS_DIR}/libgtest_main.a
            )
else()
    target_link_libraries(Jello_tests
            debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
            optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
            )
    target_link_libraries(Jello_tests
            debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
            optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
            )
endif()

target_link_libraries(Jello_tests ${CMAKE_THREAD_LIBS_INIT} Jello_lib)