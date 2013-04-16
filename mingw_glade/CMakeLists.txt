CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(MyProject CXX C)
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

find_package(PkgConfig REQUIRED)
pkg_check_modules(DEPS gtkmm-2.4)

message (" DEPS_LIBRARIES ${DEPS_LIBRARIES}")
message (" DEPS_LIBRARY_DIRS ${DEPS_LIBRARY_DIRS}") 

#
# Do work
#

add_subdirectory(src)
