/*===-- interface/aerosol/ai_bridge_aerosol.h ---------------------*- C -*-===//
 *
 * Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 *
 *===----------------------------------------------------------------------===//
 *
 * C/C++ <--> Fortran bridge functions for the Aerosol class
 *
 *===----------------------------------------------------------------------===//
 */
#ifndef AERO_MODEL_BRIDGE_H
#define AERO_MODEL_BRIDGE_H

#ifdef __cplusplus
extern "C" {
#endif

/// Returns a pointer to a newly created aerosol model implemented in C
/// with the given package name, initialized using the given description file.
void* aero_bridge_c_new_model(const char *package_name,
                              const char *description_file);

/// Returns a pointer to a newly created aerosol model implemented in C++
/// with the given package name, initialized using the given description file.
void* aero_bridge_cpp_new_model(const char *package_name,
                                const char *description_file);

/// Returns a pointer to a newly created aerosol model implemented in Fortran
/// with the given package name, initialized using the given description file.
void* aero_bridge_f_new_model(const char *package_name,
                              const char *description_file);

/// Returns whether an aerosol model is available in C with the given
/// package name.
bool aero_bridge_c_supports_model(const char *package_name);

/// Returns whether an aerosol model is available in C++ with the given
/// package name.
bool aero_bridge_cpp_supports_model(const char *package_name);

/// Returns whether an aerosol model is available in Fortran with the given
/// package name.
bool aero_bridge_fortran_supports_model(const char *package_name);

/// Frees resources associated with the given C aerosol model.
void aero_bridge_c_model_free(void *aerosol);

/// Frees resources associated with the given C++ aerosol model.
void aero_bridge_cpp_model_free(void *aerosol);

/// Frees resources associated with the given Fortran aerosol model.
void aero_bridge_fortran_model_free(void *aerosol);

#ifdef __cplusplus
}
#endif

#endif
