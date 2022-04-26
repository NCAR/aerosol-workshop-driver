#include <aero/interpolator/interpolator.hpp>

namespace aero {

// This structure holds the internals for the interpolator.
struct Interpolator::Impl {
  std::vector<std::size_t> from_points_;
  std::vector<Real>        from_weights_;
};

Interpolator::Interpolator(const Grid& from, const Grid& to)
  : impl_(new Interpolator::Impl) {
  const Array& from_array = from.interfaces();
  const Array& to_array   = to.interfaces();
  const Real* from_x = from_array.data();
  const Real* to_x   = to_array.data();

  // Build the "from" -> "to" mapping.
  size_t from_n = from_array.size();
  size_t to_n = to_array.size();
  impl_->from_points_.resize(2 * to_n);
  impl_->from_weights_.resize(2 * to_n);
  for (size_t i = 0; i < to_n; ++i) {
    // Find the "from" points to the left and right of this "to" point.
    auto lb_iter = std::lower_bound(from_x, from_x + from_n, to_x[i]);
    size_t lb = std::distance(from_x, lb_iter);
    if (lb >= from_n-1) { // off the end!
      impl_->from_points_[2*i]    = from_n-1; // left neighbor
      impl_->from_weights_[2*i]   = 1.0;
      impl_->from_points_[2*i+1]  = from_n-1; // no right neighbor
      impl_->from_weights_[2*i+1] = 0.0;
    } else {
      impl_->from_points_[2*i]    = lb;   // left neighbor
      impl_->from_weights_[2*i]   =
        1.0 - (to_x[i] - from_x[lb])/(from_x[lb+1]-from_x[lb]);
      impl_->from_points_[2*i+1]  = lb+1; // right neighbor
      impl_->from_weights_[2*i+1] =
        1.0 - (from_x[lb+1] - to_x[i])/(from_x[lb+1]-from_x[lb]);
    }
  }
}

Interpolator::~Interpolator() {
  delete impl_;
}

void Interpolator::operator()(const Array& from, Array& to) const {
  this->interpolate(from, to);
}

void Interpolator::interpolate(const Array& from, Array& to) const {
  const Real *from_a = from.data();
  Real *to_a = to.data();
  size_t to_n = to.size();
  for (size_t i = 0; i < to_n; ++i) {
    size_t j_left  = impl_->from_points_[2*i];
    Real w_left = impl_->from_weights_[2*i];
    size_t j_right = impl_->from_points_[2*i+1];
    Real w_right = impl_->from_weights_[2*i+1];
    to_a[i] = from_a[j_left] * w_left + from_a[j_right] * w_right;
  }
}

} // namespace aero
