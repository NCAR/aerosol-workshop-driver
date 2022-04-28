// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#ifndef AERO_GRID_HPP
#define AERO_GRID_HPP

#include <aero/array/array.hpp>

#include <memory>

namespace aero {

/// This type represents a computional grid consisting of a set of contiguous
/// segments separated by interfaces. The grid keeps track of the midpoints
/// between interfaces.
struct Grid final {
public:
  // A grid may be neither default constructed nor copied from another grid.
  Grid() = delete;
  Grid(const Grid&) = delete;
  Grid& operator=(const Grid&) = delete;

  /// Creates a grid from an Array containing points delimiting the interfaces
  /// between segments. The Grid assumes ownership of this array.
  explicit Grid(Array* interfaces);

  /// Creates a grid from a C pointer. The grid data is copied so it lives in
  /// both C and C++ runtimes.
  static Grid from_c_ptr(void *c_ptr);

  /// Creates a grid from a Fortran pointer. The Grid data is copied so it
  /// lives in both Fortran and C++ runtimes.
  static Grid from_fortran_ptr(void *f_ptr);

  /// Move constructor
  Grid(Grid&& other) = default;

  /// Destructor
  ~Grid();

  /// Move assignment operator
  Grid& operator=(Grid&&) = default;

  // Provides const access to grid interfaces.
  const Array& interfaces() const { return *interfaces_; }

  // Provides const access to grid interface midpoints.
  const Array& midpoints() const { return *midpoints_; }

  // Provides const access to interface lower bound.
  Real lower_bound() const { return lower_bound_; }

  // Provides const access to interface upper bound.
  Real upper_bound() const { return upper_bound_; }

private:
  /// Array storing interface coordinates (in ascending order)
  std::unique_ptr<Array> interfaces_;

  /// Array storing coordinates of midpoints between interfaces (in ascending
  /// order)
  std::unique_ptr<Array> midpoints_;

  /// Lower bound (minimum interface coordinate), provided for convenience
  Real lower_bound_;
  /// Upper bound (maximum interface coordinate), provided for convenience
  Real upper_bound_;
};

} // namespace aero

#endif
