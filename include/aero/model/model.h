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

#ifndef AERO_MODEL_H
#define AERO_MODEL_H

#include <aero/array/array.h>
#include <aero/grid/grid.h>
#include <aero/state/state.h>

#ifdef __cplusplus
extern "C" {
#endif

/// This opaque type represents an aerosol model implemented in C. The type
/// has a name, data, and associated behaviors.
typedef struct aero_model_t aero_model_t;

/// Here are behaviors implemented by a C-backed aerosol model. All of these
/// functions are passed the data pointer supplied to aero_model_new.
typedef struct aero_model_behaviors {
  /// returns the name of the aerosol model
  const char* (*name)(void *aerosol);
  /// returns a newly created aerosol state
  aero_state_t* (*create_state)(void *aerosol);
  /// returns the grid on which the aerosol's optical properties are computed
  aero_grid_t* (*optics_grid)(void *aerosol);
  /// computes optical properties given the model, an aerosol state, and
  /// destination arrays
  void (*compute_optics)(void *aerosol, aero_state_t *state,
                         aero_array_t *od, aero_array_t *od_ssa,
                         aero_array_t *od_asym);
} aero_model_behaviors;

/// Creates and returns an aerosol model implemented in C with the given data
/// (context) pointer and set of behaviors.
aero_model_t* aero_model_new(void *data, aero_model_behaviors behaviors);

/// Returns the name of the aerosol package that provides this model.
const char* aero_model_name(aero_model_t *model);

/// Returns the optics grid on which this model computes optical properties.
aero_grid_t* aero_model_optics_grid(aero_model_t *model);

/// Computes optical properties given an aerosol state and destination arrays.
void aero_model_compute_optics(aero_model_t *model,
                               aero_state_t *state,
                               aero_array_t *od,
                               aero_array_t *od_ssa,
                               aero_array_t *od_asym);

#ifdef __cplusplus
}
#endif

#endif
