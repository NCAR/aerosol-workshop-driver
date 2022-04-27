// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#include "array_bridge.h"
#include "wrap_array.h"
#include <aero/array/fortran_array.hpp>

namespace aero {

FortranArray::FortranArray(void *fortran_array):
  Array(nullptr, fortran_array),
  owns_array_(false) {}

FortranArray::FortranArray(void *fortran_array, bool owns_array):
  Array(nullptr, fortran_array),
  owns_array_(owns_array) {}

FortranArray::~FortranArray() {
  if (c_ptr_) aero_fortran_array_unwrap_c(c_ptr_);
  if (owns_array_) {
    aero_bridge_fortran_array_free(f_ptr_);
  } else {
    aero_bridge_fortran_array_free_wrapper(f_ptr_);
  }
  f_ptr_ = nullptr;
}

FortranArray& FortranArray::operator=(const std::vector<Real> &values) {
  if (f_ptr_) aero_bridge_fortran_array_copy_in(f_ptr_, values.data());
  return *this;
}

aero::Array* FortranArray::clone() const {
  AERO_ASSERT(f_ptr_ != nullptr);
  return new aero::FortranArray(aero_bridge_fortran_array_clone(f_ptr_), true);
}

const Real* FortranArray::data() const {
  if (f_ptr_) return aero_bridge_fortran_array_data(f_ptr_);
  return nullptr;
}

Real* FortranArray::data() {
  if (f_ptr_) return aero_bridge_fortran_array_data(f_ptr_);
  return nullptr;
}

void FortranArray::copy_in(const Real *input) {
  if (f_ptr_) aero_bridge_fortran_array_copy_in(f_ptr_, input);
}

void FortranArray::copy_out(Real *output) const {
  if (f_ptr_) aero_bridge_fortran_array_copy_out(f_ptr_, output);
}

std::size_t FortranArray::size() const {
  if (f_ptr_) return aero_bridge_fortran_array_size(f_ptr_);
  return 0;
}

} // namespace aero

#if __cplusplus
extern "C" {
#endif

void* aero_fortran_array_wrap_cpp(void *f_array) {
  return reinterpret_cast<void*>(new aero::FortranArray(f_array));
}

void aero_fortran_array_unwrap_cpp(void *cpp_array) {
  delete(reinterpret_cast<aero::FortranArray*>(cpp_array));
}

#if __cplusplus
} // extern "C"
#endif

