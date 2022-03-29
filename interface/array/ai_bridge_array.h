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
#ifndef AI_BRIDGE_ARRAY_H
#define AI_BRIDGE_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

/// Returns a pointer to a newly cloned (deep-copied) array implemented in C.
void* ai_bridge_c_array_clone(void *state);

/// Returns a pointer to a newly cloned (deep-copied) array implemented in C++.
void* ai_bridge_cpp_array_clone(void *state);

/// Returns a pointer to a newly cloned (deep-copied) array implemented in
/// Fortran.
void* ai_bridge_f_array_clone(void *state);

/// Frees resources associated with the given C array.
void ai_bridge_c_array_free(void *aerosol);

/// Frees resources associated with the given C++ array.
void ai_bridge_cpp_array_free(void *aerosol);

/// Frees resources associated with the given Fortran array.
void ai_bridge_f_array_free(void *aerosol);

#ifdef __cplusplus
}
#endif

#endif
