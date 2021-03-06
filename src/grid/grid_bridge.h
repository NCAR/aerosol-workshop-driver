// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#ifndef AERO_GRID_BRIDGE_H
#define AERO_GRID_BRIDGE_H

#include <aero/grid/grid.h>

#ifdef __cplusplus
extern "C" {
#endif

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
