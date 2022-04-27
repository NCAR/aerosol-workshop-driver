// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#include <aero/aero.hpp>
#include <aero/array/array.hpp>
#include "array_helper.h"

extern "C" {

void *test_array_create_cpp_array() {
  std::vector<aero::Real> ra {142.52, 0.235, -1e9, 12.5};
  return (void*) new aero::Array{ra};
}

void test_array_check_cpp_array(void* cpp_array, int index, aero_real_t value) {
  aero::Array *array = reinterpret_cast<aero::Array*>(cpp_array);
  AERO_ASSERT(almost_equal(array->data()[index], value));
}

}
