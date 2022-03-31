#include <aero/array/array.h>
#include <aero/grid/grid.h>

#include "grid_bridge.h"

#include <stdlib.h>

aero_grid_t* aero_grid_from_interfaces(aero_array_t *interfaces) {
  // The grid takes ownership of this interfaces array.
  aero_grid_t *grid = malloc(sizeof(aero_grid_t));
  grid->interfaces = interfaces;
  // TODO: Extract data from interfaces array.
  grid->midpoints = NULL;
  return grid;
}

aero_grid_t* aero_grid_from_cpp_ptr(void *cpp_ptr) {
  void *cpp_array_ptr = aero_bridge_cpp_grid_interfaces(cpp_ptr);
  aero_array_t *cpp_interfaces = aero_array_from_cpp_ptr(cpp_array_ptr);
  aero_array_t *c_interfaces = aero_array_clone(cpp_interfaces); // deep copy
  return aero_grid_from_interfaces(c_interfaces);
}

aero_grid_t* aero_grid_from_fortran_ptr(void *f_ptr) {
  void *f_array_ptr = aero_bridge_fortran_grid_interfaces(f_ptr);
  aero_array_t *f_interfaces = aero_array_from_fortran_ptr(f_array_ptr);
  aero_array_t *c_interfaces = aero_array_clone(f_interfaces); // deep copy
  return aero_grid_from_interfaces(c_interfaces);
}

void aero_grid_free(aero_grid_t *grid) {
  // The grid owns its arrays, so it deletes them.
  aero_array_free(grid->interfaces);
  aero_array_free(grid->midpoints);
  free(grid);
}

aero_grid_bounds_t aero_grid_bounds(aero_grid_t *grid) {
  return grid->bounds;
}

aero_array_t* aero_grid_interfaces(aero_grid_t *grid) {
  return grid->interfaces;
}

aero_array_t* aero_grid_midpoints(aero_grid_t *grid) {
  return grid->midpoints;
}

