
include_directories(${CMAKE_SOURCE_DIR}/src ${Boost_INCLUDE_DIRS} )
add_executable(main main.cpp
vle/value/Value.hpp vle/value/Value.cpp
vle/value/Table.hpp vle/value/Table.cpp
vle/value/Matrix.hpp vle/value/Matrix.cpp
vle/value/Tuple.hpp vle/value/Tuple.cpp
vle/value/Set.hpp vle/value/Set.cpp
vle/value/Boolean.hpp vle/value/Boolean.cpp
vle/value/Double.hpp vle/value/Double.cpp
vle/value/Integer.hpp vle/value/Integer.cpp
vle/value/XML.hpp vle/value/XML.cpp
vle/value/Map.hpp vle/value/Map.cpp
)
target_link_libraries(main ${Boost_LIBRARIES})

