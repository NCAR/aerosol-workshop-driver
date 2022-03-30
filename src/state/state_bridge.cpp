//===-- interface/state/ai_bridge_state.cpp ---------------------*- C++ -*-===//
//
// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//
///
/// \file C/C++ <--> Fortran bridge functions for the State class
///
//===----------------------------------------------------------------------===//
#include "state_bridge.h"

#include <iostream>

void* aero_bridge_c_state_clone(void *state) {
  return nullptr;
}

void* aero_bridge_cpp_state_clone(void *state) {
  return nullptr;
}

void aero_bridge_c_state_free(void *state) {
}

void aero_bridge_cpp_state_free(void *state) {
}
