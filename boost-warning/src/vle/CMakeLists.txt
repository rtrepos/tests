include_directories(${VLE_BINARY_DIR}/src ${VLE_SOURCE_DIR}/src
  ${Boost_INCLUDE_DIRS} ${VLEDEPS_INCLUDE_DIRS})

link_directories(${VLEDEPS_LIBRARY_DIRS} ${Boost_LIBRARY_DIRS})

add_subdirectory(value)

get_property(vlelib_SRCS GLOBAL PROPERTY vlelib_SRCS)

#
# Build the shared library.
#

add_library(vlelib SHARED ${vlelib_SRCS};${OS_SPECIFIC_PATH_IMPL})

target_link_libraries(vlelib ${VLEDEPS_LIBRARIES}
  ${Boost_LIBRARIES} ${OS_SPECIFIC_LIBRARIES})



