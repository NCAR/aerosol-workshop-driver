// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#ifndef AERO_FORTRAN_STATE_HPP
#define AERO_FORTRAN_STATE_HPP

#include <aero/model/fortran_model.hpp>
#include <aero/state/state.hpp>

namespace aero {

/// This state subclass allows access to aerosol states implemented in Fortran
class FortranState: public State {
public:
  ~FortranState();

private:
  friend FortranModel;
  FortranState(void *f_state);
  bool owns_state_; // Indicates whether the underlying state is owned
                    // by this wrapper
  void *f_ptr_; // pointer to Fortran state implementation
};

}

#endif // AERO_FORTRAN_STATE_HPP
