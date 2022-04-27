// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#ifndef AERO_INTERPOLATOR_HPP
#define AERO_INTERPOLATOR_HPP

#include <vector>
#include <tuple>
#include <aero/aero.hpp>
#include <aero/array/array.hpp>
#include <aero/grid/grid.hpp>

namespace aero {

class Interpolator {
public:
  /// No default constructor
  Interpolator() = delete;
  /// Deleted copy constructor
  Interpolator(const Interpolator&) = delete;
  /// Move constructor
  Interpolator(Interpolator&&) = default;
  /// Constructor from input and output grids
  Interpolator(const Grid& from, const Grid& to);

  /// Destructor
  ~Interpolator();

  /// Deleted assignment operator
  Interpolator& operator=(const Interpolator&) = delete;
  /// Deleted move assignment operator
  Interpolator& operator=(Interpolator&&) = delete;
  /// Function call operator (same as calling interpolate)
  void operator()(const Array& from, Array& to) const;

  /// Interpolates from an array on the input grid to an array
  /// on the output grid
  void interpolate(const Array& from, Array& to) const;

private:

  // implementation
  struct Impl;
  Impl* impl_;
};

} // namespace aero

#endif
