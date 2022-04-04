#ifndef AERO_FORTRAN_ARRAY_HPP
#define AERO_FORTRAN_ARRAY_HPP

#include <aero/array/array.hpp>

namespace aero {

/// This Array subclass allows access to arrays implemented in
/// Fortran.
class FortranArray: public Array {
public:
  /// Default constructor
  FortranArray() = delete;
  /// Copy constructor
  FortranArray(const FortranArray& other);
  /// Move constructor
  FortranArray(FortranArray&& other);
  /// Construct from a pointer to a Fortran-backed Array
  explicit FortranArray(void *fortran_array);

  /// Destructor
  ~FortranArray() override;

  /// Copy assignment operator
  FortranArray& operator=(FortranArray& other);
  /// Assignment from a vector of Reals
  FortranArray& operator=(const std::vector<Real> &values);
  /// Default move assignment operator
  FortranArray& operator=(FortranArray&&);

  /// Returns a clone (deep-copy) of an array
  Array* clone() const;
  /// Copies data into an Array
  void copy_in(const Real *input) override;
  /// Copies data out of an Array
  void copy_out(Real *output) const override;
  /// Returns the number of elements in an Array
  std::size_t size() const override;

private:
  void *f_ptr_; // pointer to Fortran array implementation
};

} // namespace aero

#endif
