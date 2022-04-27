/* Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 *
 * Support functions for C++/Fortran MyModel template tests
 */

#include <aero/model/model.h>
#include "my_model_helper.h"
#include "my_model.h"

void *test_my_model_create_c_model() {
  return (void*) my_model_new("");
}
