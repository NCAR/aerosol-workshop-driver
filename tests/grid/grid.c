/* Copyright (C) 2022 National Center for Atmospheric Research,
 * National Technology & Engineering Solutions of Sandia, LLC (NTESS),
 * and the U.S. Environmental Protection Agency (USEPA)
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "grid_helper.h"

#include <aero/grid/grid.h>
#include <aero/array/array.h>
#include <aero/array/cpp_array.h>
#include <aero/array/fortran_array.h>

#include <math.h>
#include <stdio.h>

int main(const int argc, const char *argv[]) {

  // Create a grid from a set of interfaces, and make sure everything is
  // correct within it.
  aero_real_t points[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
  aero_array_t *interfaces = aero_array_from_array(11, points);
  aero_grid_t *grid = aero_grid_from_interfaces(interfaces);
  const aero_array_t* g_interfaces = aero_grid_interfaces(grid);
  const aero_array_t* g_midpoints = aero_grid_midpoints(grid);
  AERO_ASSERT(g_interfaces->size(g_interfaces) == 11);
  AERO_ASSERT(g_midpoints->size(g_midpoints) == 10);
  AERO_ASSERT(almost_equal(aero_grid_lower_bound(grid), 0.0));
  AERO_ASSERT(almost_equal(aero_grid_upper_bound(grid), 1.0));
  aero_grid_free(grid);

  // Now let's create a grid from a Fortran array.
  interfaces = aero_new_fortran_array(test_grid_create_fortran_interfaces(), true);
  interfaces->copy_in(interfaces, points);
  grid = aero_grid_from_interfaces(interfaces);
  g_interfaces = aero_grid_interfaces(grid);
  g_midpoints = aero_grid_midpoints(grid);
  AERO_ASSERT(g_interfaces->size(g_interfaces) == 11);
  AERO_ASSERT(g_midpoints->size(g_midpoints) == 10);
  AERO_ASSERT(almost_equal(aero_grid_lower_bound(grid), 0.0));
  AERO_ASSERT(almost_equal(aero_grid_upper_bound(grid), 1.0));
  aero_grid_free(grid);

  // Do the same with a C++ array.
  interfaces = aero_new_cpp_array(test_grid_create_cpp_interfaces(), true);
  interfaces->copy_in(interfaces, points);
  grid = aero_grid_from_interfaces(interfaces);
  g_interfaces = aero_grid_interfaces(grid);
  g_midpoints = aero_grid_midpoints(grid);
  AERO_ASSERT(g_interfaces->size(g_interfaces) == 11);
  AERO_ASSERT(g_midpoints->size(g_midpoints) == 10);
  AERO_ASSERT(almost_equal(aero_grid_lower_bound(grid), 0.0));
  AERO_ASSERT(almost_equal(aero_grid_upper_bound(grid), 1.0));
  aero_grid_free(grid);

  return 0;
}
