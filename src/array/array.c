#include <aero/array/array.h>
#include <stdlib.h>

struct aero_array_t {
  int size_;
  aero_real_t *values_;
};

aero_array_t* aero_array_from_dimensions(const int number_of_elements,
    aero_real_t initial_value) {
  aero_array_t *array = malloc(sizeof(aero_array_t));
  array->size_ = number_of_elements;
  array->values_ = malloc(sizeof(aero_real_t)*array->size_);
  for (int i=0; i<array->size_; ++i) array->values_[i] = initial_value;
  return array;
}

aero_array_t* aero_array_from_array(const int number_of_elements,
    aero_real_t *values) {
  aero_array_t *array = malloc(sizeof(aero_array_t));
  array->size_ = number_of_elements;
  array->values_ = malloc(sizeof(aero_real_t)*array->size_);
  for (int i=0; i<array->size_; ++i) array->values_[i] = values[i];
  return array;
}

aero_array_t* aero_array_clone(aero_array_t *from) {
  aero_array_t *array = malloc(sizeof(aero_array_t));
  array->size_ = array->size_;
  array->values_ = malloc(sizeof(aero_real_t)*array->size_);
  for (int i=0; i<array->size_; ++i) array->values_[i] = from->values_[i];
  return array;
}

void aero_array_free(aero_array_t *array) {
  free(array->values_);
  free(array);
}

void aero_array_copy_in(aero_array_t *array, aero_real_t *from) {
  for (int i=0; i<array->size_; ++i) array->values_[i] = from[i];
}

void aero_array_copy_out(aero_array_t *array, aero_real_t *to) {
  for (int i=0; i<array->size_; ++i) to[i] = array->values_[i];
}

int aero_array_size(aero_array_t *array) {
  return array->size_;
}
