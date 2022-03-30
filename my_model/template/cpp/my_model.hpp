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

#pragma once
#include "aero/model/model.hpp"

namespace mya {

/// \brief My aerosol model
class MyModel : public aero::Model {

public:
  MyModel();
  virtual ~MyModel() {}
  void GetOptics(double *optics);

private:
};

} // mya project
