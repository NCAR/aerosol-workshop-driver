#include "array_bridge.h"
#include "wrap_array.h"
#include <aero/array/array.h>
#include <aero/array/cpp_array.h>
#include <stdlib.h>

struct aero_array_data_t {
  bool owns_array_;
  void* cpp_ptr_;
};

static aero_array_t* aero_cpp_array_create(aero_array_data_t *array_data);

static aero_array_t* aero_cpp_array_clone(aero_array_t *from) {
  aero_array_data_t *array_data = malloc(sizeof(aero_array_data_t));
  array_data->cpp_ptr_ =
    aero_bridge_cpp_array_clone(from->data_->cpp_ptr_);
  array_data->owns_array_ = true;
  return aero_cpp_array_create(array_data);
}

static void aero_cpp_array_free(aero_array_t *array) {
  if (array->data_->owns_array_)
    aero_bridge_cpp_array_free(array->data_->cpp_ptr_);
  free(array->data_);
  free(array);
}

static void aero_cpp_array_copy_in(aero_array_t *array, const aero_real_t *from) {
  aero_bridge_cpp_array_copy_in(array->data_->cpp_ptr_, from);
}

static void aero_cpp_array_copy_out(const aero_array_t *array, aero_real_t *to) {
  aero_bridge_cpp_array_copy_out(array->data_->cpp_ptr_, to);
}

static const aero_real_t* aero_cpp_array_const_data(const aero_array_t *array) {
  return aero_bridge_cpp_array_data(array->data_->cpp_ptr_);
}

static aero_real_t* aero_cpp_array_data(aero_array_t *array) {
  return aero_bridge_cpp_array_data(array->data_->cpp_ptr_);
}

static size_t aero_cpp_array_size(const aero_array_t *array) {
  return aero_bridge_cpp_array_size(array->data_->cpp_ptr_);
}

static const void* aero_array_cpp_const_ptr(const aero_array_t *array) {
  return array->data_->cpp_ptr_;;
}

static const void* aero_array_fortran_const_ptr(const aero_array_t *array) {
  return NULL;
}

static void* aero_array_cpp_ptr(aero_array_t *array) {
  return array->data_->cpp_ptr_;
}

static void* aero_array_fortran_ptr(aero_array_t *array) {
  return NULL;
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
  array->cpp_const_ptr = aero_array_cpp_const_ptr;
  array->fortran_const_ptr = aero_array_fortran_const_ptr;
  array->cpp_ptr = aero_array_cpp_ptr;
  array->fortran_ptr = aero_array_fortran_ptr;
  return array;
}

void* aero_cpp_array_wrap_c(void *cpp_array) {
  aero_array_data_t *array_data = malloc(sizeof(aero_array_data_t));
  array_data->cpp_ptr_ = cpp_array;
  array_data->owns_array_ = false;
  return (void*)aero_cpp_array_create(array_data);
}

void aero_cpp_array_unwrap_c(void *c_array) {
  aero_array_t* array = (aero_array_t*) c_array;
  array->free(array);
}

aero_array_t* aero_new_cpp_array(void *cpp_array, bool owns_array) {
  aero_array_t* array = (aero_array_t*) aero_cpp_array_wrap_c(cpp_array);
  array->data_->owns_array_ = owns_array;
  return array;
}
