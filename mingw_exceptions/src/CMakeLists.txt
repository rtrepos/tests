
#
# Build dll with shared libgcc and libstdc++
#

add_library(mydll SHARED mydll.cpp mydll.hpp)
set_target_properties(mydll PROPERTIES
  LINK_FLAGS "-shared-libgcc"
  COMPILE_DEFINITIONS "MYDLL_EXPORTS")

#
# Build dll with static libgcc and libstdc++
#

add_library(mydll-static SHARED mydll.cpp mydll.hpp)

set_target_properties(mydll-static PROPERTIES
  LINK_FLAGS "-static-libgcc -static-libstdc++"
  COMPILE_DEFINITIONS "MYDLL_EXPORTS")

#
# Build main with mydll
#

add_executable(main main.cpp mydll.hpp)
target_link_libraries(main mydll)

#
# Build main with mydll-static
#

add_executable(main-static main.cpp mydll.hpp)
target_link_libraries(main-static mydll-static)
