#ifndef AERO_GRID_HPP
#define AERO_GRID_HPP

#include <aero/array/array.hpp>

#include <memory>

namespace aero {

/// This type represents a computional grid consisting of a set of contiguous
/// segments separated by interfaces. The grid keeps track of the midpoints
/// between interfaces.
struct Grid final {
public:
  // A grid may be neither default constructed nor copied from another grid.
  Grid() = delete;
  Grid(const Grid&) = delete;
  Grid& operator=(const Grid&) = delete;

  /// Creates a grid from an Array containing points delimiting the interfaces
  /// between segments. The Grid assumes ownership of this array.
  explicit Grid(Array* interfaces);

  /// Creates a grid from a C pointer. The grid data is copied so it lives in
  /// both C and C++ runtimes.
  static Grid from_c_ptr(void *c_ptr);

  /// Creates a grid from a Fortran pointer. The Grid data is copied so it
  /// lives in both Fortran and C++ runtimes.
  static Grid from_fortran_ptr(void *f_ptr);

  /// Move constructor
  Grid(Grid&& other) = default;

  /// Destructor
  ~Grid();

  /// Default move assignment operator
  Grid& operator=(Grid&&) = default;

  /// Array storing interface coordinates (in ascending order)
  std::unique_ptr<Array> interfaces;

  /// Array storing coordinates of midpoints between interfaces (in ascending
  /// order)
  std::unique_ptr<Array> midpoints;

  /// Lower bound (minimum interface coordinate), provided for convenience
  Real lower_bound;
  /// Upper bound (maximum interface coordinate), provided for convenience
  Real upper_bound;
};

} // namespace aero

#endif
