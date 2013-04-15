


##
## main
##

include_directories(${DEPS_INCLUDE_DIRS})
link_directories(${DEPS_LIBRARY_DIRS})

add_executable(main main.cpp)
set_target_properties(main PROPERTIES
  LINK_FLAGS "-shared-libgcc")
target_link_libraries(main ${DEPS_LIBRARIES})

