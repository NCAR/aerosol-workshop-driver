#ifndef AI_ARRAY_HPP
#define AI_ARRAY_HPP

namespace ai {

class Array {
public:
  /// Default constructor.
  Array() = default;
  /// Copy constructor
  Array(const Array& other) = default;
  /// Move constructor
  Array(Array&& other) = default;

  /// Destructor
  virtual ~Array() {}

  /// Assignment operator
  Array& operator=(const Array&) = default;
  /// Default move assignment operator
  Array& operator=(Array&&) = default;
};

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

} // namespace ai

#endif
