/* Copyright (C) 2022 National Center for Atmospheric Research,
 * National Technology & Engineering Solutions of Sandia, LLC (NTESS),
 * and the U.S. Environmental Protection Agency (USEPA)
 *
 * SPDX-License-Identifier: Apache-2.0
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
typedef struct aero_model_data_t aero_model_data_t;

/// Here are behaviors implemented by a C-backed aerosol model. All of these
/// functions are passed the data pointer supplied to aero_model_new.
typedef struct aero_model_t aero_model_t;
typedef struct aero_model_t {
  /// Data members of the aero_model_t class
  aero_model_data_t *data_;
  /// returns the name of the aerosol model
  const char* (*name)(const aero_model_t *model);
  /// returns a newly created aerosol state
  aero_state_t* (*create_state)(const aero_model_t *model);
  /// frees a state created by create_state
  void (*free_state)(const aero_model_t *model, aero_state_t *state);
  /// returns the grid on which the aerosol's optical properties are computed
  aero_grid_t* (*optics_grid)(const aero_model_t *model);
  /// computes optical properties given the model, an aerosol state, and
  /// destination arrays
  void (*compute_optics)(const aero_model_t* model, aero_state_t *state,
                         aero_array_t *od, aero_array_t *od_ssa,
                         aero_array_t *od_asym);
  /// Destroys the model's contextual data, freeing any associated resources.
  void (*free)(aero_model_t* model);
} aero_model_t;

#ifdef __cplusplus
} // extern "C"
#endif

#endif
