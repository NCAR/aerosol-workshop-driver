#ifndef AERO_STATE_HPP
#define AERO_STATE_HPP

namespace aero {

class State {
public:
  /// Default constructor.
  State() = default;
  /// Copy constructor
  State(const State&) = delete;
  /// Move constructor
  State(State&&) = delete;

  /// Destructor
  virtual ~State() {}

  /// Assignment operator
  State& operator=(const State&) = delete;
  /// Default move assignment operator
  State& operator=(State&&) = delete;
};

} // namespace aero

#endif
