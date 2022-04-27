// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#ifndef AERO_FORTRAN_MODEL_HPP
#define AERO_FORTRAN_MODEL_HPP

#include <aero/model/model.hpp>

namespace aero {

/// This model subclass allows access to models implemented in Fortran
class FortranModel: public Model {
public:
  FortranModel(void *fortran_model);
  FortranModel(void *fortran_model, bool owns_model);
  ~FortranModel();
  std::string name() const override;
  aero::State* create_state() const override;
  aero::Grid* optics_grid() const override;
  void compute_optics(aero::State& state,
                      aero::Array& od,
                      aero::Array& od_ssa,
                      aero::Array& od_asym) const override;

private:
  bool owns_model_; // Indicates whether the underlying model is owned
                    // by this wrapper
  void *f_ptr_; // pointer to Fortran model implementation
};

}

#endif // AERO_FORTRAN_MODEL_HPP
