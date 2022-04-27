/* Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 *
 * Support functions for C++/Fortran MyModel template tests
 */

#include <aero/aero.h>

#if __cplusplus
extern "C" {
#endif

void *test_my_model_create_c_model();

void *test_my_model_create_cpp_model();

#if __cplusplus
} // extern "C"
#endif
