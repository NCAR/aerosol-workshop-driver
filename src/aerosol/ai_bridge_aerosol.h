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
#ifndef AI_BRIDGE_AEROSOL_H
#define AI_BRIDGE_AEROSOL_H

#ifdef __cplusplus
extern "C" {
#endif

/// Returns a pointer to a newly created aerosol model implemented in C
/// with the given package name, initialized using the given description file.
void* ai_bridge_c_new_aerosol(const char *package_name,
                              const char *description_file);

/// Returns a pointer to a newly created aerosol model implemented in C++
/// with the given package name, initialized using the given description file.
void* ai_bridge_cpp_new_aerosol(const char *package_name,
                                const char *description_file);

/// Returns a pointer to a newly created aerosol model implemented in Fortran
/// with the given package name, initialized using the given description file.
void* ai_bridge_f_new_aerosol(const char *package_name,
                              const char *description_file);

/// Returns whether an aerosol model is available in C with the given
/// package name.
bool ai_bridge_c_supports_aerosol(const char *package_name);

/// Returns whether an aerosol model is available in C++ with the given
/// package name.
bool ai_bridge_cpp_supports_aerosol(const char *package_name);

/// Returns whether an aerosol model is available in Fortran with the given
/// package name.
bool ai_bridge_f_supports_aerosol(const char *package_name);

/// Frees resources associated with the given C aerosol model.
void ai_bridge_c_aerosol_free(void *aerosol);

/// Frees resources associated with the given C++ aerosol model.
void ai_bridge_cpp_aerosol_free(void *aerosol);

/// Frees resources associated with the given Fortran aerosol model.
void ai_bridge_f_aerosol_free(void *aerosol);

#ifdef __cplusplus
}
#endif

#endif
