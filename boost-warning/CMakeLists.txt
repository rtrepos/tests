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
# Check libraries with pkgconfig
#
find_package(PkgConfig REQUIRED)

# FIXME use old-style link directories for now
if (COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 OLD)
endif (COMMAND CMAKE_POLICY)

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

if (WITH_TEST)
  if (Boost_UNIT_TEST_FRAMEWORK_FOUND)
    set(VLE_HAVE_UNITTESTFRAMEWORK 1 CACHE INTERNAL "" FORCE)
  endif (Boost_UNIT_TEST_FRAMEWORK_FOUND)
endif (WITH_TEST)


#
# Generate the config.h
#
check_include_file_cxx(cxxabi.h VLE_HAVE_GCC_ABI_DEMANGLE)
check_include_file_cxx(execinfo.h VLE_HAVE_EXECINFO)
check_include_file_cxx(signal.h VLE_HAVE_SIGNAL)
include_directories(${VLE_BINARY_DIR})



#
# Add sources for a target
# add_sources(<target> <source1> [<source2> ...])
#
function(add_sources target)
  get_property(prop_defined GLOBAL PROPERTY ${target}_SRCS DEFINED)
  if(NOT prop_defined)
    define_property(GLOBAL PROPERTY ${target}_SRCS
      BRIEF_DOCS "Sources for the ${target} target"
      FULL_DOCS "List of source files for the ${target} target")
  endif()

  set(SRCS)
  foreach(src ${ARGN})
    if(NOT IS_ABSOLUTE "${src}")
      get_filename_component(src "${src}" ABSOLUTE)
    endif()
    list(APPEND SRCS "${src}")
  endforeach()
  set_property(GLOBAL APPEND PROPERTY "${target}_SRCS" "${SRCS}")
endfunction()

#
# Browse the src subdirectory
#
ADD_SUBDIRECTORY(src)

