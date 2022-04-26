//===-- template/cpp/my_aerosol.cpp -----------------------------*- C++ -*-===//
//
// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//
///
/// \file My aerosol functions
///
//===----------------------------------------------------------------------===//

#include "my_model.h"

#include <aero/grid/grid.h>
#include <aero/state/state.h>

#include <stdlib.h>
#include <string.h>

// Store your data here. It's available via the context pointer argument to
// methods.
struct aero_model_data_t {
  aero_grid_t *grid_;   // radiation wave number ("wavelength") grid [m-1]
};

// Aerosol state data for this model is defined here.
struct aero_state_t {
  aero_real_t *od_;      // aerosol optical depth [m]
  aero_real_t *od_ssa_;  // aerosol single scattering albedo [-]
  aero_real_t *od_asym_; // aerosol asymmetric scattering optical depth [m]
  aero_real_t *od_work_; // working array for computing optics
};

static aero_model_t* my_model_create(aero_model_data_t *model_data);

// Returns the name of this aerosol model.
static const char* my_model_name(const aero_model_t *model) {
  return "My C Model";
}

// Returns a newly created aerosol state related to this model.
static aero_state_t* my_model_create_state(const aero_model_t *model) {
  aero_state_t *state = malloc(sizeof(aero_state_t));

  // We initialize C arrays with data pulled from
  // https://acp.copernicus.org/articles/18/7815/2018/acp-18-7815-2018-f03.pdf
  // For this state, we use the "mixed type" measures, indicated by triangles.
  // Note the units in the fields of the aero_state_t struct at the top of
  // this file. The data here corresponds to the grid interfaces shown in the
  // figure.
  //
  // The data arrays are ordered so they correspond to the following
  // wavelengths, expressed in descending order:
  // {1020.0, 870.0, 675.0, 440.0} [nm]
  // This corresponds to a grid with interfaces expressed in ascending
  // wave numbers [m-1].
  aero_real_t od_data[]      = {0.27, 0.35, 0.5, 0.75};       // top left
  aero_real_t od_ssa_data[]  = {0.88, 0.895, 0.905, 0.88};    // middle left
  aero_real_t od_asym_data[] = {0.3, 0.035, 0.045, 0.09};     // top right
  state->od_      = malloc(sizeof(aero_real_t) * 4);
  state->od_ssa_  = malloc(sizeof(aero_real_t) * 4);
  state->od_asym_ = malloc(sizeof(aero_real_t) * 4);
  state->od_work_ = malloc(sizeof(aero_real_t) * 4);
  memcpy(state->od_, od_data, sizeof(aero_real_t) * 4);
  memcpy(state->od_ssa_, od_ssa_data, sizeof(aero_real_t) * 4);
  memcpy(state->od_asym_, od_asym_data, sizeof(aero_real_t) * 4);
  return state;
}

/// Frees resources of a state object
static void my_model_free_state(const aero_model_t *model, aero_state_t *state) {
  free(state->od_);
  free(state->od_ssa_);
  free(state->od_asym_);
  free(state->od_work_);
  free(state);
}

// Returns the grid associated with this model
static aero_grid_t* my_model_optics_grid(const aero_model_t *model) {
  return model->data_->grid_;
}

static void my_model_compute_optics(const aero_model_t *model,
                                    aero_state_t *state,
                                    aero_array_t *od,
                                    aero_array_t *od_ssa,
                                    aero_array_t *od_asym) {
  // We simply copy the state's optics data into place.
  for (int i=0; i<4; ++i) state->od_work_[i] = state->od_[i];
  od->copy_in(od, state->od_work_);
  for (int i=0; i<4; ++i) state->od_work_[i] *= state->od_ssa_[i];
  od_ssa->copy_in(od_ssa, state->od_work_);
  for (int i=0; i<4; ++i) state->od_work_[i] *= state->od_asym_[i];
  od_asym->copy_in(od_asym, state->od_work_);
}

static void my_model_free(aero_model_t *model) {
  aero_grid_free(model->data_->grid_);
  free(model->data_);
  free(model);
}

static aero_model_t* my_model_create(aero_model_data_t *model_data) {
  aero_model_t *model;
  model = malloc(sizeof(aero_model_t));
  model->data_ = model_data;
  model->name = my_model_name;
  model->create_state = my_model_create_state;
  model->free_state = my_model_free_state;
  model->optics_grid = my_model_optics_grid;
  model->compute_optics = my_model_compute_optics;
  model->free = my_model_free;
  return model;
}

aero_model_t* my_model_new(const char *description_file) {

  // Define the model's data based on the contents of the description file.
  aero_model_data_t *data = malloc(sizeof(aero_model_data_t));

  // Initialize the aerosol grid with wavelength data pulled from
  // https://acp.copernicus.org/articles/18/7815/2018/acp-18-7815-2018-f03.pdf
  // We specify wavelengths in descending order so their wave numbers appear in
  // ascending order in the grid interfaces array.
  aero_real_t wavelengths[] = {1020.0, 870.0, 675.0, 440.0}; // [nm]

  // Convert to wave numbers for the grid's interfaces.
  aero_real_t wave_numbers[4];
  for (size_t i = 0; i < 4; ++i) {
    wave_numbers[i] = 1e-9 / wavelengths[i]; // [m-1]
  }

  aero_array_t *interfaces = aero_array_from_array(4, wave_numbers);
  data->grid_ = aero_grid_from_interfaces(interfaces);

  return my_model_create(data);
}

