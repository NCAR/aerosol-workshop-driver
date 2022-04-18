//===-- interface/array/ai_bridge_array.cpp ---------------------*- C++ -*-===//
//
// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//
///
/// \file C/C++ <--> Fortran bridge functions for the aero::Array class
///
//===----------------------------------------------------------------------===//
#include <aero/array/array.h>
#include <aero/array/array.hpp>
#include "array_bridge.h"
#include <iostream>

#if __cplusplus
extern "C" {
#endif

void* aero_bridge_c_array_clone(void *array) {
  aero_array_t *c_array = reinterpret_cast<aero_array_t*>(array);
  return reinterpret_cast<void*>(c_array->clone(c_array));
}

void* aero_bridge_cpp_array_clone(void *array) {
  aero::Array *cpp_array = reinterpret_cast<aero::Array*>(array);
  aero::Array *new_array = new aero::Array(*cpp_array);
  return reinterpret_cast<void*>(new_array);
}

void aero_bridge_c_array_free(void *array) {
  aero_array_t *c_array = reinterpret_cast<aero_array_t*>(array);
  c_array->free(c_array);
}

void aero_bridge_cpp_array_free(void *array) {
  aero::Array *cpp_array = reinterpret_cast<aero::Array*>(array);
  delete cpp_array;
}

void aero_bridge_c_array_copy_in(void *array, const aero_real_t *input) {
  aero_array_t *c_array = reinterpret_cast<aero_array_t*>(array);
  c_array->copy_in(c_array, input);
}

void aero_bridge_cpp_array_copy_in(void *array, const aero_real_t *input) {
  aero::Array *cpp_array = reinterpret_cast<aero::Array*>(array);
  cpp_array->copy_in(input);
}

void aero_bridge_c_array_copy_out(void *array, aero_real_t *output) {
  aero_array_t *c_array = reinterpret_cast<aero_array_t*>(array);
  c_array->copy_out(c_array, output);
}

void aero_bridge_cpp_array_copy_out(void *array, aero_real_t *output) {
  aero::Array *cpp_array = reinterpret_cast<aero::Array*>(array);
  cpp_array->copy_out(output);
}

aero_real_t* aero_bridge_c_array_data(void *array) {
  aero_array_t *c_array = reinterpret_cast<aero_array_t*>(array);
  return c_array->data(c_array);
}

aero_real_t* aero_bridge_cpp_array_data(void *array) {
  aero::Array *cpp_array = reinterpret_cast<aero::Array*>(array);
  return cpp_array->data();
}

size_t aero_bridge_c_array_size(void *array) {
  aero_array_t *c_array = reinterpret_cast<aero_array_t*>(array);
  return c_array->size(c_array);
}

size_t  aero_bridge_cpp_array_size(void *array) {
  aero::Array *cpp_array = reinterpret_cast<aero::Array*>(array);
  return cpp_array->size();
}

#if __cplusplus
} // extern "C"
#endif
