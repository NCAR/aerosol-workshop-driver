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
#include <aero/grid/grid.h>
#include <aero/grid/grid.hpp>
#include <aero/array/array.h>
#include <aero/array/array.hpp>

extern "C" {

void* aero_bridge_cpp_grid_interfaces(void *cpp_ptr) {
  aero::Grid *grid = reinterpret_cast<aero::Grid*>(cpp_ptr);
  return reinterpret_cast<void*>(&(grid->interfaces()));
}

void* aero_bridge_c_grid_interfaces(void *c_ptr) {
  aero_grid_t *grid = reinterpret_cast<aero_grid_t*>(c_ptr);
  return reinterpret_cast<void*>(grid->interfaces);
}

} // extern "C"

