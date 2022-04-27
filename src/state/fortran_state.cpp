// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#include "state_bridge.h"
#include <aero/state/fortran_state.hpp>

namespace aero {

FortranState::FortranState(void *fortran_state):
  f_ptr_(fortran_state) {}

FortranState::~FortranState() {
  aero_bridge_fortran_state_free(f_ptr_);
  f_ptr_ = nullptr;
}

}
