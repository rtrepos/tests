cmake_minimum_required(VERSION 2.6)
project(VLE CXX C)
enable_testing()




#
# CMake modules
#
include(CheckIncludeFileCXX)
include(CheckIncludeFile)
include(CheckLibraryExists)
include(CMakeDetermineCCompiler)

#
# append debug mode when compiler is GNU.
#

if (CMAKE_BUILD_TYPE STREQUAL "")
  SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
endif ()

if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

  option(WITH_COVERAGE "use coverage build [default: off]" OFF)
  if (WITH_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} --coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
  endif ()

  if ("${CMAKE_BUILD_TYPE}" EQUAL "Debug" OR
      "${CMAKE_BUILD_TYPE}" EQUAL "RelWithDebInfo")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3")
  endif ()
endif ()


#
# Test the libboost header and libboost-text library.
#


  set(Boost_THREADAPI "win32")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

set(Boost_USE_MULTITHREADED ON)
set(Boost_DETAILED_FAILURE_MSG ON)
set(Boost_DEBUG OFF)

find_package(Boost COMPONENTS unit_test_framework thread filesystem system
  chrono date_time regex program_options)

if (NOT Boost_FOUND)
  message(STATUS "Boost is not founded. Try without chrono")
  find_package(Boost COMPONENTS unit_test_framework thread filesystem system
    date_time regex program_options)
endif ()

if (NOT Boost_FILESYSTEM_FOUND)
  message(FATAL_ERROR "The boost filesystem library is required")
endif (NOT Boost_FILESYSTEM_FOUND)
if (NOT Boost_REGEX_FOUND)
  message(FATAL_ERROR "The boost regex library is required")
endif (NOT Boost_REGEX_FOUND)
if (NOT Boost_DATE_TIME_FOUND)
  message(FATAL_ERROR "The boost date_time library is required")
endif (NOT Boost_DATE_TIME_FOUND)
if (NOT Boost_THREAD_FOUND)
  message(FATAL_ERROR "The boost thread library is required")
endif (NOT Boost_THREAD_FOUND)
if (NOT Boost_PROGRAM_OPTIONS_FOUND)
  message(FATAL_ERROR "The boost program options library is required")
endif (NOT Boost_PROGRAM_OPTIONS_FOUND)

if (Boost_MINOR_VERSION AND ${Boost_MINOR_VERSION} LESS "41")
  set(VLE_HAVE_BOOST_SPIRIT2 0 CACHE INTERNAL "" FORCE)
else (Boost_MINOR_VERSION AND ${Boost_MINOR_VERSION} LESS "41")
  set(VLE_HAVE_BOOST_SPIRIT2 1 CACHE INTERNAL "" FORCE)
endif (Boost_MINOR_VERSION AND ${Boost_MINOR_VERSION} LESS "41")

#
# Browse the src subdirectory
#
include_directories(
  ${Boost_INCLUDE_DIRS})

add_library(vlelib SHARED Matrix.cpp Matrix.hpp)

