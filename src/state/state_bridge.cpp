// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
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
