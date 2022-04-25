#include <aero/array/array.h>
#include <stdlib.h>
#include "wrap_array.h"

struct aero_array_data_t {
  int size_;
  aero_real_t *values_;
  void* cpp_ptr_;
  void* f_ptr_;
};

static aero_array_t* aero_array_create(aero_array_data_t *array_data);

static aero_array_t* aero_array_clone(aero_array_t *from) {
  aero_array_data_t *array_data = malloc(sizeof(aero_array_data_t));
  array_data->size_ = from->data_->size_;
  array_data->values_ = malloc(sizeof(aero_real_t)*array_data->size_);
  for (int i=0; i<array_data->size_; ++i) {
    array_data->values_[i] = from->data_->values_[i];
  }
  return aero_array_create(array_data);
}

static void aero_array_free(aero_array_t *array) {
  aero_fortran_array_unwrap_cpp(array->data_->cpp_ptr_);
  aero_cpp_array_unwrap_fortran(array->data_->f_ptr_);
  free(array->data_->values_);
  free(array->data_);
  free(array);
}

static void aero_array_copy_in(aero_array_t *array, const aero_real_t *from) {
  for (int i=0; i<array->data_->size_; ++i) array->data_->values_[i] = from[i];
}

static void aero_array_copy_out(const aero_array_t *array, aero_real_t *to) {
  for (int i=0; i<array->data_->size_; ++i) to[i] = array->data_->values_[i];
}

static const aero_real_t* aero_array_const_data(const aero_array_t *array) {
  return array->data_->values_;
}

static aero_real_t* aero_array_data(aero_array_t *array) {
  return array->data_->values_;
}

static size_t aero_array_size(const aero_array_t *array) {
  return array->data_->size_;
}

static const void* aero_array_cpp_const_ptr(const aero_array_t *array) {
  return array->data_->cpp_ptr_;
}

static const void* aero_array_fortran_const_ptr(const aero_array_t *array) {
  return array->data_->f_ptr_;
}

static void* aero_array_cpp_ptr(aero_array_t *array) {
  return array->data_->cpp_ptr_;
}

static void* aero_array_fortran_ptr(aero_array_t *array) {
  return array->data_->f_ptr_;
}

static aero_array_t* aero_array_create(aero_array_data_t *array_data) {
  aero_array_t *array = malloc(sizeof(aero_array_t));
  array->data_ = array_data;
  array->clone = aero_array_clone;
  array->free = aero_array_free;
  array->copy_in = aero_array_copy_in;
  array->copy_out = aero_array_copy_out;
  array->const_data = aero_array_const_data;
  array->data = aero_array_data;
  array->size = aero_array_size;
  array->cpp_const_ptr = aero_array_cpp_const_ptr;
  array->fortran_const_ptr = aero_array_fortran_const_ptr;
  array->cpp_ptr = aero_array_cpp_ptr;
  array->fortran_ptr = aero_array_fortran_ptr;
  array_data->cpp_ptr_ = (void*) aero_c_array_wrap_cpp((void*)array);
  array_data->f_ptr_   = (void*) aero_c_array_wrap_fortran((void*)array);
  return array;
}

aero_array_t* aero_array_from_dimensions(size_t size,
    aero_real_t initial_value) {
  aero_array_data_t *array_data = malloc(sizeof(aero_array_data_t));
  array_data->size_ = size;
  array_data->values_ = malloc(sizeof(aero_real_t)*array_data->size_);
  for (int i=0; i<array_data->size_; ++i) array_data->values_[i] = initial_value;
  return aero_array_create(array_data);
}

aero_array_t* aero_array_from_array(size_t size,
    const aero_real_t *values) {
  aero_array_data_t *array_data = malloc(sizeof(aero_array_data_t));
  array_data->size_ = size;
  array_data->values_ = malloc(sizeof(aero_real_t)*array_data->size_);
  for (int i=0; i<array_data->size_; ++i) array_data->values_[i] = values[i];
  return aero_array_create(array_data);
}

