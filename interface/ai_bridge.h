/*===-- interface/ai_bridge.h ---------------------------------*- C -*-===//
 *
 * Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 *
 *===----------------------------------------------------------------------===//
 *
 * C/C++ <--> Fortran bridge functions
 *
 *===----------------------------------------------------------------------===//
 */
#ifndef AI_BRIDGE_H
#define AI_BRIDGE_H

#ifdef __cplusplus
extern "C" {
#endif

//----------------
// Aerosol models
//----------------

/// Returns a pointer to a newly created aerosol model implemented in C
/// with the given package name, initialized using the given description file.
void* ai_bridge_c_new_aerosol(const char *package_name,
                              const char *description_file);

/// Returns a pointer to a newly created aerosol model implemented in C++
/// with the given package name, initialized using the given description file.
void* ai_bridge_cpp_new_aerosol(const char *package_name,
                                const char *description_file);

/// Returns a pointer to a newly created aerosol model implemented in Fortran
/// with the given package name, initialized using the given description file.
void* ai_bridge_f_new_aerosol(const char *package_name,
                              const char *description_file);

/// Frees resources associated with the given C aerosol model.
void ai_bridge_c_aerosol_free(void *aerosol);

/// Frees resources associated with the given C++ aerosol model.
void ai_bridge_cpp_aerosol_free(void *aerosol);

/// Frees resources associated with the given Fortran aerosol model.
void ai_bridge_f_aerosol_free(void *aerosol);

//----------------
// Aerosol states
//----------------

/// Returns a pointer to a newly cloned (deep-copied) aerosol state implemented
/// in C.
void* ai_bridge_c_state_clone(void *state);

/// Returns a pointer to a newly cloned (deep-copied) aerosol state implemented
/// in C++.
void* ai_bridge_cpp_state_clone(void *state);

/// Returns a pointer to a newly cloned (deep-copied) aerosol state implemented
/// in Fortran.
void* ai_bridge_f_state_clone(void *state);

/// Frees resources associated with the given C aerosol state.
void ai_bridge_c_state_free(void *aerosol);

/// Frees resources associated with the given C++ aerosol state.
void ai_bridge_cpp_state_free(void *aerosol);

/// Frees resources associated with the given Fortran aerosol state.
void ai_bridge_f_state_free(void *aerosol);

//--------
// Arrays
//--------

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

//-------
// Grids
//-------

/// Returns a pointer to a newly cloned (deep-copied) grid implemented in C.
void* ai_bridge_c_grid_clone(void *state);

/// Returns a pointer to a newly cloned (deep-copied) grid implemented in C++.
void* ai_bridge_cpp_grid_clone(void *state);

/// Returns a pointer to a newly cloned (deep-copied) grid implemented in
/// Fortran.
void* ai_bridge_f_grid_clone(void *state);

/// Frees resources associated with the given C grid.
void ai_bridge_c_grid_free(void *aerosol);

/// Frees resources associated with the given C++ grid.
void ai_bridge_cpp_grid_free(void *aerosol);

/// Frees resources associated with the given Fortran grid.
void ai_bridge_f_grid_free(void *aerosol);

#ifdef __cplusplus
}
#endif

#endif
