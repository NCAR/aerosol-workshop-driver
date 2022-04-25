#ifndef AERO_FORTRAN_ARRAY_H
#define AERO_FORTRAN_ARRAY_H

#include <aero/array/array.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Creates a new Fortran-backed C array
/// The flag \c owns_array is used to indicate whether this wrapper owns
/// the underlying array
aero_array_t* aero_new_fortran_array(void *fortran_array, bool owns_array);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
