#ifndef AERO_FORTRAN_ARRAY_H
#define AERO_FORTRAN_ARRAY_H

#include <aero/aero.h>
#include "array.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Creates an array by wrapping a Fortran-backed array
aero_array_t* aero_fortran_array_wrap(void *array);

/// Creates an array by cloning (deep-copying) an array
aero_array_t* aero_fortran_array_clone(aero_array_t *from);

/// Frees the resources associated with an array
void aero_fortran_array_free(aero_array_t *array);

/// Copies values into an array
void aero_fortran_array_copy_in(aero_array_t *array, aero_real_t *from);

/// Copies values out of an array
void aero_fortran_array_copy_out(aero_array_t *array, aero_real_t *to);

/// Returns the number of elements in the array
unsigned int aero_fortran_array_size(aero_array_t *array);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
