// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#include <aero/aero.hpp>
#include <aero/array/array.hpp>
#include <aero/grid/grid.hpp>
#include <aero/interpolator/interpolator.hpp>

using Real = aero::Real;

int main(const int argc, const char *argv[]) {

  std::vector<Real> from_points {1.0, 11.0, 51.0, 61.0};
  std::vector<Real> from_values {5.0, 10.0, 2.0, 0.0};
  std::vector<Real> to_points {0.0, 6.0, 11.0, 56.0, 57.0};

  auto *from_interfaces = new aero::Array(from_points);
  auto *to_interfaces   = new aero::Array(to_points);
  auto *from_grid       = new aero::Grid(from_interfaces);
  auto *to_grid         = new aero::Grid(to_interfaces);

  auto *from_data       = new aero::Array(from_values);
  auto *to_data         = new aero::Array(5);

  // Create an interpolator from the input and output grids
  {
    auto *interp = new aero::Interpolator(*from_grid, *to_grid);
    (*interp)(*from_data, *to_data);
    auto *to_a = to_data->data();
    AERO_ASSERT(aero::almost_equal(to_a[0], 5.0));
    AERO_ASSERT(aero::almost_equal(to_a[1], 7.5));
    AERO_ASSERT(aero::almost_equal(to_a[2], 10.0));
    AERO_ASSERT(aero::almost_equal(to_a[3], 1.0));
    AERO_ASSERT(aero::almost_equal(to_a[4], 0.8));
    delete interp;
  }

  delete from_data;
  delete to_data;
  delete from_grid;
  delete to_grid;
}
