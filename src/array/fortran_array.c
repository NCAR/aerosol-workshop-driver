#include <aero/array/fortran_array.h>
#include "array_bridge.h"
#include <stdlib.h>

struct aero_array_data_t {
  void* fortran_array_;
};

aero_array_t* aero_fortran_array_create(aero_array_data_t *array_data) {
  aero_array_t *array;
  array = malloc(sizeof(aero_array_t));
  array->data_ = array_data;
  array->clone = aero_fortran_array_clone;
  array->free = aero_fortran_array_free;
  array->copy_in = aero_fortran_array_copy_in;
  array->copy_out = aero_fortran_array_copy_out;
  array->size = aero_fortran_array_size;
  return array;
}

aero_array_t* aero_fortran_array_wrap(void *fortran_array) {
  aero_array_data_t *array_data = malloc(sizeof(aero_array_data_t));
  array_data->fortran_array_ = fortran_array;
  return aero_fortran_array_create(array_data);
}

aero_array_t* aero_fortran_array_clone(aero_array_t *from) {
  aero_array_data_t *array_data = malloc(sizeof(aero_array_data_t));
  array_data->fortran_array_ =
    aero_bridge_fortran_array_clone(from->data_->fortran_array_);
  return aero_fortran_array_create(array_data);
}

void aero_fortran_array_free(aero_array_t *array) {
  aero_bridge_fortran_array_free(array->data_->fortran_array_);
  free(array->data_);
  free(array);
}

void aero_fortran_array_copy_in(aero_array_t *array, aero_real_t *from) {
  aero_bridge_fortran_array_copy_in(array->data_->fortran_array_, from);
}

void aero_fortran_array_copy_out(aero_array_t *array, aero_real_t *to) {
  aero_bridge_fortran_array_copy_out(array->data_->fortran_array_, to);
}

unsigned int aero_fortran_array_size(aero_array_t *array) {
  return aero_bridge_fortran_array_size(array->data_->fortran_array_);
}
