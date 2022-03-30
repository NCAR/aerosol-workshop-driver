//===-- interface/array/ai_bridge_array.cpp ---------------------*- C++ -*-===//
//
// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//
///
/// \file C/C++ <--> Fortran bridge functions for the Array class
///
//===----------------------------------------------------------------------===//
#include <iostream>
#include "ai_bridge_array.h"

void* ai_bridge_c_array_clone(void *state) {
  return nullptr;
}

void* ai_bridge_cpp_array_clone(void *state) {
  return nullptr;
}

void ai_bridge_c_array_free(void *aerosol) {
}

void ai_bridge_cpp_array_free(void *aerosol) {
}
