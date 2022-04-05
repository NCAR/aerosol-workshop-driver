#include <aero/array/array.h>
#include <aero/array/cpp_array.h>
#include <aero/array/fortran_array.h>
#include <aero/grid/grid.h>

#include "grid_bridge.h"

#include <assert.h>
#include <stdlib.h>

aero_grid_t aero_grid_from_interfaces(aero_array_t *interfaces) {
  assert(aero_array_size(interfaces) >= 2);
  // Extract data from interfaces array to compute midpoints.
  size_t n_iface = aero_array_size(interfaces);
  aero_real_t *iface_data = malloc(sizeof(aero_real_t) * n_iface);
  size_t n_midpt = n_iface - 1;
  aero_real_t *midpt_data = malloc(sizeof(aero_real_t) * n_midpt);
  for (size_t i = 0; i < n_midpt; ++i) {
    midpt_data[i] = 0.5 * (iface_data[i] + iface_data[i+1]);
  }

  return (aero_grid_t){
    .interfaces = aero_array_from_array(n_iface, iface_data),
    .midpoints = aero_array_from_array(n_midpt, midpt_data),
    .lower_bound = iface_data[0],
    .upper_bound = iface_data[n_iface-1]
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
  aero_array_free((aero_array_t*)grid.interfaces);
  aero_array_free((aero_array_t*)grid.midpoints);
}

