/*===-- interface/state/ai_bridge_state.h -------------------------*- C -*-===//
 *
 * Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 *
 *===----------------------------------------------------------------------===//
 *
 * C/C++ <--> Fortran bridge functions for the State class
 *
 *===----------------------------------------------------------------------===//
 */
#ifndef AERO_STATE_BRIDGE_H
#define AERO_STATE_BRIDGE_H

#ifdef __cplusplus
extern "C" {
#endif

/// Returns a pointer to a newly cloned (deep-copied) aerosol state implemented
/// in C.
void* aero_bridge_c_state_clone(void *state);

/// Returns a pointer to a newly cloned (deep-copied) aerosol state implemented
/// in C++.
void* aero_bridge_cpp_state_clone(void *state);

/// Returns a pointer to a newly cloned (deep-copied) aerosol state implemented
/// in Fortran.
void* aero_bridge_fortran_state_clone(void *state);

/// Frees resources associated with the given C aerosol state.
void aero_bridge_c_state_free(void *state);

/// Frees resources associated with the given C++ aerosol state.
void aero_bridge_cpp_state_free(void *state);

/// Frees resources associated with the given Fortran aerosol state.
void aero_bridge_fortran_state_free(void *state);

#ifdef __cplusplus
}
#endif

#endif
