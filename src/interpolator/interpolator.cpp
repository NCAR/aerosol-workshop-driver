#include <aero/interpolator/interpolator.hpp>

namespace aero {

std::vector<std::tuple<int, int, Real>> create_map(const Grid& from, const Grid &to) {
  std::vector<std::tuple<int, int, Real>> map;
  const Real *from_a = from.interfaces().data();
  const Real *to_a   = to.interfaces().data();
  Real weight;
  for (int i=0; i<from.interfaces().size()-1; ++i) {
    for (int j=0; j<to.interfaces().size()-1; ++j) {
      if (to_a[j] < from_a[i+1] && from_a[i] < to_a[j+1]) {
        weight = std::max(0.0, std::min(from_a[i+1], to_a[j+1]) - std::max(from_a[i], to_a[j]));
        weight /= (from_a[i+1] - from_a[i]);
        map.push_back(std::tuple<int, int, Real>(i, j, weight));
      }
    }
  }
  return map;
}

Interpolator::Interpolator(const Grid& from, const Grid& to) : map_(create_map(from, to)) {}

void Interpolator::operator()(const Array& from, Array& to) const {
  this->interpolate(from, to);
}

Interpolator* Interpolator::clone() const {
  return new Interpolator(this->map_);
}

void Interpolator::interpolate(const Array& from, Array& to) const {
  for (int i=0; i<to.size(); ++i) to[i] = 0.0;
  for (auto& map_elem : this->map_) {
    to[std::get<1>(map_elem)] += from[std::get<0>(map_elem)] * std::get<2>(map_elem);
  }
}

Interpolator::Interpolator(const std::vector<std::tuple<int, int, Real>> map) :
  map_(map) {}

} // namespace aero
