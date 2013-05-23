add_sources(vlelib 
  Matrix.cpp Matrix.hpp
  Value.cpp Value.hpp)

install(FILES Matrix.hpp
  Value.hpp
  DESTINATION ${VLE_INCLUDE_DIRS}/value)
