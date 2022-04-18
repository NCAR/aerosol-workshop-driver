/*===-- interface/array/ai_bridge_array.h -------------------------*- C -*-===//
 *
 * Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 *
 *===----------------------------------------------------------------------===//
 *
 * C/C++ <--> Fortran bridge functions for the Array class
 *
 *===----------------------------------------------------------------------===//
 */
#ifndef AERO_ARRAY_BRIDGE_H
#define AERO_ARRAY_BRIDGE_H

#include <aero/aero.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Returns a pointer to a newly cloned (deep-copied) array implemented in C.
void* aero_bridge_c_array_clone(void *array);

/// Returns a pointer to a newly cloned (deep-copied) array implemented in C++.
void* aero_bridge_cpp_array_clone(void *array);

/// Returns a pointer to a newly cloned (deep-copied) array implemented in
/// Fortran.
void* aero_bridge_fortran_array_clone(void *array);

/// Frees resources associated with the given C array.
void aero_bridge_c_array_free(void *array);

/// Frees resources associated with the given C++ array.
void aero_bridge_cpp_array_free(void *array);

/// Frees resources associated with the given Fortran array.
void aero_bridge_fortran_array_free(void *array);

/// Copies data into the given C array
void aero_bridge_c_array_copy_in(void *array, const aero_real_t *input);

/// Copies data into the given C++ array
void aero_bridge_cpp_array_copy_in(void *array, const aero_real_t *input);

/// Copies data into the given Fortran array
void aero_bridge_fortran_array_copy_in(void *array, const aero_real_t *input);

/// Copies data out of the given C array
void aero_bridge_c_array_copy_out(void *array, aero_real_t *output);

/// Copies data out of the given C++ array
void aero_bridge_cpp_array_copy_out(void *array, aero_real_t *output);

/// Returns a pointer to the underlying data in a Fortran array
aero_real_t* aero_bridge_fortran_array_data(void *array);

/// Returns a pointer to the underlying data in a C array
aero_real_t* aero_bridge_c_array_data(void *array);

/// Returns a pointer to the underlying data in a C++ array
aero_real_t* aero_bridge_cpp_array_data(void *array);

/// Copies data out of the given Fortran array
void aero_bridge_fortran_array_copy_out(void *array, aero_real_t *output);

/// Returns the number of elements in the given C array
size_t aero_bridge_c_array_size(void *array);

/// Returns the number of elements in the given C++ array
size_t aero_bridge_cpp_array_size(void *array);

/// Returns the number of elements in the given Fortran array
size_t aero_bridge_fortran_array_size(void *array);

#ifdef __cplusplus
}
#endif

#endif
