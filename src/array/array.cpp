// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#include <aero/array/array.hpp>
#include "array_bridge.h"
#include "wrap_array.h"

namespace aero {

Array::Array(std::size_t size)
  : values_(size, 0.0),
    c_ptr_(aero_cpp_array_wrap_c(this)),
    f_ptr_(aero_cpp_array_wrap_fortran(this)) {}

Array:: Array(std::size_t size, Real initial_value)
  : values_(size, initial_value),
    c_ptr_(aero_cpp_array_wrap_c(this)),
    f_ptr_(aero_cpp_array_wrap_fortran(this)) {}

Array::Array(const std::vector<Real> &values)
  : values_(values),
    c_ptr_(aero_cpp_array_wrap_c(this)),
    f_ptr_(aero_cpp_array_wrap_fortran(this)) {}

Array& Array::operator=(const std::vector<Real> &values) {
  this->values_ = values;
  return *this;
}

Array::~Array() {
  if (c_ptr_) aero_cpp_array_unwrap_c(c_ptr_);
  if (f_ptr_) aero_cpp_array_unwrap_fortran(f_ptr_);
}

Array* Array::clone() const {
  return new Array(this->values_);
}

void Array::copy_in(const Real *input) {
  for (int i=0; i<this->values_.size(); ++i) {
    this->values_[i] = input[i];
  }
}

void Array::copy_in(const std::vector<Real> &input) {
  AERO_ASSERT(input.size() == this->size());
  this->copy_in(input.data());
}

void Array::copy_out(Real *output) const {
  for (int i=0; i<this->values_.size(); ++i) {
    output[i] = this->values_[i];
  }
}

void Array::copy_out(std::vector<Real> &output) const {
  AERO_ASSERT(output.size() == this->size());
  this->copy_out(output.data());
}

const Real* Array::data() const {
  return this->values_.data();
}

Real* Array::data() {
  return this->values_.data();
}

std::size_t Array::size() const {
  return this->values_.size();
}

const void* Array::c_ptr() const {
  return this->c_ptr_;
}

const void* Array::fortran_ptr() const {
  return this->f_ptr_;
}

void* Array::c_ptr() {
  return this->c_ptr_;
}

void* Array::fortran_ptr() {
  return this->f_ptr_;
}

Array::Array(void *c_ptr, void *f_ptr): c_ptr_(c_ptr), f_ptr_(f_ptr) {}
} // namespace aero
