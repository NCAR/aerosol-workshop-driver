// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#include "array_bridge.h"
#include "wrap_array.h"
#include <aero/array/c_array.hpp>

namespace aero {

CArray::CArray(void *c_array):
  Array(c_array, nullptr),
  owns_array_(false) {}

CArray::CArray(void *c_array, bool owns_array):
  Array(c_array, nullptr),
  owns_array_(owns_array) {}

CArray::~CArray() {
  if (f_ptr_) aero_c_array_unwrap_fortran(f_ptr_);
  if (owns_array_) aero_bridge_c_array_free(c_ptr_);
  c_ptr_ = nullptr;
}

CArray& CArray::operator=(const std::vector<Real> &values) {
  if (c_ptr_) aero_bridge_c_array_copy_in(c_ptr_, values.data());
  return *this;
}

Array* CArray::clone() const {
  AERO_ASSERT(c_ptr_ != nullptr);
  return new CArray(aero_bridge_c_array_clone(c_ptr_), true);
}

void CArray::copy_in(const Real *input) {
  if (c_ptr_) aero_bridge_c_array_copy_in(c_ptr_, input);
}

void CArray::copy_out(Real *output) const {
  if (c_ptr_) aero_bridge_c_array_copy_out(c_ptr_, output);
}

const Real* CArray::data() const {
  if (c_ptr_) return aero_bridge_c_array_data(c_ptr_);
  return nullptr;
}

Real* CArray::data() {
  if (c_ptr_) return aero_bridge_c_array_data(c_ptr_);
  return nullptr;
}

std::size_t CArray::size() const {
  if (c_ptr_) return aero_bridge_c_array_size(c_ptr_);
  return 0;
}

} // namespace aero

#if __cplusplus
extern "C" {
#endif

void* aero_c_array_wrap_cpp(void *c_array) {
  return reinterpret_cast<void*>(new aero::CArray(c_array));
}

void aero_c_array_unwrap_cpp(void *cpp_array) {
  delete(reinterpret_cast<aero::CArray*>(cpp_array));
}

#if __cplusplus
} // extern "C"
#endif

