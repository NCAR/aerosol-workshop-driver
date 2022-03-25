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

#include "my_aerosol.h"

// Store your data here. It's available via the context pointer argument to
// methods.
typedef struct my_model_data_t {
  int parameter;
} my_model_data_t;

static ai_grid_t* my_optics_grid(void *context) {
  // extract grid from data stashed in context.
}

static void my_compute_optics(void *context,
                              ai_state_t *state,
                              ai_array_t *od,
                              ai_array_t *od_ssa,
                              ai_array_t *od_asym) {
  // calculate here optics using data stashed in context.
}

ai_aerosol_t* my_aerosol_new(const char *description_file) {

  ai_aerosol_behaviors behaviors = {
    .optics_grid = my_optics_grid,
    .compute_optics = my_compute_optics
  };

  // Define the model's data based on the contents of the description file.
  my_model_data_t *data = malloc(sizeof(my_model_data_t));
  data->parameter = 42; // the Answer to It All
  return ai_aerosol_new("my package name", data, behaviors);
}

