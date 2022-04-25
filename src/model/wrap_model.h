#ifndef AERO_WRAP_MODEL_H
#define AERO_WRAP_MODEL_H

#include <aero/aero.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Creates an model by wrapping a C-backed model
/// @{
void* aero_c_model_wrap_cpp(void *c_model);
void* aero_c_model_wrap_fortran(void *c_model);
/// @}

/// Creates an model by wrapping a C++-backed model
/// @{
void* aero_cpp_model_wrap_c(void *cpp_model);
void* aero_cpp_model_wrap_fortran(void *cpp_model);
/// @}

/// Creates an model by wrapping a Fortran-backed model
/// @{
void* aero_fortran_model_wrap_c(void *fortran_model);
void* aero_fortran_model_wrap_cpp(void *fortran_model);
/// @}

/// "Unwraps" a wrapped C-backed model, freeing the wrapper resources but
/// leaving the original C model intact.
/// @{
void aero_c_model_unwrap_cpp(void *cpp_model);
void aero_c_model_unwrap_fortran(void *fortran_model);
/// @}

/// "Unwraps" a wrapped C++-backed model, freeing the wrapper resources but
/// leaving the original C++ model intact.
/// @{
void aero_cpp_model_unwrap_c(void *c_model);
void aero_cpp_model_unwrap_fortran(void *fortran_model);
/// @}

/// "Unwraps" a wrapped Fortran-backed model, freeing the wrapper resources but
/// leaving the original Fortran model intact.
/// @{
void aero_fortran_model_unwrap_c(void *c_model);
void aero_fortran_model_unwrap_cpp(void *cpp_model);
/// @}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
