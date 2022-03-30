#ifndef AERO_GRID_HPP
#define AERO_GRID_HPP

namespace aero {

class Grid {
public:
  /// Default constructor.
  Grid() = default;
  /// Copy constructor
  Grid(const Grid& other) = default;
  /// Move constructor
  Grid(Grid&& other) = default;

  /// Destructor
  virtual ~Grid() {}

  /// Assignment operator
  Grid& operator=(const Grid&) = default;
  /// Default move assignment operator
  Grid& operator=(Grid&&) = default;
};

/// This Grid subclass allows access to arrays implemented in Fortran.
class FortranGrid: public Grid {
public:

  /// Construct an aerosol model wrapped around a Fortran implementation
  /// that can be accessed with the given pointer.
  explicit FortranGrid(void *fortran_pointer);

  // Overridden functionality

  FortranGrid(FortranGrid& other);
  FortranGrid(FortranGrid&& other);
  ~FortranGrid() override;

  FortranGrid& operator=(FortranGrid& other);
  FortranGrid& operator=(FortranGrid&& other);

  void *f_ptr_; // pointer to Fortran grid implementation
};

} // namespace aero

#endif
