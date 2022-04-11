#ifndef AERO_CPP_ARRAY_H
#define AERO_CPP_ARRAY_H

#include <aero/aero.h>
#include "array.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Creates an array by wrapping a C++-backed array
aero_array_t* aero_cpp_array_wrap(void *array);

/// "Unwraps" a wrapped C++-backed array, freeing the wrapper resources but
/// leaving the original C++ array intact.
void aero_cpp_array_unwrap(aero_array_t *array);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
