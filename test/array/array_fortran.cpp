// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
// Support functions for Fortran array tests

#include <aero/aero.hpp>
#include <aero/array/array.hpp>

extern "C" {

void *test_array_create_cpp_array() {
  std::vector<Real> ra {142.52, 0.235, -1e9, 12.5};
  return (void*) new aero::Array{ra};
}

}
