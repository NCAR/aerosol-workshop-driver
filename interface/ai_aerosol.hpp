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

#ifndef AI_AEROSOL_HPP
#define AI_AEROSOL_HPP

#include "ai_array.hpp"
#include "ai_grid.hpp"
#include "ai_state.hpp"

#include <string>

namespace ai {

/// Aerosol model base class
class Aerosol {

public:
  /// Default constructor
  Aerosol() = default;
  /// Copy constructor is disabled (no deep copies)
  Aerosol(const Aerosol&) = delete;
  /// Default move constructor
  Aerosol(Aerosol&&) = default;

  /// Destructor
  virtual ~Aerosol() {}

  /// Assignment operator is disabled (no deep copies)
  Aerosol& operator=(const Aerosol&) = delete;
  /// Default move assignment operator
  Aerosol& operator=(Aerosol&&) = default;

  /// Returns the name of the aerosol model/package.
  virtual std::string name() const = 0;

  /// Returns the aerosol optics grid, discretized in wavelength space.
  virtual Grid optics_grid() const = 0;

  /// Computes optical property data, given an aerosol state and destination
  /// arrays.
  virtual void compute_optics(const State& state,
                              Array& od,
                              Array& od_ssa,
                              Array& od_asym) const = 0;
};

/// This Aerosol subclass allows access to aerosol models implemented in
/// Fortran.
class FortranAerosol: public Aerosol {
public:

  /// Construct an aerosol model wrapped around a Fortran implementation
  /// that can be accessed with the given pointer.
  explicit FortranAerosol(void *fortran_pointer);

  /// Move constructor (Aerosol models cannot be deep copied)
  FortranAerosol(FortranAerosol&& other);

  /// Destructor
  ~FortranAerosol() override;

  /// Move assignment operator
  FortranAerosol& operator=(FortranAerosol&& other);

  // Overridden methods
  Grid optics_grid() const override;
  void compute_optics(const State& state,
                      Array& od,
                      Array& od_ssa,
                      Array& od_asym) const override;

  void *f_ptr_; // pointer to Fortran aerosol implementation
};

} // namespace ai

#endif
