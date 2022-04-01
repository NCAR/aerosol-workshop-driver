#ifndef AERO_ARRAY_HPP
#define AERO_ARRAY_HPP

#include <aero/array/array.hpp>

namespace aero {

/// This Array subclass allows access to arrays implemented in
/// Fortran.
class FortranArray: public Array {
public:

  /// Construct an aerosol model wrapped around a Fortran implementation
  /// that can be accessed with the given pointer.
  explicit FortranArray(void *fortran_pointer);

  // Overridden functionality

  FortranArray(FortranArray& other);
  FortranArray(FortranArray&& other);
  ~FortranArray() override;

  FortranArray& operator=(FortranArray& other);
  FortranArray& operator=(FortranArray&& other);

  void *f_ptr_; // pointer to Fortran array implementation
};

} // namespace aero

#endif
