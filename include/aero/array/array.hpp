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
  Array(const Array& other) = default;
  /// Move constructor
  Array(Array&& other) = default;
  /// Constructor from dimensions. Array elements
  /// are initialized to zero.
  Array(const unsigned int number_of_elements);
  /// Constructor from dimensions and initial value
  Array(const unsigned int number_of_elements,
      const Real initial_value);
  /// Constructor from vector of reals
  Array(const std::vector<Real> &values);

  /// Destructor
  virtual ~Array() {}

  /// Assignment operator
  Array& operator=(const Array&) = default;
  /// Assignment from a vector of Reals
  Array& operator=(const std::vector<Real> &values);
  /// Default move assignment operator
  Array& operator=(Array&&) = default;

  /// Returns a clone (deep-copy) of an Array
  virtual Array* clone() const;
  /// Copies data into an Array
  virtual void copy_in(const Real *input);
  /// Copies data into an Array
  virtual void copy_in(const std::vector<Real> &input);
  /// Copies data out of an Array
  virtual void copy_out(Real *output) const;
  /// Copies data out of an Array
  virtual void copy_out(std::vector<Real> &output) const;
  /// Returns the number of elements in an Array
  virtual unsigned int size() const;

private:
  std::vector<Real> values_;

};

} // namespace aero

#endif
