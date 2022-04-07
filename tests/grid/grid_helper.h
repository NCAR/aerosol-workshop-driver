// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
// Support functions for C/Fortran array tests

#ifdef __cplusplus
extern "C" {
#endif

void *test_grid_create_c_interfaces();
void *test_grid_create_cpp_interfaces();
void *test_grid_create_fortran_interfaces();

#ifdef __cplusplus
} // extern "C"
#endif
