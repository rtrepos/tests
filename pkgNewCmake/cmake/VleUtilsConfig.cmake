# VleCheckDependencies.cmake
# ===========================
#
# Check the dependencies of the current package
#
# Copyright (c) 2014-2014 INRA
# Ronan Trépos <rtrepos@toulouse.inra.fr>
#
# Distributed under the OS-approved BSD License (the "License");
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#
# ===========================================================================
#
# Changelog
# ---------
#
# 1.0  Initial version.
#
# ===========================================================================
#
# Description
# -----------
#
# This script provides utils functions for vle cmake files :
#
# - VleCheckPackage: it checks if a package is installed into the binary 
#     packages. And sets the variables used to link to the designated package.
#
# - VleCheckDependencies: it checks if vle dependencies, declared 
#     into the file Descitption.txt (${CMAKE_SRC_DIR}/Description.txt)
#     are installed into the binary packages (VLE_HOME/pkgs-${VLE_ABI_VERSION})
#
# - VleBuildLibrary: it builds a library from a cpp file taking into account
#     packages dependencies declared into the dependencies declared into 
#     tag "@@tagdepends" into the cpp file
# 
# - VleBuildLibraries: for all the cpp files into the current directory,
#     if the tag "@@tagdynamic@@" the it builds a library using VleBuildLibrary.
#
# CMake variables used by the functions in this module:
#  
#  VLE_DEBUG             - If true, prints debug traces (default OFF)
#
# ===========================================================================
#
# Usage of VleCheckPackage
# ------------------------
#
# find_package(VleUtils REQUIRED)
# set(VLE_ABI_VERSION 1.1)
# VleCheckPackage(PREFIX package)
#
# The script sets the following variables:
#   VleUtils_VERSION        ... the version of this script (integer)
#   <PREFIX>_FOUND          ... set to 1 is package exist
#   <PREFIX>_LIBRARIES      ... only the libraries (w/o the '-l') found into
#                                 the lib directory of the package.
#   <PREFIX>_INCLUDE_DIRS   ... the '-I' preprocessor flags (w/o the '-I')
#
#
# Usage of VleCheckDependencies
# -----------------------------
#
# find_package(VleUtils REQUIRED)
# set(VLE_ABI_VERSION 1.1)
# VleCheckDependencies()
#
# Usage of VleBuildLibrary
# ------------------------
#
# find_package(VleUtils REQUIRED)
# VleBuildLibraries()
# 
# ===========================================================================

set(VleUtils_VERSION 1.0)

##
## internal macros
##

macro(_vle_check_package_set var value)
  set(${var} "${value}" CACHE INTERNAL "")
endmacro(_vle_check_package_set)

macro(_vle_check_package_unset var)
  set(${var} "" CACHE INTERNAL "")
endmacro(_vle_check_package_unset)


##
## user visible macros
##

macro(VleCheckPackage _prefix _module)
  if (DEFINED VLE_DEBUG)
    set (_vle_debug  ${VLE_DEBUG})
  else ()
    set (_vle_debug 0)
  endif ()
  file(TO_CMAKE_PATH "$ENV{VLE_HOME}" _vle_home)
  if (NOT _vle_home)
    if (CMAKE_HOST_WIN32)
      file(TO_CMAKE_PATH "$ENV{HOMEDRIVE}$ENV{HOMEPATH}/vle" _vle_home)
    else ()
      file(TO_CMAKE_PATH "$ENV{HOME}/.vle" _vle_home)
    endif ()
    if (_vle_debug) 
      message(STATUS "The VLE_HOME undefined, try default ${_vle_home}")
    endif()
  else ()
    if (_vle_debug)
      message(STATUS "The VLE_HOME defined: ${_vle_home}")
    endif ()
  endif ()
  if (NOT VLE_ABI_VERSION)
    set(_vle_package_dir "pkgs")
    if (_vle_debug)
      message(STATUS "VLE_ABI_VERSION undefined for package directory, "
                     "try default ${_vle_package_dir}")
    endif()
  else ()
    set(_vle_package_dir "pkgs-${VLE_ABI_VERSION}")
    if (_vle_debug)
      message(STATUS "VLE_ABI_VERSION defined for package directory: "
                     "${_vle_package_dir}")
    endif ()
  endif ()
  if (EXISTS ${_vle_home})
    set(_vle_include_dirs "${_vle_home}/${_vle_package_dir}/${_module}/src")
    set(_vle_lib_dirs "${_vle_home}/${_vle_package_dir}/${_module}/lib")
    if (EXISTS "${_vle_include_dirs}" OR EXISTS "${_vle_lib_dirs}")
      if (CMAKE_HOME_WIN32)
        file(GLOB _vle_libraries "${_vle_lib_dirs}/*.lib" "${_vle_lib_dirs}/*.dll.a")
      else (CMAKE_HOME_WIN32)
        file(GLOB _vle_libraries "${_vle_lib_dirs}/*.a")
      endif (CMAKE_HOME_WIN32)
      _vle_check_package_set(${_prefix}_FOUND 1)
      _vle_check_package_set(${_prefix}_INCLUDE_DIRS ${_vle_include_dirs})
      _vle_check_package_set(${_prefix}_LIBRARIES "${_vle_libraries}")
      if (_vle_debug)
        message(STATUS "Found `${_module}': ${_vle_libraries} and "
                       "${_vle_include_dirs}")
      endif ()
    else (EXISTS "${_vle_include_dirs}" OR EXISTS "${_vle_lib_dirs}")
      message(FATAL_ERROR "Package `${_module}' not found")
    endif (EXISTS "${_vle_include_dirs}" OR EXISTS "${_vle_lib_dirs}")
  else ()
    message(FATAL_ERROR "VLE_HOME was not found")
  endif ()
endmacro(VleCheckPackage)

## 

macro(VleCheckDependencies)
  if (NOT EXISTS "${CMAKE_SOURCE_DIR}/Description.txt")
    message(FATAL_ERROR "Missing Description.txt file: "
                        "${CMAKE_SOURCE_DIR}/Description.txt ")  
  endif ()
  file(STRINGS "${CMAKE_SOURCE_DIR}/Description.txt" __DESCRIPTION_TEXT)
  foreach(__LINE_DESCR_TEXT IN LISTS __DESCRIPTION_TEXT)
   if ("${__LINE_DESCR_TEXT}" MATCHES "^Depends:(.*)")
    STRING(REGEX REPLACE "," ";" __VLE_PKGS_DEPENDENCIES ${CMAKE_MATCH_1})
    foreach(__VLE_PKG_DEP IN LISTS __VLE_PKGS_DEPENDENCIES)
      STRING(REGEX REPLACE "[ ]" "" __VLE_PKG_DEP ${__VLE_PKG_DEP})
      VleCheckPackage(${__VLE_PKG_DEP} ${__VLE_PKG_DEP})
      if (NOT ${${__VLE_PKG_DEP}_FOUND})
         message(FATAL_ERROR "Missing package ${__VLE_PKG_DEP}")
      endif ()
    endforeach ()
   endif ()
  endforeach () 
endmacro(VleCheckDependencies)

##

macro (VleBuildLibrary _libname _cppfile)
  if (DEFINED VLE_DEBUG)
    set (_vle_debug  ${VLE_DEBUG})
  else ()
    set (_vle_debug 0)
  endif ()
  file(READ "${_cppfile}" __cpp_content)
  string(REGEX MATCH "@@tagdepends:(.+)@@endtagdepends" __tag_depends ${__cpp_content})
  set(__include_dirs "")
  set(__libraries "")
  if(NOT ${__tag_depends} STREQUAL "")
    set (__tag_depends ${CMAKE_MATCH_1})
    string(REGEX REPLACE "," ";" __tag_depends ${CMAKE_MATCH_1})
    foreach(__vle_pkg_dep IN LISTS __tag_depends)
      string(REGEX REPLACE "[ ]" "" __vle_pkg_dep ${__vle_pkg_dep})
      message (" DBG ${__vle_pkg_dep}")
      if (NOT ${__vle_pkg_dep}_FOUND)
        message (FATAL_ERROR "Missing pkg '${__vle_pkg_dep}' for building "
                             "${_cppfile}, maybe you forgot to add this " 
                             "package into the Description.txt file")
      endif ()
      set(__include_dirs "${__include_dirs};${${__vle_pkg_dep}_INCLUDE_DIRS}")
      set(__libraries "${__libraries};${${__vle_pkg_dep}_LIBRARIES}")    
    endforeach ()
    if (_vle_debug)
      message(STATUS "Additional include dir for `${_libname}': "
                     "${__include_dirs}")
      message(STATUS "Additional libs to link for `${_libname}': "
                     "${__libraries}")
    endif ()

  endif ()
  include_directories(${CMAKE_SOURCE_DIR}/src ${VLE_INCLUDE_DIRS}
                        ${Boost_INCLUDE_DIRS} ${__include_dirs})
  link_directories(${VLE_LIBRARY_DIRS} ${Boost_LIBRARY_DIRS})
  add_library(${_libname} MODULE ${_cppfile})
  target_link_libraries(${_libname} ${__libraries} ${VLE_LIBRARIES}
                        ${Boost_LIBRARIES})
  install(TARGETS ${_libname}
                 RUNTIME DESTINATION plugins/simulator
                 LIBRARY DESTINATION plugins/simulator)
endmacro(VleBuildLibrary)

##

macro (VleBuildLibraries)
  if (DEFINED VLE_DEBUG)
    set (_vle_debug  ${VLE_DEBUG})
  else ()
    set (_vle_debug 0)
  endif ()
  file(GLOB __cpp_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
  foreach(__cppfile ${__cpp_files})
    file(READ "${__cppfile}" __cppcontent)
    string(REGEX MATCH "@@tagdynamic@@+" __tag_dyn ${__cppcontent})
    if(NOT ${__tag_dyn} STREQUAL "")
      string(REGEX MATCH "(.+).cpp" __libname ${__cppfile})
      set (__libname ${CMAKE_MATCH_1})
      if (_vle_debug)
        message(STATUS "Detected lib to build : `${__libname}'")
      endif ()
      VleBuildLibrary(${__libname} "${__cppfile}")
    endif()
  endforeach ()
endmacro(VleBuildLibraries)
