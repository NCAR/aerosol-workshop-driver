#ifndef AERO_INTERPOLATOR_HPP
#define AERO_INTERPOLATOR_HPP

#include <vector>
#include <tuple>
#include <aero/aero.hpp>
#include <aero/array/array.hpp>
#include <aero/grid/grid.hpp>

namespace aero {

class Interpolator {
public:
  /// No default constructor
  Interpolator() = delete;
  /// Deleted copy constructor
  Interpolator(const Interpolator&) = delete;
  /// Move constructor
  Interpolator(Interpolator&&) = default;
  /// Constructor from input and output grids
  Interpolator(const Grid& from, const Grid& to);

  /// Destructor
  virtual ~Interpolator() {}

  /// Deleted assignment operator
  Interpolator& operator=(const Interpolator&) = delete;
  /// Deleted move assignment operator
  Interpolator& operator=(Interpolator&&) = delete;
  /// Function call operator
  void operator()(const Array& from, Array& to) const;

  /// Returns a clone (deep-copy) of an Interpolator
  virtual Interpolator* clone() const;
  /// Interpolates from an array on the input grid to an array
  /// on the output grid
  void interpolate(const Array& from, Array& to) const;

private:
  /// Constructor from weighted map
  Interpolator(const std::vector<std::tuple<int, int, Real>> map);

  /// Weighted map (from index, to index, weight)
  const std::vector<std::tuple<int, int, Real>> map_;

};

} // namespace aero

#endif
