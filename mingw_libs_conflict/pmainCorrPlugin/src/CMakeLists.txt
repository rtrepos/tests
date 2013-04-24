
include_directories(${CMAKE_INSTALL_PREFIX}/include)
link_directories(${CMAKE_INSTALL_PREFIX}/lib)

#
# Build mainCorrPlugin
#

add_library(mainCorrPlugin MODULE mainCorrPlugin.cpp)
set_target_properties(mainCorrPlugin PROPERTIES
	 COMPILE_DEFINITIONS "MAIN_CORR_PLUGIN_EXPORTS"
)
target_link_libraries(mainCorrPlugin mydll)

install(TARGETS mainCorrPlugin LIBRARY DESTINATION lib)
install(FILES mainCorrPlugin.hpp DESTINATION ${CMAKE_INSTALL_PREFIX}/include)