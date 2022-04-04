#include "array_bridge.h"
#include <aero/array/c_array.hpp>

namespace aero {

CArray::CArray(const CArray& other):
  c_ptr_(aero_bridge_c_array_clone(other.c_ptr_)) {}

CArray::CArray(CArray&& other):
  c_ptr_(other.c_ptr_) {
  other.c_ptr_ = nullptr;
}

CArray::CArray(void *c_array) : c_ptr_(c_array) {}

CArray::~CArray() {
  aero_bridge_c_array_free(c_ptr_);
}

CArray& CArray::operator=(CArray& other) {
  if (this != &other) {
    if (c_ptr_) {
      aero_bridge_c_array_free(c_ptr_);
    }
    c_ptr_ = aero_bridge_c_array_clone(other.c_ptr_);
  }
  return *this;
}

CArray& CArray::operator=(const std::vector<Real> &values) {
  if (c_ptr_) aero_bridge_c_array_copy_in(c_ptr_, values.data());
  return *this;
}

CArray& CArray::operator=(CArray&& other) {
  if (this != &other) {
    c_ptr_ = other.c_ptr_;
    other.c_ptr_ = nullptr;
  }
  return *this;
}

Array* CArray::clone() const {
  return new CArray(aero_bridge_c_array_clone(c_ptr_));
}

void CArray::copy_in(const Real *input) {
  if (c_ptr_) aero_bridge_c_array_copy_in(c_ptr_, input);
}

void CArray::copy_in(const std::vector<Real> &input) {
  if (c_ptr_) aero_bridge_c_array_copy_in(c_ptr_, input.data());
}

void CArray::copy_out(Real *output) const {
  if (c_ptr_) aero_bridge_c_array_copy_out(c_ptr_, output);
}

void CArray::copy_out(std::vector<Real> &output) const {
  if (c_ptr_) aero_bridge_c_array_copy_out(c_ptr_, output.data());
}

std::size_t CArray::size() const {
  if (c_ptr_) return aero_bridge_c_array_size(c_ptr_);
  return 0;
}


} // namespace aero
