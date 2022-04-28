/* Copyright (C) 2022 National Center for Atmospheric Research,
 * National Technology & Engineering Solutions of Sandia, LLC (NTESS),
 * and the U.S. Environmental Protection Agency (USEPA)
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AERO_WRAP_ARRAY_H
#define AERO_WRAP_ARRAY_H

#include <aero/aero.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Creates an array by wrapping a C-backed array
/// @{
void* aero_c_array_wrap_cpp(void *c_array);
void* aero_c_array_wrap_fortran(void *c_array);
/// @}

/// Creates an array by wrapping a C++-backed array
/// @{
void* aero_cpp_array_wrap_c(void *cpp_array);
void* aero_cpp_array_wrap_fortran(void *cpp_array);
/// @}

/// Creates an array by wrapping a Fortran-backed array
/// @{
void* aero_fortran_array_wrap_c(void *fortran_array);
void* aero_fortran_array_wrap_cpp(void *fortran_array);
/// @}

/// "Unwraps" a wrapped C-backed array, freeing the wrapper resources but
/// leaving the original C array intact.
/// @{
void aero_c_array_unwrap_cpp(void *cpp_array);
void aero_c_array_unwrap_fortran(void *fortran_array);
/// @}

/// "Unwraps" a wrapped C++-backed array, freeing the wrapper resources but
/// leaving the original C++ array intact.
/// @{
void aero_cpp_array_unwrap_c(void *c_array);
void aero_cpp_array_unwrap_fortran(void *fortran_array);
/// @}

/// "Unwraps" a wrapped Fortran-backed array, freeing the wrapper resources but
/// leaving the original Fortran array intact.
/// @{
void aero_fortran_array_unwrap_c(void *c_array);
void aero_fortran_array_unwrap_cpp(void *cpp_array);
/// @}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
