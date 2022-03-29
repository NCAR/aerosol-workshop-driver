/*===-- interface/aerosol/ai_aerosol.h ----------------------------*- C -*-===//
 *
 * Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 *
 *===----------------------------------------------------------------------===//
 *
 * Aerosol base class functions
 *
 *===----------------------------------------------------------------------===//
 */

#ifndef AI_AEROSOL_H
#define AI_AEROSOL_H

#include "array/ai_array.h"
#include "grid/ai_grid.h"
#include "state/ai_state.h"

#ifdef __cplusplus
extern "C" {
#endif

/// This opaque type represents an aerosol model implemented in C. The type
/// has a name, data, and associated behaviors.
typedef struct ai_aerosol_t ai_aerosol_t;

/// Here are behaviors implemented by a C-backed aerosol model. All of these
/// functions are passed the data pointer supplied to ai_aerosol_new.
typedef struct ai_aerosol_behaviors {
  /// returns the name of the aerosol model
  const char* (*name)(void *aerosol);
  /// returns a newly created aerosol state
  ai_state_t* (*create_state)(void *aerosol);
  /// returns the grid on which the aerosol's optical properties are computed
  ai_grid_t* (*optics_grid)(void *aerosol);
  /// computes optical properties given the model, an aerosol state, and
  /// destination arrays
  void (*compute_optics)(void *aerosol, ai_state_t *state,
                         ai_array_t *od, ai_array_t *od_ssa, ai_array_t *od_asym);
} ai_aerosol_behaviors;

/// Creates and returns an aerosol model implemented in C with the given data
/// (context) pointer and set of behaviors.
ai_aerosol_t* ai_aerosol_new(void *data, ai_aerosol_behaviors behaviors);

/// Returns the name of the aerosol package that provides this model.
const char* ai_aerosol_name(ai_aerosol_t *aerosol);

/// Returns the optics grid on which this model computes optical properties.
ai_grid_t* ai_aerosol_optics_grid(ai_aerosol_t *aerosol);

/// Computes optical properties given an aerosol state and destination arrays.
void ai_aerosol_compute_optics(ai_aerosol_t *aerosol,
                               ai_state_t *state,
                               ai_array_t *od,
                               ai_array_t *od_ssa,
                               ai_array_t *od_asym);

#ifdef __cplusplus
}
#endif

#endif
