# Generate the top-level C/C++ header files and Fortran module.

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/aero/aero.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/aero/aero.h
  @ONLY
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/aero/aero.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/aero/aero.hpp
  @ONLY
)

