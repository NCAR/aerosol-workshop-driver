#include "grid_bridge.h"

#include <aero/array/c_array.hpp>
#include <aero/array/fortran_array.hpp>
#include <aero/grid/grid.hpp>

namespace aero {

Grid::Grid(Array* interfaces):
  interfaces_(interfaces) {

  // Extract data from interfaces array to compute midpoints.
  std::vector<Real> iface_data(interfaces_->size());
  interfaces_->copy_out(iface_data);
  std::vector<Real> midpt_data(iface_data.size()-1);
  for (size_t i = 0; i < midpt_data.size(); ++i) {
    midpt_data[i] = 0.5 * (iface_data[i] + iface_data[i+1]);
  }
  midpoints_ = std::unique_ptr<Array>(new Array(midpt_data));
  lower_bound_ = iface_data.front();
  upper_bound_ = iface_data.back();
}

Grid Grid::from_c_ptr(void *c_ptr) {
  void *c_array_ptr = aero_bridge_c_grid_interfaces(c_ptr);
  auto *cpp_interfaces = new CArray(c_array_ptr);
  return Grid(cpp_interfaces);
}

Grid Grid::from_fortran_ptr(void *f_ptr) {
  void *f_array_ptr = aero_bridge_fortran_grid_interfaces(f_ptr);
  auto *f_interfaces = new FortranArray(f_array_ptr);
  return Grid(f_interfaces);
}

Grid::~Grid() {
}

} // namespace aero
