
#
# Build main
#

add_executable(mainCorr mainCorr.cpp)

##
## install exe
##   

install(TARGETS mainCorr DESTINATION ${CMAKE_INSTALL_PREFIX}/exe)
