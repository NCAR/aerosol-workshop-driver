// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#ifndef AERO_ARRAY_HPP
#define AERO_ARRAY_HPP

#include <aero/aero.hpp>
#include <vector>

namespace aero {

class Array {
public:
  /// Default constructor.
  Array() = default;
  /// Copy constructor
  Array(const Array& other) = delete;
  /// Move constructor
  Array(Array&& other) = delete;
  /// Constructor from dimensions. Array elements
  /// are initialized to zero.
  explicit Array(std::size_t size);
  /// Constructor from dimensions and initial value
  Array(std::size_t size, Real initial_value);
  /// Constructor from vector of reals
  explicit Array(const std::vector<Real> &values);

  /// Destructor
  virtual ~Array();

  /// Assignment operator
  Array& operator=(const Array&) = delete;
  /// Assignment from a vector of Reals
  Array& operator=(const std::vector<Real> &values);
  /// Default move assignment operator
  Array& operator=(Array&&) = delete;

  /// Returns a clone (deep-copy) of an Array
  virtual Array* clone() const;
  /// Copies data into an Array
  virtual void copy_in(const Real *input);
  /// Copies data into an Array
  void copy_in(const std::vector<Real> &input);
  /// Copies data out of an Array
  virtual void copy_out(Real *output) const;
  /// Copies data out of an Array
  void copy_out(std::vector<Real> &output) const;
  /// Returns a pointer to the array data
  /// @{
  virtual const Real* data() const;
  virtual Real* data();
  /// @}
  /// Returns the number of elements in an Array
  virtual std::size_t size() const;
  /// Returns pointers to the array for use in each language
  const void* c_ptr() const;
  const void* fortran_ptr() const;
  void* c_ptr();
  void* fortran_ptr();
  /// @}

protected:
  Array(void* c_ptr, void* f_ptr);
  void* c_ptr_;
  void* f_ptr_;

private:
  std::vector<Real> values_;

};

} // namespace aero

#endif
