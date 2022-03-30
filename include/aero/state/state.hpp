#ifndef AERO_STATE_HPP
#define AERO_STATE_HPP

namespace aero {

class State {
public:
  /// Default constructor.
  State() = default;
  /// Copy constructor
  State(const State&) = default;
  /// Move constructor
  State(State&&) = default;

  /// Destructor
  virtual ~State() {}

  /// Assignment operator
  State& operator=(const State&) = default;
  /// Default move assignment operator
  State& operator=(State&&) = default;
};

/// This State subclass allows access to aerosol states implemented in
/// Fortran.
class FortranState: public State {
public:

  /// Construct an aerosol model wrapped around a Fortran implementation
  /// that can be accessed with the given pointer.
  explicit FortranState(void *fortran_pointer);

  // Overridden functionality

  FortranState(FortranState& other);
  FortranState(FortranState&& other);
  ~FortranState() override;

  FortranState& operator=(FortranState& other);
  FortranState& operator=(FortranState&& other);

  void *f_ptr_; // pointer to Fortran state implementation
};

} // namespace aero

#endif
