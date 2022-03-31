#ifndef AERO_ARRAY_H
#define AERO_ARRAY_H

#include <aero/aero.h>

#ifdef __cplusplus
extern "C" {
#endif

/// This opaque type represents an array implemented in C.
typedef struct aero_array_t aero_array_t;

/// Creates an array from a number of elements and an initial value
aero_array_t* aero_array_from_dimensions(const int number_of_elements,
    aero_real_t initial_value);

/// Creates an array from a primitive type array
aero_array_t* aero_array_from_array(const int number_of_elements,
    aero_real_t *values);

/// Creates an an array by cloning (deep-copying) an array
aero_array_t* aero_array_clone(aero_array_t *from);

/// Frees the resources associated with an array
void aero_array_free(aero_array_t *array);

/// Copies values into an array
void aero_array_copy_in(aero_array_t *array, aero_real_t *from);

/// Copies values out of an array
void aero_array_copy_out(aero_array_t *array, aero_real_t *to);

/// Returns the number of elements in the array
int aero_array_size(aero_array_t *array);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
