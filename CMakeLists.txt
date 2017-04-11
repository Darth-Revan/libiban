cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(libiban)

# set C++11 as a required feature of the compiler
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

# set additional flags for GCC and Clang
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message("Setting additional flags for GCC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Werror")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message("Setting additional flags for Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Werror -Weverything")
endif()

set(SOURCE_FILES src/libiban.h src/libiban.cpp)
add_library(libiban SHARED ${SOURCE_FILES})

set(TEST_FILES test/main.cpp ${SOURCE_FILES})
add_executable(libiban_test ${TEST_FILES})