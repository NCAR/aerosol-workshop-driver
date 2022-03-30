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
#ifndef AERO_GRID_BRIDGE_H
#define AERO_GRID_BRIDGE_H

#ifdef __cplusplus
extern "C" {
#endif

/// Returns a pointer to a newly cloned (deep-copied) grid implemented in C.
void* aero_bridge_c_grid_clone(void *grid);

/// Returns a pointer to a newly cloned (deep-copied) grid implemented in C++.
void* aero_bridge_cpp_grid_clone(void *grid);

/// Returns a pointer to a newly cloned (deep-copied) grid implemented in
/// Fortran.
void* aero_bridge_fortran_grid_clone(void *grid);

/// Frees resources associated with the given C grid.
void aero_bridge_c_grid_free(void *grid);

/// Frees resources associated with the given C++ grid.
void aero_bridge_cpp_grid_free(void *grid);

/// Frees resources associated with the given Fortran grid.
void aero_bridge_fortran_grid_free(void *grid);

#ifdef __cplusplus
}
#endif

#endif
