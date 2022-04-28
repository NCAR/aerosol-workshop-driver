// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#ifndef AERO_C_STATE_HPP
#define AERO_C_STATE_HPP

#include <aero/model/c_model.hpp>
#include <aero/state/state.hpp>

namespace aero {

/// This state subclass allows access to aerosol states implemented in C
class CState: public State {
public:
  ~CState();

private:
  friend CModel;
  CState(void *c_state);
  bool owns_state_; // Indicates whether the underlying state is owned
                    // by this wrapper
  void *c_ptr_; // pointer to C state implementation
};

}

#endif // AERO_C_STATE_HPP
