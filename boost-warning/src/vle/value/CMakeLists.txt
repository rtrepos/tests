add_sources(vlelib  Double.cpp Double.hpp
  Matrix.cpp Matrix.hpp
  Value.cpp Value.hpp)

install(FILES Double.hpp Matrix.hpp
  Value.hpp
  DESTINATION ${VLE_INCLUDE_DIRS}/value)
