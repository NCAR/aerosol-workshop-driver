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
#include <aero/state/state.h>
#include <aero/state/state.hpp>

#if __cplusplus
extern "C" {
#endif

void aero_bridge_c_state_free(void *state) {
  aero_state_t *c_state = reinterpret_cast<aero_state_t*>(state);
  c_state->free(c_state);
}

void aero_bridge_cpp_state_free(void *state) {
  aero::State *cpp_state = reinterpret_cast<aero::State*>(state);
  delete(cpp_state);
}

#if __cplusplus
} // extern "C"
#endif
