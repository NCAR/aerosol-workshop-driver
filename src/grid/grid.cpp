#include "grid_bridge.h"
#include <aero/grid/grid.hpp>

namespace aero {

Grid::Grid(Array&& interfaces):
  interfaces_(interfaces) {

  // TODO: Extract info from interfaces array here!
}

Grid Grid::from_c_ptr(void *c_ptr) {
  void *c_array_ptr = aero_bridge_c_grid_interfaces(c_ptr);
  auto c_interfaces = Array::from_c_ptr(c_array_ptr);
  Array cpp_interfaces(c_interfaces) // deep copy
  return Grid(cpp_interfaces);
}

Grid Grid::from_fortran_ptr(void *f_ptr) {
  void *f_array_ptr = aero_bridge_fortran_grid_interfaces(f_ptr);
  auto f_interfaces = Array::from_fortran_ptr(f_array_ptr);
  Array cpp_interfaces(f_interfaces) // deep copy
  return Grid(cpp_interfaces);
}

Grid::~Grid() {
}

} // namespace aero
