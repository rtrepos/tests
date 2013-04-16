



include_directories(${DEPS_INCLUDE_DIRS})
link_directories(${DEPS_LIBRARY_DIRS})


##
## main_2_22
##

add_executable(main_2_22 main_2_22.cpp)
set_target_properties(main_2_22 PROPERTIES
  LINK_FLAGS "-shared-libgcc")
target_link_libraries(main_2_22 ${DEPS_LIBRARIES})


##
## main_2_24
##

add_executable(main_2_24 main_2_24.cpp)
set_target_properties(main_2_24 PROPERTIES
  LINK_FLAGS "-shared-libgcc")
target_link_libraries(main_2_24 ${DEPS_LIBRARIES})

