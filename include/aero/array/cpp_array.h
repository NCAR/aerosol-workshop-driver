#ifndef AERO_CPP_ARRAY_H
#define AERO_CPP_ARRAY_H

#include <aero/array/array.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Creates a new C++-Backed C array
/// The flag \c owns_array is used to indicate whether this wrapper owns
/// the underlying array
aero_array_t* aero_new_cpp_array(void *cpp_array, bool owns_array);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
