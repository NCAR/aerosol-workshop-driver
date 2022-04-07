#include <aero/array/array.h>
#include <aero/array/cpp_array.h>
#include <aero/array/fortran_array.h>
#include <aero/grid/grid.h>

#include "grid_bridge.h"

#include <assert.h>
#include <stdlib.h>

aero_grid_t aero_grid_from_interfaces(aero_array_t *interfaces) {
  // Extract data from interfaces array to compute midpoints.
  size_t n_iface = interfaces->size(interfaces);
  assert(n_iface >= 2);
  aero_real_t *iface_data = malloc(sizeof(aero_real_t) * n_iface);
  interfaces->copy_out(interfaces, iface_data);
  size_t n_midpt = n_iface - 1;
  aero_real_t *midpt_data = malloc(sizeof(aero_real_t) * n_midpt);
  for (size_t i = 0; i < n_midpt; ++i) {
    midpt_data[i] = 0.5 * (iface_data[i] + iface_data[i+1]);
  }
  aero_real_t lb = iface_data[0], ub = iface_data[n_iface-1];
  free(iface_data);

  return (aero_grid_t){
    .interfaces = interfaces,
    .midpoints = aero_array_from_array(n_midpt, midpt_data),
    .lower_bound = lb,
    .upper_bound = ub
  };
}

aero_grid_t aero_grid_from_cpp_ptr(void *cpp_ptr) {
  void *cpp_array_ptr = aero_bridge_cpp_grid_interfaces(cpp_ptr);
  aero_array_t *cpp_interfaces = aero_cpp_array_wrap(cpp_array_ptr);
  aero_grid_t grid = aero_grid_from_interfaces(cpp_interfaces);
  aero_cpp_array_unwrap(cpp_interfaces);
  return grid;
}

aero_grid_t aero_grid_from_fortran_ptr(void *f_ptr) {
  void *f_array_ptr = aero_bridge_fortran_grid_interfaces(f_ptr);
  aero_array_t *f_interfaces = aero_fortran_array_wrap(f_array_ptr);
  aero_grid_t grid = aero_grid_from_interfaces(f_interfaces);
  aero_fortran_array_unwrap(f_interfaces);
  return grid;
}

void aero_grid_free(aero_grid_t grid) {
  // The grid owns its arrays, so it deletes them.
  grid.interfaces->free(grid.interfaces);
  grid.midpoints->free(grid.midpoints);
}

