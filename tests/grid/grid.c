/* Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 *
 * Tests for the C grid type
 */

#include "grid_helper.h"

#include <aero/grid/grid.h>
#include <aero/array/array.h>
#include <aero/array/cpp_array.h>
#include <aero/array/fortran_array.h>

#include <assert.h>
#include <math.h>
#include <stdio.h>

int main(const int argc, const char *argv[]) {

  // Create a grid from a set of interfaces, and make sure everything is
  // correct within it.
  aero_real_t points[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
  aero_array_t *interfaces = aero_array_from_array(11, points);
  aero_grid_t grid = aero_grid_from_interfaces(interfaces);
  assert(grid.interfaces->size(grid.interfaces) == 11);
  assert(grid.midpoints->size(grid.midpoints) == 10);
  assert(fabs(grid.lower_bound) < aero_epsilon);
  assert(fabs(grid.upper_bound - 1.0) < aero_epsilon);
  aero_grid_free(grid);

  // Now let's create a grid from a Fortran array.
  interfaces = aero_fortran_array_wrap(test_grid_create_fortran_interfaces());
  interfaces->copy_in(interfaces, points);
  grid = aero_grid_from_interfaces(interfaces);
  assert(grid.interfaces->size(grid.interfaces) == 11);
  assert(grid.midpoints->size(grid.midpoints) == 10);
  assert(fabs(grid.lower_bound) < aero_epsilon);
  assert(fabs(grid.upper_bound - 1.0) < aero_epsilon);
  aero_grid_free(grid);

  // Do the same with a C++ array.
  interfaces = aero_cpp_array_wrap(test_grid_create_cpp_interfaces());
  interfaces->copy_in(interfaces, points);
  grid = aero_grid_from_interfaces(interfaces);
  assert(grid.interfaces->size(grid.interfaces) == 11);
  assert(grid.midpoints->size(grid.midpoints) == 10);
  assert(fabs(grid.lower_bound) < aero_epsilon);
  assert(fabs(grid.upper_bound - 1.0) < aero_epsilon);
  aero_grid_free(grid);

  return 0;
}
