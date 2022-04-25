#include "array_bridge.h"
#include "wrap_array.h"
#include <aero/array/array.h>
#include <aero/array/fortran_array.h>
#include <stdlib.h>

struct aero_array_data_t {
  bool owns_array_;
  void* f_ptr_;
};

static aero_array_t* aero_fortran_array_create(aero_array_data_t *array_data);

static aero_array_t* aero_fortran_array_clone(aero_array_t *from) {
  aero_array_data_t *array_data = malloc(sizeof(aero_array_data_t));
  array_data->f_ptr_ =
    aero_bridge_fortran_array_clone(from->data_->f_ptr_);
  array_data->owns_array_ = true;
  return aero_fortran_array_create(array_data);
}

static void aero_fortran_array_free(aero_array_t *array) {
  if (array->data_->owns_array_) {
    aero_bridge_fortran_array_free(array->data_->f_ptr_);
  } else {
    aero_bridge_fortran_array_free_wrapper(array->data_->f_ptr_);
  }
  free(array->data_);
  free(array);
}

static void aero_fortran_array_copy_in(aero_array_t *array, const aero_real_t *from) {
  aero_bridge_fortran_array_copy_in(array->data_->f_ptr_, from);
}

static void aero_fortran_array_copy_out(const aero_array_t *array, aero_real_t *to) {
  aero_bridge_fortran_array_copy_out(array->data_->f_ptr_, to);
}

static const aero_real_t *aero_fortran_array_const_data(const aero_array_t* array) {
  return aero_bridge_fortran_array_data(array->data_->f_ptr_);
}

static aero_real_t *aero_fortran_array_data(aero_array_t *array) {
  return aero_bridge_fortran_array_data(array->data_->f_ptr_);
}

static size_t aero_fortran_array_size(const aero_array_t *array) {
  return aero_bridge_fortran_array_size(array->data_->f_ptr_);
}

const void* aero_fortran_array_cpp_const_ptr(const aero_array_t *array) {
  return NULL;
}

const void* aero_fortran_array_fortran_const_ptr(const aero_array_t *array) {
  return array->data_->f_ptr_;
}

void* aero_fortran_array_cpp_ptr(aero_array_t *array) {
  return NULL;
}

void* aero_fortran_array_fortran_ptr(aero_array_t *array) {
  return array->data_->f_ptr_;
}

static aero_array_t* aero_fortran_array_create(aero_array_data_t *array_data) {
  aero_array_t *array;
  array = malloc(sizeof(aero_array_t));
  array->data_ = array_data;
  array->clone = aero_fortran_array_clone;
  array->free = aero_fortran_array_free;
  array->copy_in = aero_fortran_array_copy_in;
  array->copy_out = aero_fortran_array_copy_out;
  array->const_data = aero_fortran_array_const_data;
  array->data = aero_fortran_array_data;
  array->size = aero_fortran_array_size;
  array->cpp_const_ptr = aero_fortran_array_cpp_const_ptr;
  array->fortran_const_ptr = aero_fortran_array_fortran_const_ptr;
  array->cpp_ptr = aero_fortran_array_cpp_ptr;
  array->fortran_ptr = aero_fortran_array_fortran_ptr;
  return array;
}

void* aero_fortran_array_wrap_c(void *fortran_array) {
  aero_array_data_t *array_data = malloc(sizeof(aero_array_data_t));
  array_data->f_ptr_ = fortran_array;
  array_data->owns_array_ = false;
  return aero_fortran_array_create(array_data);
}

void aero_fortran_array_unwrap_c(void *c_array) {
  aero_array_t* array = (aero_array_t*) c_array;
  array->free(array);
}

aero_array_t* aero_new_fortran_array(void *fortran_array, bool owns_array) {
  aero_array_t* array = (aero_array_t*) aero_fortran_array_wrap_c(fortran_array);
  array->data_->owns_array_ = owns_array;
  return array;
}
