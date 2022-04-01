#include "array_bridge.h"
#include <aero/array/fortran_array.hpp>

namespace aero {

FortranArray::FortranArray(const FortranArray& other):
  f_ptr_(aero_bridge_fortran_array_clone(other.f_ptr_)) {}

FortranArray::FortranArray(FortranArray&& other):
  f_ptr_(other.f_ptr_) {
  other.f_ptr_ = nullptr;
}

FortranArray::FortranArray(void *fortran_array) : f_ptr_(fortran_array) {}

FortranArray::~FortranArray() {
  aero_bridge_fortran_array_free(f_ptr_);
}

FortranArray& FortranArray::operator=(FortranArray& other) {
  if (this != &other) {
    if (f_ptr_) {
      aero_bridge_fortran_array_free(f_ptr_);
    }
    f_ptr_ = aero_bridge_fortran_array_clone(other.f_ptr_);
  }
  return *this;
}

FortranArray& FortranArray::operator=(const std::vector<Real> &values) {
  if (f_ptr_) aero_bridge_fortran_array_copy_in(f_ptr_, values.data());
  return *this;
}

FortranArray& FortranArray::operator=(FortranArray&& other) {
  if (this != &other) {
    f_ptr_ = other.f_ptr_;
    other.f_ptr_ = nullptr;
  }
  return *this;
}

Array* FortranArray::clone() const {
  return new FortranArray(aero_bridge_fortran_array_clone(f_ptr_));
}

void FortranArray::copy_in(const Real *input) {
  if (f_ptr_) aero_bridge_fortran_array_copy_in(f_ptr_, input);
}

void FortranArray::copy_in(const std::vector<Real> &input) {
  if (f_ptr_) aero_bridge_fortran_array_copy_in(f_ptr_, input.data());
}

void FortranArray::copy_out(Real *output) const {
  if (f_ptr_) aero_bridge_fortran_array_copy_out(f_ptr_, output);
}

void FortranArray::copy_out(std::vector<Real> &output) const {
  if (f_ptr_) aero_bridge_fortran_array_copy_out(f_ptr_, output.data());
}

unsigned int FortranArray::size() const {
  if (f_ptr_) return aero_bridge_fortran_array_size(f_ptr_);
  return 0;
}


} // namespace aero
