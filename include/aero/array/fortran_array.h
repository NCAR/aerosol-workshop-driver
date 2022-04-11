#ifndef AERO_FORTRAN_ARRAY_H
#define AERO_FORTRAN_ARRAY_H

#include <aero/aero.h>
#include "array.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Creates an array by wrapping a Fortran-backed array
aero_array_t* aero_fortran_array_wrap(void *array);

/// "Unwraps" a wrapped Fortran-backed array, freeing the wrapper resources but
/// leaving the original Fortran array intact.
void aero_fortran_array_unwrap(aero_array_t *array);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
