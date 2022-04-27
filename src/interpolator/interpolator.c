#include <aero/interpolator/interpolator.h>
#include <stdlib.h>
#include <tgmath.h>

// Linear interpolator implementation.
struct aero_interpolator_impl_t {
  // Both of these arrays are of length 2 * "to" grid size
  size_t *from_points_;       // indices of pts from "from" grid
  aero_real_t *from_weights_; // weights for "from" pts
};

static aero_interpolator_t* aero_interpolator_create(aero_interpolator_impl_t
  *interpolator_impl);

static void aero_interpolator_free(aero_interpolator_t *interp) {
  free(interp->impl_->from_points_);
  free(interp->impl_->from_weights_);
  free(interp->impl_);
  free(interp);
}

static void aero_interpolator_interpolate(const aero_interpolator_t *interp,
  const aero_array_t *from, aero_array_t *to) {
  const aero_real_t *from_a = from->const_data(from);
  aero_real_t *to_a = to->data(to);
  size_t to_n = to->size(to);
  for (size_t i=0; i < to_n; ++i) {
    size_t j_left  = interp->impl_->from_points_[2*i];
    aero_real_t w_left = interp->impl_->from_weights_[2*i];
    size_t j_right = interp->impl_->from_points_[2*i+1];
    aero_real_t w_right = interp->impl_->from_weights_[2*i+1];
    to_a[i] = from_a[j_left] * w_left + from_a[j_right] * w_right;
  }
}

static aero_interpolator_t* aero_interpolator_create(aero_interpolator_impl_t
  *interpolator_impl) {
  aero_interpolator_t *interp;
  interp = malloc(sizeof(aero_interpolator_t));
  interp->impl_ = interpolator_impl;
  interp->free = aero_interpolator_free;
  interp->interpolate = aero_interpolator_interpolate;
  return interp;
}

// This helper performs a binary search on sorted grid data, computing the index
// of the first point within the grid data that is no larger than the desired
// value.
static size_t lower_bound(const aero_real_t *data,
                          size_t size,
                          aero_real_t value) {
  // Till our paths cross...
  int low = 0, high = size;
  while (low < high) {
    int mid = low + (high - low) / 2;
    if (value <= data[mid]) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }

  if ((low < size) && (data[low] < value)) ++low;
  return low;
}

aero_interpolator_t* aero_linear_interpolator(const aero_grid_t *from,
  const aero_grid_t *to) {
  const aero_array_t *from_array = aero_grid_interfaces(from);
  const aero_array_t *to_array   = aero_grid_interfaces(to);
  const aero_real_t *from_x = from_array->const_data(from_array);
  const aero_real_t *to_x   = to_array->const_data(to_array);

  // Build the "from" -> "to" mapping.
  size_t from_n = from_array->size(from_array);
  size_t to_n = to_array->size(to_array);
  aero_interpolator_impl_t *impl = malloc(sizeof(aero_interpolator_impl_t));
  impl->from_points_ = malloc(sizeof(size_t) * 2 * to_n);
  impl->from_weights_ = malloc(sizeof(aero_real_t) * 2 * to_n);
  for (size_t i=0; i < to_n; ++i) {
    // Find the "from" points to the left and right of this "to" point.
    size_t lb = lower_bound(from_x, from_n, to_x[i]);
    if (lb == 0) { // off the lower end!
      impl->from_points_[2*i]    = 0; // no left neighbor
      impl->from_weights_[2*i]   = 0.0;
      impl->from_points_[2*i+1]  = 0; // right neighbor
      impl->from_weights_[2*i+1] = 1.0;
    } else if (lb >= from_n) { // off the upper end!
      impl->from_points_[2*i]    = from_n-1; // left neighbor
      impl->from_weights_[2*i]   = 1.0;
      impl->from_points_[2*i+1]  = from_n-1; // no right neighbor
      impl->from_weights_[2*i+1] = 0.0;
    } else {
      impl->from_points_[2*i]    = lb-1;   // left neighbor
      impl->from_weights_[2*i]   =
        1.0 - (to_x[i] - from_x[lb-1])/(from_x[lb]-from_x[lb-1]);
      impl->from_points_[2*i+1]  = lb; // right neighbor
      impl->from_weights_[2*i+1] =
        1.0 - (from_x[lb] - to_x[i])/(from_x[lb]-from_x[lb-1]);
    }
  }
  return aero_interpolator_create(impl);
}
