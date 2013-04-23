CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(mingw_libs_conflict CXX C)
SET (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
ENABLE_TESTING()


MESSAGE("CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}")


##
## Modules
##

INCLUDE(CheckIncludeFileCXX)
INCLUDE(CheckIncludeFile)
INCLUDE(CheckLibraryExists)
INCLUDE(CMakeDetermineCCompiler)

add_subdirectory(src)
