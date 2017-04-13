cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(libiban)

# set C++11 as a required feature of the compiler
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

# set additional flags for GCC and Clang
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message("Setting additional flags for GCC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Werror -Wno-c++98-compat -Wno-c++98-compat-pedantic")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message("Setting additional flags for Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Werror -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors")
endif()

# The project version number.
set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   1   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   0   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

#configure target for building documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create HTML documentation of API with Doxygen" OFF)
if(BUILD_DOCUMENTATION)
    if (NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed for building documentation")
    endif()
    message("Building documentation ...")
    set(doxy_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set(doxy ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${doxy_in} ${doxy} @ONLY)
    add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxy}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generate documentation with Doxygen"
            VERBATIM)
endif()

# find Boost Random for generating random numbers
option(USE_BOOST_RANDOM "Use Boost Random instead of standard library rand() for generating IBANs." ON)
if (USE_BOOST_RANDOM)
    find_package(Boost COMPONENTS random)
    if(NOT Boost_FOUND)
        message(FATAL_ERROR "Boost Random is required, but could not be found!")
    endif()
    message("Building with Boost Random ...")
    add_definitions(-DUSE_BOOST=1)
else()
    message("Building without using Boost ...")
endif()

set(SOURCE_FILES src/libiban.h src/libiban.cpp src/utils.h src/utils.cpp)
add_library(iban SHARED ${SOURCE_FILES})

# link against Boost if required
if (USE_BOOST_RANDOM)
    target_link_libraries(iban ${Boost_LIBRARIES})
endif()

set(TEST_FILES test/main.cpp src/libiban.h src/utils.h)
add_executable(libiban_test ${TEST_FILES})
target_link_libraries(libiban_test iban)