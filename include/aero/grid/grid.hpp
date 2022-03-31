#ifndef AERO_GRID_HPP
#define AERO_GRID_HPP

namespace aero {

/// Simple container for storing grid lower/upper bounds.
struct GridBounds {
  Real lower, upper;
};

/// This type represents a computional grid consisting of a set of contiguous
/// segments separated by interfaces. The grid keeps track of the midpoints
/// between interfaces.
class Grid final {
public:
  // No Default constructor for Grids
  Grid() = delete;
  // No copy constructor, either
  Grid(const Grid& other) = delete;

  /// Creates a Grid from an Array containing points delimiting the interfaces
  /// between segments. The Grid assumes ownership of this array.
  explicit Grid(Array&& interfaces);

  /// Creates a Grid from a C pointer to a Grid. The Grid itself is copied
  /// so it lives in both C and C++ runtimes.
  static Grid from_c_ptr(void *c_ptr);

  /// Creates a Grid from a Fortran pointer to a Grid. The Grid itself is copied
  /// so it lives in both Fortran and C++ runtimes.
  static Grid from_fortran_ptr(void *f_ptr);

  /// Move constructor
  Grid(Grid&& other) = default;

  /// Destructor
  ~Grid();

  /// Default move assignment operator
  Grid& operator=(Grid&&) = default;

  /// Returns the lower bound (minimum grid interface point) for the grid.
  GridBounds bounds() const { return bounds_; }

  /// Provides const access to the array containing grid interfaces.
  const Array& interfaces() const { return interfaces_; }

  /// Provides const access to the array containing grid segment midpoints.
  const Array& midpoints() const { return midpoints_; }

private:
  // Arrays containing interfaces and segment midpoints.
  Array interfaces_, midpoints_;
  // Lower and upper bounds.
  GridBounds bounds_;
};

} // namespace aero

#endif
