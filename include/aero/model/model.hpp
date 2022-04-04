//===-- interface/aerosol/ai_aerosol.hpp ------------------------*- C++ -*-===//
//
// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//
///
/// \file C++ wrapper for aerosol interface
///
//===----------------------------------------------------------------------===//

#ifndef AERO_MODEL_HPP
#define AERO_MODEL_HPP

#include <aero/array/array.hpp>
#include <aero/grid/grid.hpp>
#include <aero/state/state.hpp>

#include <string>

namespace aero {

/// Aerosol model base class
class Model {

public:
  /// Default constructor
  Model() = default;
  /// Copy constructor is disabled (no deep copies)
  Model(const Model&) = delete;
  /// Default move constructor
  Model(Model&&) = default;

  /// Destructor
  virtual ~Model() {}

  /// Assignment operator is disabled (no deep copies)
  Model& operator=(const Model&) = delete;
  /// Default move assignment operator
  Model& operator=(Model&&) = default;

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
#if 0
/// This Model subclass allows access to aerosol models implemented in
/// Fortran.
class FortranModel: public Model {
public:

  /// Construct an aerosol model wrapped around a Fortran implementation
  /// that can be accessed with the given pointer.
  explicit FortranModel(void *fortran_pointer);

  /// Move constructor (Aerosol models cannot be deep copied)
  FortranModel(FortranModel&& other);

  /// Destructor
  ~FortranModel() override;

  /// Move assignment operator
  FortranModel& operator=(FortranModel&& other);

  // Overridden methods
  Grid optics_grid() const override;
  void compute_optics(const State& state,
                      Array& od,
                      Array& od_ssa,
                      Array& od_asym) const override;

  void *f_ptr_; // pointer to Fortran aerosol implementation
};
#endif
} // namespace aero

#endif
