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

/// Returns the name of an aerosol model
/// @{
const char* aero_bridge_c_model_name(void *model);
const char* aero_bridge_cpp_model_name(void *model);
void* aero_bridge_fortran_model_name(void *model);
/// @}

/// Creates a new state for use with a given aerosol model.
/// @{
void* aero_bridge_c_model_create_state(void *model);
void* aero_bridge_cpp_model_create_state(void *model);
void* aero_bridge_fortran_model_create_state(void *model);
/// @}

/// Returns a copy of the optics grid interfaces used by the aerosol model.
/// @{
void* aero_bridge_c_model_optics_grid(void *model);
void* aero_bridge_cpp_model_optics_grid(void *model);
void* aero_bridge_fortran_model_optics_grid(void *model);
/// @}

/// Computes aerosol optical properties for a given state
/// @{
void aero_bridge_c_model_compute_optics(void *model, void *state, void *od,
    void *od_ssa, void* od_asym);
void aero_bridge_cpp_model_compute_optics(void *model, void *state, void *od,
    void *od_ssa, void* od_asym);
void aero_bridge_fortran_model_compute_optics(void *model, void *state, void *od,
    void *od_ssa, void* od_asym);
/// @}

/// Frees resources associated with the given aerosol model.
/// @{
void aero_bridge_c_model_free(void *aerosol);
void aero_bridge_cpp_model_free(void *aerosol);
void aero_bridge_fortran_model_free(void *aerosol);
/// @}

#ifdef __cplusplus
}
#endif

#endif
