// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#include "grid_helper.h"

#include <aero/grid/grid.hpp>
#include <aero/array/array.h>
#include <aero/array/c_array.hpp>
#include <aero/array/fortran_array.hpp>

#include <cmath>

using Real = aero::Real;

int main(const int argc, const char *argv[]) {

  std::vector<Real> points {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};

  // Create a grid from a set of interfaces, and make sure everything is
  // correct within it.
  {
    auto *interfaces = new aero::Array(points);
    aero::Grid grid(interfaces);
    AERO_ASSERT(grid.interfaces().size() == 11);
    AERO_ASSERT(grid.midpoints().size() == 10);
    AERO_ASSERT(aero::almost_equal(grid.lower_bound(), 0.0));
    AERO_ASSERT(aero::almost_equal(grid.upper_bound(), 1.0));
  }

  // Now let's create a grid from a Fortran array.
  {
    auto *interfaces = new aero::FortranArray(test_grid_create_fortran_interfaces(), true);
    aero::Grid grid(interfaces);
    AERO_ASSERT(grid.interfaces().size() == 11);
    AERO_ASSERT(grid.midpoints().size() == 10);
    AERO_ASSERT(aero::almost_equal(grid.lower_bound(), 0.0));
    AERO_ASSERT(aero::almost_equal(grid.upper_bound(), 1.0));
  }

  // Do the same with a C array.
  {
    auto *interfaces = new aero::CArray(aero_array_from_array(11, points.data()), true);
    aero::Grid grid(interfaces);
    AERO_ASSERT(grid.interfaces().size() == 11);
    AERO_ASSERT(grid.midpoints().size() == 10);
    AERO_ASSERT(aero::almost_equal(grid.lower_bound(), 0.0));
    AERO_ASSERT(aero::almost_equal(grid.upper_bound(), 1.0));
  }

  return 0;
}

