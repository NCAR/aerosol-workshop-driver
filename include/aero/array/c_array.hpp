// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#ifndef AERO_C_ARRAY_HPP
#define AERO_C_ARRAY_HPP

#include <aero/array/array.hpp>

namespace aero {

/// This Array subclass allows access to arrays implemented in C
class CArray: public Array {
public:
  /// Default constructor
  CArray() = delete;
  /// Copy constructor
  CArray(const CArray& other) = delete;
  /// Move constructor
  CArray(CArray&& other);
  /// Construct from a pointer to a C-backed Array
  explicit CArray(void *c_array);
  /// Construct from a pointer to a C-backed Array with a flag indicating
  /// whether this wrapper owns the underlying Array
  CArray(void *c_array, bool owns_array);

  /// Destructor
  ~CArray() override;

  /// Copy assignment operator
  CArray& operator=(CArray& other) = delete;
  /// Assignment from a vector of Reals
  CArray& operator=(const std::vector<Real> &values);
  /// Move assignment operator
  CArray& operator=(CArray&&);

  /// Returns a clone (deep-copy) of an array
  Array* clone() const override;
  /// Copies data into an Array
  void copy_in(const Real *input) override;
  /// Copies data out of an Array
  void copy_out(Real *output) const override;
  /// Returns a pointer to the array data
  /// @{
  const Real* data() const override;
  Real* data() override;
  /// @}
  /// Returns the number of elements in an Array
  std::size_t size() const override;

private:
  bool owns_array_;
};

} // namespace aero

#endif
