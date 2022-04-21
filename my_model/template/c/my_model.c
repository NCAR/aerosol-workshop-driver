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
typedef struct my_model_data_t {
  aero_grid_t *grid_;   // radiation wave number ("wavelength") grid [m-1]
} my_model_data_t;

// Aerosol state data for this model is defined here.
struct aero_state_t {
  aero_real_t *od_;      // aerosol optical depth [m]
  aero_real_t *od_ssa_;  // aerosol single scattering albedo [-]
  aero_real_t *od_asym_; // aerosol asymmetric scattering optical depth [m]
};

// Returns the name of this aerosol model.
static const char* my_name(void *context) {
  return "My Model";
}

// Returns a newly created aerosol state related to this model.
static aero_state_t* my_create_state(void *context) {
  aero_state_t *state = malloc(sizeof(aero_state_t));

  // We initialize C arrays with data pulled from
  // https://acp.copernicus.org/articles/18/7815/2018/acp-18-7815-2018-f03.pdf
  // For this state, we use the "mixed type" measures, indicated by triangles.
  // Note the units in the fields of the aero_state_t struct at the top of
  // this file. The data here corresponds to the grid interfaces shown in the
  // figure.
  aero_real_t od_data[]      = {0.75, 0.5, 0.35, 0.27};       // top left
  aero_real_t od_ssa_data[]  = {0.88, 0.905, 0.895, 0.88};    // middle left
  aero_real_t od_asym_data[] = {0.09, 0.045, 0.035, 0.3};     // top right
  state->od_      = malloc(sizeof(aero_real_t) * 4);
  state->od_ssa_  = malloc(sizeof(aero_real_t) * 4);
  state->od_asym_ = malloc(sizeof(aero_real_t) * 4);
  memcpy(state->od_, od_data, sizeof(aero_real_t) * 4);
  memcpy(state->od_ssa_, od_ssa_data, sizeof(aero_real_t) * 4);
  memcpy(state->od_asym_, od_asym_data, sizeof(aero_real_t) * 4);
  return state;
}

// Returns the grid associated with this model
static aero_grid_t* my_optics_grid(void *context) {
  // extract grid from data stashed in context.
  my_model_data_t *data = context;
  return data->grid_;
}

static void my_compute_optics(void *context,
                              aero_state_t *state,
                              aero_array_t *od,
                              aero_array_t *od_ssa,
                              aero_array_t *od_asym) {
  // We simply copy the state's optics data into place.
  od->copy_in(od, state->od_);
  od_ssa->copy_in(od_ssa, state->od_ssa_);
  od_asym->copy_in(od_asym, state->od_asym_);
}

static void my_free(void *context) {
  my_model_data_t *data = context;
  aero_grid_free(data->grid_);
}

aero_model_t* my_model_new(const char *description_file) {

  aero_model_behaviors behaviors = {
    .name = my_name,
    .create_state = my_create_state,
    .optics_grid = my_optics_grid,
    .compute_optics = my_compute_optics,
    .free = my_free
  };

  // Define the model's data based on the contents of the description file.
  my_model_data_t *data = malloc(sizeof(my_model_data_t));

  // Initialize the aerosol grid with wavelength data pulled from
  // https://acp.copernicus.org/articles/18/7815/2018/acp-18-7815-2018-f03.pdf
  aero_real_t wavelengths[] = {440.0, 675.0, 870.0, 1020.0}; // [nm]

  // Convert to wave numbers for the grid's interfaces.
  aero_real_t wave_numbers[4];
  for (size_t i = 0; i < 4; ++i) {
    wave_numbers[i] = 1e-9 / wavelengths[i]; // [m-1]
  }
  aero_array_t *interfaces = aero_array_from_array(4, wave_numbers);
  data->grid_ = aero_grid_from_interfaces(interfaces);

  return aero_model_new(data, behaviors);
}

