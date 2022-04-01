#include "array_bridge.h"
#include <aero/array/array.hpp>

namespace aero {

  Array::Array(const unsigned int number_of_elements) :
    values_(number_of_elements, 0.0) {}

  Array:: Array(const unsigned int number_of_elements,
      const Real initial_value) : values_(number_of_elements, initial_value) {}

  Array::Array(const std::vector<Real> &values) : values_(values) {}

  Array& Array::operator=(const std::vector<Real> &values) {
    this->values_ = values;
    return *this;
  }

  void Array::copy_in(const std::vector<Real> &input) {
    this->values_ = input;
  }

  void Array::copy_out(std::vector<Real> &output) const {
    output = this->values_;
  }

  unsigned int Array::size() const {
    return this->values_.size();
  }

} // namespace aero
