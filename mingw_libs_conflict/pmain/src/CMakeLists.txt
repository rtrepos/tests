
#
# Build main with mydll
#

include_directories(${CMAKE_INSTALL_PREFIX}/include)

link_directories(${CMAKE_INSTALL_PREFIX}/lib)
add_executable(main main.cpp)
target_link_libraries(main mydll)

##
## install hpp
##   

install(TARGETS main DESTINATION ${CMAKE_INSTALL_PREFIX}/exe)
