#include <aero/array/cpp_array.h>
#include "array_bridge.h"
#include <stdlib.h>

struct aero_array_data_t {
  void* cpp_array_;
};

static aero_array_t* aero_cpp_array_create(aero_array_data_t *array_data);

static aero_array_t* aero_cpp_array_clone(aero_array_t *from) {
  aero_array_data_t *array_data = malloc(sizeof(aero_array_data_t));
  array_data->cpp_array_ =
    aero_bridge_cpp_array_clone(from->data_->cpp_array_);
  return aero_cpp_array_create(array_data);
}

static void aero_cpp_array_free(aero_array_t *array) {
  aero_bridge_cpp_array_free(array->data_->cpp_array_);
  free(array->data_);
  free(array);
}

static void aero_cpp_array_copy_in(aero_array_t *array, const aero_real_t *from) {
  aero_bridge_cpp_array_copy_in(array->data_->cpp_array_, from);
}

static void aero_cpp_array_copy_out(const aero_array_t *array, aero_real_t *to) {
  aero_bridge_cpp_array_copy_out(array->data_->cpp_array_, to);
}

static const aero_real_t* aero_cpp_array_const_data(const aero_array_t *array) {
  return aero_bridge_cpp_array_data(array->data_->cpp_array_);
}

static aero_real_t* aero_cpp_array_data(aero_array_t *array) {
  return aero_bridge_cpp_array_data(array->data_->cpp_array_);
}

static size_t aero_cpp_array_size(const aero_array_t *array) {
  return aero_bridge_cpp_array_size(array->data_->cpp_array_);
}

static aero_array_t* aero_cpp_array_create(aero_array_data_t *array_data) {
  aero_array_t *array;
  array = malloc(sizeof(aero_array_t));
  array->data_ = array_data;
  array->clone = aero_cpp_array_clone;
  array->free = aero_cpp_array_free;
  array->copy_in = aero_cpp_array_copy_in;
  array->copy_out = aero_cpp_array_copy_out;
  array->const_data = aero_cpp_array_const_data;
  array->data = aero_cpp_array_data;
  array->size = aero_cpp_array_size;
  return array;
}

aero_array_t* aero_cpp_array_wrap(void *cpp_array) {
  aero_array_data_t *array_data = malloc(sizeof(aero_array_data_t));
  array_data->cpp_array_ = cpp_array;
  return aero_cpp_array_create(array_data);
}

void aero_cpp_array_unwrap(aero_array_t *cpp_array) {
  free(cpp_array->data_);
  free(cpp_array);
}

