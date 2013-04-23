
#
# Build mydll2
#

add_library(mydll_target2 MODULE mydll2.cpp mydll.hpp)
set_target_properties(mydll_target2 PROPERTIES
	 COMPILE_DEFINITIONS "MYDLL_EXPORTS"
	 OUTPUT_NAME "mydll"
)

install(TARGETS mydll_target2 LIBRARY DESTINATION lib2)
   
   
##
## install hpp
##   

#install(FILES mydll.hpp DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
## ALREADY INSTALLED by pdll1