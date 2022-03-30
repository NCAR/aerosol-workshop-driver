#include "array_bridge.h"
#include <aero/array/array.hpp>

namespace aero {

FortranArray::FortranArray(void *fortran_pointer):
  f_ptr_(fortran_pointer) {}

FortranArray::FortranArray(FortranArray& other):
  f_ptr_(nullptr) {
  f_ptr_ = aero_bridge_fortran_array_clone(other.f_ptr_);
}

FortranArray::FortranArray(FortranArray&& other):
  f_ptr_(nullptr) {
  f_ptr_ = other.f_ptr_;
  other.f_ptr_ = nullptr;
}

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

FortranArray& FortranArray::operator=(FortranArray&& other) {
  if (this != &other) {
    f_ptr_ = other.f_ptr_;
    other.f_ptr_ = nullptr;
  }
  return *this;
}

} // namespace aero
