//===-- template/cpp/my_aerosol.hpp -----------------------------*- C++ -*-===//
//
// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//
///
/// \file Implementation of an aerosol model
///
//===----------------------------------------------------------------------===//

#include <aero/model/model.hpp>

namespace mya {

/// \brief My aerosol model
class MyModel : public aero::Model {

public:
  MyModel();
  ~MyModel();
  std::string name() const override;
  aero::State* create_state() const override;
  const aero::Grid& optics_grid() const override;
  void compute_optics(const aero::State& state,
                      aero::Array& od,
                      aero::Array& od_ssa,
                      aero::Array& od_asym) const override;

private:

  aero::Grid* create_grid_();
  aero::Grid* grid_;
};

} // mya project
