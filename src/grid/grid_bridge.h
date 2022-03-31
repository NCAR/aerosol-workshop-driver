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

// C grid struct
struct aero_grid_t {
  // Arrays for grid interfaces and midpoints.
  aero_array_t *interfaces, *midpoints;
  // Lower and upper bounds.
  aero_grid_bounds_t bounds;
};

// Given a C++ pointer to a grid, returns a C++ pointer to the array storing
// its interfaces.
void* aero_bridge_cpp_grid_interfaces(void *cpp_ptr);

// Given a Fortran pointer to a grid, returns a Fortran pointer to the array
// storing its interfaces.
void* aero_bridge_fortran_grid_interfaces(void *f_ptr);

// Given a C pointer to a grid, returns a C pointer to the array storing
// its interfaces.
void* aero_bridge_c_grid_interfaces(void *c_ptr);

#ifdef __cplusplus
}
#endif

#endif
