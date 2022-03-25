/*===-- interface/aerosol.c -------------------------------------*- C++ -*-===//
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
#include "ai_aerosol.h"

#include <stdlib.h>

struct ai_aerosol_t {
  void                 *context;
  ai_aerosol_behaviors  behaviors;
};

ai_aerosol_t* ai_aerosol_new(void *data, ai_aerosol_behaviors behaviors) {
  ai_aerosol_t *aerosol = malloc(sizeof(ai_aerosol_t));
  aerosol->context = data;
  aerosol->behaviors = behaviors;
  return aerosol;
}

const char* ai_aerosol_name(ai_aerosol_t *aerosol) {
  return aerosol->behaviors.name(aerosol->context);
}

ai_grid_t* ai_aerosol_optics_grid(ai_aerosol_t *aerosol) {
  return aerosol->behaviors.optics_grid(aerosol->context);
}

void ai_aerosol_compute_optics(ai_aerosol_t *aerosol,
                               ai_state_t *state,
                               ai_array_t *od,
                               ai_array_t *od_ssa,
                               ai_array_t *od_asym) {
  return aerosol->behaviors.compute_optics(aerosol->context, state,
                                           od, od_ssa, od_asym);
}
