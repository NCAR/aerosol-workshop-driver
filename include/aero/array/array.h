#ifndef AERO_ARRAY_H
#define AERO_ARRAY_H

#include <aero/aero.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/// This opaque type represents an implementation of an Array
typedef struct aero_array_data_t aero_array_data_t;

/// Behaviors and data associated with an Array. All of these functions
/// are passed the data pointer created by an Array constructor
typedef struct aero_array_t aero_array_t;
typedef struct aero_array_t {
  /// pointer to the array data
  aero_array_data_t *data_;
  /// returns a clone (deep-copy) of an array
  aero_array_t* (*clone)(aero_array_t *from);
  /// frees resources associated with an array
  void (*free)(aero_array_t *array);
  /// copies data into an array
  void (*copy_in)(aero_array_t *array, const aero_real_t *from);
  /// copies data out of an array
  void (*copy_out)(aero_array_t *array, aero_real_t *to);
  /// returns the number of elements in an array
  size_t (*size)(aero_array_t *array);
} aero_array_t;

/// Creates an array from a number of elements and an initial value
aero_array_t* aero_array_from_dimensions(size_t size,
    aero_real_t initial_value);

/// Creates an array from a primitive type array
aero_array_t* aero_array_from_array(size_t size,
    aero_real_t *values);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
