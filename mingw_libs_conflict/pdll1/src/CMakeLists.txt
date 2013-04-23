
#
# Build mydll
#

add_library(mydll_target MODULE mydll.cpp mydll.hpp)
set_target_properties(mydll_target PROPERTIES
  COMPILE_DEFINITIONS "MYDLL_EXPORTS"
  OUTPUT_NAME "mydll")

install(TARGETS mydll_target LIBRARY DESTINATION lib)
   
##
## install hpp
##   

install(FILES mydll.hpp DESTINATION ${CMAKE_INSTALL_PREFIX}/include)