#include <aero/interpolator/interpolator.h>
#include <stdlib.h>
#include <tgmath.h>

typedef struct aero_interpolator_data_elem_t {
  int from_;
  int to_;
  aero_real_t weight_;
} aero_interpolator_data_elem_t;

struct aero_interpolator_data_t {
  aero_interpolator_data_elem_t *map_;
  int n_map_elem_;
};

static aero_interpolator_t* aero_interpolator_create(aero_interpolator_data_t
  *interpolator_data);

static aero_interpolator_t* aero_interpolator_clone(aero_interpolator_t *from) {
  aero_interpolator_data_t *interpolator_data = malloc(sizeof(aero_interpolator_data_t));
  interpolator_data->n_map_elem_ = from->data_->n_map_elem_;
  interpolator_data->map_ =
    malloc(interpolator_data->n_map_elem_*sizeof(aero_interpolator_data_elem_t));
  for (int i=0; i<interpolator_data->n_map_elem_; ++i) {
    interpolator_data->map_[i].from_   = from->data_->map_[i].from_;
    interpolator_data->map_[i].to_     = from->data_->map_[i].to_;
    interpolator_data->map_[i].weight_ = from->data_->map_[i].weight_;
  }
  return aero_interpolator_create(interpolator_data);
}

static void aero_interpolator_free(aero_interpolator_t *interp) {
  free(interp->data_->map_);
  free(interp->data_);
  free(interp);
}

static void aero_interpolator_interpolate(const aero_interpolator_t *interp,
  const aero_array_t *from, aero_array_t *to) {
  const aero_real_t *from_a = from->const_data(from);
  aero_real_t *to_a = to->data(to);
  for (int i=0; i<to->size(to); ++i) to_a[i] = 0.0;
  for (int i=0; i<interp->data_->n_map_elem_; ++i) {
    to_a[interp->data_->map_[i].to_] += from_a[interp->data_->map_[i].from_] *
      interp->data_->map_[i].weight_;
  }
}

static aero_interpolator_t* aero_interpolator_create(aero_interpolator_data_t
  *interpolator_data) {
  aero_interpolator_t *interp;
  interp = malloc(sizeof(aero_interpolator_t));
  interp->data_ = interpolator_data;
  interp->clone = aero_interpolator_clone;
  interp->free = aero_interpolator_free;
  interp->interpolate = aero_interpolator_interpolate;
  return interp;
}

aero_interpolator_t* aero_linear_interpolator(const aero_grid_t *from,
  const aero_grid_t *to) {
  aero_interpolator_data_t *interp_data = malloc(sizeof(aero_interpolator_data_t));
  size_t map_size = 0;
  const aero_array_t *from_array = aero_grid_interfaces(from);
  const aero_array_t *to_array   = aero_grid_interfaces(to);
  const aero_real_t *from_a = from_array->const_data(from_array);
  const aero_real_t *to_a   = to_array->const_data(to_array);
  aero_real_t weight;
  for (int i=0; i<from_array->size(from_array)-1; ++i) {
    for (int j=0; j<to_array->size(to_array)-1; ++j) {
      if (to_a[j] < from_a[i+1] && from_a[i] < to_a[j+1]) ++map_size;
    }
  }
  interp_data->n_map_elem_ = map_size;
  interp_data->map_ = malloc(map_size*sizeof(aero_interpolator_data_elem_t));
  for (int i=0, i_map=0; i<from_array->size(from_array)-1; ++i) {
    for (int j=0; j<to_array->size(to_array)-1; ++j) {
      if (to_a[j] < from_a[i+1] && from_a[i] < to_a[j+1]) {
        weight = fmax(0.0, fmin(from_a[i+1], to_a[j+1]) - fmax(from_a[i], to_a[j]));
        weight /= (from_a[i+1] - from_a[i]);
        interp_data->map_[i_map++] =
          (aero_interpolator_data_elem_t){.from_=i, .to_=j, .weight_=weight};
      }
    }
  }
  return aero_interpolator_create(interp_data);
}
