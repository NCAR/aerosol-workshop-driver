// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
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
  Model(Model&&) = delete;

  /// Destructor
  virtual ~Model() {}

  /// Assignment operator is disabled (no deep copies)
  Model& operator=(const Model&) = delete;
  /// Default move assignment operator
  Model& operator=(Model&&) = delete;

  /// Returns the name of the aerosol model/package.
  virtual std::string name() const = 0;

  /// Returns a newly created aerosol state.
  virtual State* create_state() const = 0;

  /// Returns the aerosol optics grid, discretized in wavelength space.
  virtual Grid* optics_grid() const = 0;

  /// Computes optical property data, given an aerosol state and destination
  /// arrays.
  virtual void compute_optics(State& state,
                              Array& od,
                              Array& od_ssa,
                              Array& od_asym) const = 0;
};

} // namespace aero

#endif
