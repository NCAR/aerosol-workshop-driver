#include "grid_bridge.h"

#include <aero/array/c_array.hpp>
#include <aero/array/fortran_array.hpp>
#include <aero/grid/grid.hpp>

namespace aero {

Grid::Grid(Array&& interfaces):
  interfaces(interfaces) {

  // Extract data from interfaces array to compute midpoints.
  std::vector<Real> iface_data;
  interfaces.copy_out(iface_data);
  std::vector<Real> midpt_data(iface_data.size()-1);
  for (size_t i = 0; i < midpt_data.size(); ++i) {
    midpt_data[i] = 0.5 * (iface_data[i] + iface_data[i+1]);
  }
  interfaces = Array(iface_data);
  midpoints = Array(midpt_data);
  lower_bound = iface_data.front();
  upper_bound = iface_data.back();
}

Grid Grid::from_c_ptr(void *c_ptr) {
  void *c_array_ptr = aero_bridge_c_grid_interfaces(c_ptr);
  CArray cpp_interfaces(c_array_ptr);
  return Grid(std::move(cpp_interfaces));
}

Grid Grid::from_fortran_ptr(void *f_ptr) {
  void *f_array_ptr = aero_bridge_fortran_grid_interfaces(f_ptr);
  FortranArray f_interfaces(f_array_ptr);
  return Grid(std::move(f_interfaces));
}

Grid::~Grid() {
}

} // namespace aero
