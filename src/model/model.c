/*===-- src/model/aero_model.c --------------------------*- C -*-===//
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
#include <aero/model/model.h>

#include <stdlib.h>

struct aero_model_t {
  void                 *context;
  aero_model_behaviors  behaviors;
};

aero_model_t* aero_model_new(void *data, aero_model_behaviors behaviors) {
  aero_model_t *model = malloc(sizeof(aero_model_t));
  model->context = data;
  model->behaviors = behaviors;
  return model;
}

const char* aero_model_name(aero_model_t *model) {
  return model->behaviors.name(model->context);
}

aero_grid_t* aero_model_optics_grid(aero_model_t *model) {
  return model->behaviors.optics_grid(model->context);
}

void aero_model_compute_optics(aero_model_t *model,
                               aero_state_t *state,
                               aero_array_t *od,
                               aero_array_t *od_ssa,
                               aero_array_t *od_asym) {
  return model->behaviors.compute_optics(model->context, state,
                                         od, od_ssa, od_asym);
}
