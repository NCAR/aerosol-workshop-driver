//===-- interface/aerosol/ai_aerosol.cpp ------------------------*- C++ -*-===//
//
// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//
///
/// \file C++ wrapper for aerosol interface
///
//===----------------------------------------------------------------------===//

#include <aero/model/model.hpp>
#include <aero/state/state.hpp>

extern "C" {

// This Fortran subroutine populates the given optical property arrays with
// data given pointers to an aerosol model and state.
void aero_fortran_model_compute_optics(void *model_ptr,
                                       void *state_ptr,
                                       void *od_ptr,
                                       void *od_ssa_ptr,
                                       void *od_asym_ptr);

}

namespace aero {
#if 0
FortranModel::FortranModel(void *fortran_pointer):
  Model(),
  f_ptr_(fortran_pointer) {}

FortranModel::FortranModel(FortranModel&& other):
  Model(),
  f_ptr_(nullptr) {

  f_ptr_ = other.f_ptr_;
  other.f_ptr_ = nullptr;
}

void FortranModel::compute_optics(const State& state,
                                  Array& od,
                                  Array& od_ssa,
                                  Array& od_asym) const {
  const FortranState& f_state = dynamic_cast<const FortranState&>(state);
  FortranArray& f_od          = dynamic_cast<FortranArray&>(od);
  FortranArray& f_od_ssa      = dynamic_cast<FortranArray&>(od_ssa);
  FortranArray& f_od_asym     = dynamic_cast<FortranArray&>(od_asym);
  aero_fortran_model_compute_optics(f_ptr_, f_state.f_ptr_, f_od.f_ptr_,
                                    f_od_ssa.f_ptr_, f_od_asym.f_ptr_);
}
#endif
} // aero namespace
