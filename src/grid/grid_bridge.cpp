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
#include "grid_bridge.h"

#include <iostream>

void* aero_bridge_c_grid_clone(void *grid) {
  return nullptr;
}

void* aero_bridge_cpp_grid_clone(void *grid) {
  return nullptr;
}

void aero_bridge_c_grid_free(void *grid) {
}

void aero_bridge_cpp_grid_free(void *grid) {
}

