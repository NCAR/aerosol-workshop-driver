// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#include <aero/aero.hpp>
#include "my_model_helper.h"
#include "my_model.hpp"

extern "C" {

void *test_my_model_create_cpp_model() {
  return reinterpret_cast<void*>(new MyModel(""));
}

}
