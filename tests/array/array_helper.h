// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
// Support functions for C/Fortran array tests

#include <aero/aero.h>

#if __cplusplus
extern "C" {
#endif

void *test_array_create_c_array();

void test_array_check_c_array(void *c_array, int index, aero_real_t value);

void *test_array_create_cpp_array();

void test_array_check_cpp_array(void *cpp_array, int index, aero_real_t value);

#if __cplusplus
} // extern "C"
#endif
