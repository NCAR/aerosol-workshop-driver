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
#include "interface/aerosol/ai_aerosol.hpp"

namespace mya {

/// \brief My aerosol model
class MyAerosol : public ai::Aerosol {

public:
  MyAerosol();
  virtual ~MyAerosol() {}
  void GetOptics(double *optics);

private:
};

} // mya project
