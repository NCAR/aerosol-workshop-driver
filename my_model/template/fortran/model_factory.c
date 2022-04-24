/* Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 */

#include "model_factory.h"

aero_model_t* create_model(const char* package_name, const char* description_file) {
  aero_model_t* new_model = aero_cpp_model_create(package_name, description_file);
  if (new_model) return new_model;
  return aero_fortran_model_create(package_name, description_file);
}

bool is_c_model(const char* package_name) {
  return false;
}

aero_model_t* create_c_model(const char* package_name, const char* description_file) {
  AERO_ASSERT( false, "Unsupported C aerosol model" );
}
