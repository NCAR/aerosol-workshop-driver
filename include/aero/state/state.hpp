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

} // namespace aero

#endif
