add_sources(vlelib  Double.cpp Double.hpp
  Map.cpp Map.hpp Matrix.cpp Matrix.hpp
  Set.cpp Set.hpp Table.cpp
  Table.hpp Tuple.cpp Tuple.hpp Value.cpp Value.hpp)

install(FILES Double.hpp Map.hpp Matrix.hpp
  Set.hpp Table.hpp Tuple.hpp Value.hpp
  DESTINATION ${VLE_INCLUDE_DIRS}/value)
