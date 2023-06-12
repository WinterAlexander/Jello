cmake_minimum_required(VERSION 3.17)
project(Jello)

find_package(Threads REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated -pthread)
endif()

set(CMAKE_CXX_STANDARD 20)
set(GLFW_VERSION 3.3.2)
set(GTEST_VERSION release-1.10.0)
set(GLM_VERSION 0.9.9.8)
set(ASSIMP_VERSION v5.2.5)
set(STB_COMMIT 5736b15f7ea0ffb08dd38af21067c314d6a3aae9)

include(FetchContent)

FetchContent_Declare(stb
        GIT_REPOSITORY git@github.com:nothings/stb.git
        GIT_TAG ${STB_COMMIT})
FetchContent_MakeAvailable(stb)
FetchContent_GetProperties(stb SOURCE_DIR STB_SOURCE_DIR)

FetchContent_Declare(glm
        GIT_REPOSITORY git@github.com:g-truc/glm.git
        GIT_TAG ${GLM_VERSION})
FetchContent_MakeAvailable(glm)
FetchContent_GetProperties(glm SOURCE_DIR GLM_SOURCE_DIR)

FetchContent_Declare(assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG ${ASSIMP_VERSION})

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(assimp)
FetchContent_GetProperties(assimp SOURCE_DIR ASSIMP_SOURCE_DIR BINARY_DIR ASSIMP_BINARY_DIR)

file(GLOB_RECURSE JELLO_SRC_FILES "src/*.cpp" "include/*.h")

add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)

include_directories(include)
include_directories(${GLAD_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLM_SOURCE_DIR}/glm)
include_directories(${STB_SOURCE_DIR})
include_directories(${ASSIMP_SOURCE_DIR}/include)

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

target_link_libraries(Jello assimp)
target_link_libraries(Jello_lib assimp)

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
            ${GTEST_LIBS_DIR}/libgtest_main.a)
else()
    target_link_libraries(Jello_tests
            debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
            optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES})
    target_link_libraries(Jello_tests
            debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
            optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES})
endif()

target_link_libraries(Jello_tests ${CMAKE_THREAD_LIBS_INIT} Jello_lib)