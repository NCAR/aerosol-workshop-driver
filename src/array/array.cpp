#include "array_bridge.h"
#include <aero/array/array.hpp>

namespace aero {

Array::Array(std::size_t size)
  : values_(size, 0.0) {}

Array:: Array(std::size_t size, Real initial_value)
  : values_(size, initial_value) {}

Array::Array(const std::vector<Real> &values)
  : values_(values) {}

Array& Array::operator=(const std::vector<Real> &values) {
  this->values_ = values;
  return *this;
}

Array* Array::clone() const {
  return new Array(*this);
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

std::size_t Array::size() const {
  return this->values_.size();
}

} // namespace aero
