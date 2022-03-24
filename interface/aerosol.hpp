//===-- interface/aerosol.hpp -----------------------------------*- C++ -*-===//
//
// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//
///
/// \file C++ wrapper for aerosol interface
///
//===----------------------------------------------------------------------===//

#pragma once

namespace ai {

/// \brief Base aerosol model
///
class Aerosol {

public:
  Aerosol();
  virtual ~Aerosol() {}
  void GetOptics(double *optics);

private:
};

} // namespace ai
