// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#include "state_bridge.h"
#include <aero/state/c_state.hpp>

namespace aero {

CState::CState(void *c_state):
  c_ptr_(c_state) {}

CState::~CState() {
  aero_bridge_c_state_free(c_ptr_);
  c_ptr_ = nullptr;
}

}
