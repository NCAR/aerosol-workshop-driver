//===-- interface/grid/ai_bridge_grid.cpp -----------------------*- C++ -*-===//
//
// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//
///
/// \file C/C++ <--> Fortran bridge functions for the Grid class
///
//===----------------------------------------------------------------------===//
#include <iostream>
#include "ai_bridge_grid.h"

void* ai_bridge_c_grid_clone(void *state) {
  return nullptr;
}

void* ai_bridge_cpp_grid_clone(void *state) {
  return nullptr;
}

void ai_bridge_c_grid_free(void *aerosol) {
}

void ai_bridge_cpp_grid_free(void *aerosol) {
}

