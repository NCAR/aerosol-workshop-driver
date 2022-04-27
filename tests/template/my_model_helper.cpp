// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
// Support functions for C/Fortran MyModel template tests

#include <aero/aero.hpp>
#include "my_model_helper.h"
#include "my_model.hpp"

extern "C" {

void *test_my_model_create_cpp_model() {
  return reinterpret_cast<void*>(new MyModel(""));
}

}
