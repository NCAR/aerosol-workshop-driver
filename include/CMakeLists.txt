# Generate the top-level C/C++ header files and Fortran module.

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/aero.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/aero.h
  @ONLY
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/aero.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/aero.hpp
  @ONLY
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/aero.F90.in
  ${CMAKE_CURRENT_BINARY_DIR}/aero.F90
  @ONLY
)

add_library(aero_f90 ${CMAKE_CURRENT_BINARY_DIR}/aero.f90)
