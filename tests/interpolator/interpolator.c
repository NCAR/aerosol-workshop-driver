/* Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 *
 * Tests for the C Interpolator type
 */

#include <aero/aero.h>
#include <aero/array/array.h>
#include <aero/grid/grid.h>
#include <aero/interpolator/interpolator.h>

int main(const int argc, const char *argv[]) {

  aero_real_t from_points[4] = {1.0, 11.0, 51.0, 61.0};
  aero_real_t from_values[4] = {5.0, 10.0, 2.0, 0.0};
  aero_real_t to_points[5]   = {0.0,  6.0, 11.0, 56.0, 57.0};

  aero_array_t *from_interfaces = aero_array_from_array(4, from_points);
  aero_array_t *to_interfaces   = aero_array_from_array(5, to_points);
  aero_grid_t  *from_grid = aero_grid_from_interfaces(from_interfaces);
  aero_grid_t  *to_grid   = aero_grid_from_interfaces(to_interfaces);

  aero_array_t *from_data = aero_array_from_array(3, from_values);
  aero_array_t *to_data   = aero_array_from_dimensions(5, 0.0);

  aero_interpolator_t *interp = aero_linear_interpolator(from_grid, to_grid);
  interp->interpolate(interp, from_data, to_data);
  aero_real_t *to_a = to_data->data(to_data);
  AERO_ASSERT(almost_equal(to_a[0], 5.0));
  AERO_ASSERT(almost_equal(to_a[1], 7.5));
  AERO_ASSERT(almost_equal(to_a[2], 10.0));
  AERO_ASSERT(almost_equal(to_a[3], 1.0));
  AERO_ASSERT(almost_equal(to_a[4], 0.8));

  interp->free(interp);
  from_data->free(from_data);
  to_data->free(to_data);
  aero_grid_free(from_grid);
  aero_grid_free(to_grid);
}
