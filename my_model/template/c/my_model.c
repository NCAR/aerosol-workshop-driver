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

#include <stdlib.h>
#include "my_model.h"

// Store your data here. It's available via the context pointer argument to
// methods.
typedef struct my_model_data_t {
  int parameter;
} my_model_data_t;

static aero_grid_t* my_optics_grid(void *context) {
  // extract grid from data stashed in context.
}

static void my_compute_optics(void *context,
                              aero_state_t *state,
                              aero_array_t *od,
                              aero_array_t *od_ssa,
                              aero_array_t *od_asym) {
  // calculate here optics using data stashed in context.
}

aero_model_t* my_model_new(const char *description_file) {

  aero_model_behaviors behaviors = {
    .optics_grid = my_optics_grid,
    .compute_optics = my_compute_optics
  };

  // Define the model's data based on the contents of the description file.
  my_model_data_t *data = malloc(sizeof(my_model_data_t));
  data->parameter = 42; // the Answer to It All
  return aero_model_new(data, behaviors);
}

