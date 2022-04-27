// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#include "grid_helper.h"
#include <aero/aero.hpp>
#include <aero/array/array.h>
#include <aero/array/array.hpp>

extern "C" {

void *test_grid_create_c_interfaces() {
  aero::Real ra[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
  return (void*)aero_array_from_array(11, ra);
}

void *test_grid_create_cpp_interfaces() {
  std::vector<aero::Real> ra {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
  return (void*) new aero::Array{ra};
}

}
