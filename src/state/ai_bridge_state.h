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
#ifndef AI_BRIDGE_STATE_H
#define AI_BRIDGE_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif
