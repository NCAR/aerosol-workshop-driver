/* Copyright (C) 2022 National Center for Atmospheric Research,
 * National Technology & Engineering Solutions of Sandia, LLC (NTESS),
 * and the U.S. Environmental Protection Agency (USEPA)
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <aero/aero.h>
#include <aero/array/array.h>
#include <aero/grid/grid.h>
#include <aero/model/model.h>
#include <aero/model/cpp_model.h>
#include <aero/model/fortran_model.h>
#include <my_model.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_model_helper.h"

void* test_my_model_create_fortran_model();

void test_my_model_t() {

  // c model
  aero_model_t *model = my_model_new("");
  aero_state_t *state = model->create_state(model);
  aero_grid_t *model_grid = model->optics_grid(model);
  const aero_array_t *interfaces = aero_grid_interfaces(model_grid);
  aero_array_t *od, *od_ssa, *od_asym;
  aero_real_t *od_a, *od_ssa_a, *od_asym_a;
  int size;

  AERO_ASSERT(strcmp(model->name(model), "my model") == 0);
  size = interfaces->size(interfaces);
  AERO_ASSERT(size == 4);
  od      = aero_array_from_dimensions(size, 0.0);
  od_ssa  = aero_array_from_dimensions(size, 0.0);
  od_asym = aero_array_from_dimensions(size, 0.0);
  od_a      = (aero_real_t*) malloc(size*sizeof(aero_real_t));
  od_ssa_a  = (aero_real_t*) malloc(size*sizeof(aero_real_t));
  od_asym_a = (aero_real_t*) malloc(size*sizeof(aero_real_t));

  model->compute_optics(model, state, od, od_ssa, od_asym);
  od->copy_out(od, od_a);
  od_ssa->copy_out(od_ssa, od_ssa_a);
  od->copy_out(od_asym, od_asym_a);

  AERO_ASSERT(almost_equal(od_a[1], 0.35));
  AERO_ASSERT(almost_equal(od_ssa_a[3], 0.75 * 0.88));
  AERO_ASSERT(almost_equal(od_asym_a[0], 0.27 * 0.88 * 0.3));

  od->free(od);
  od_ssa->free(od_ssa);
  od_asym->free(od_asym);
  aero_grid_free(model_grid);
  state->free(state);
  model->free(model);
  free(od_a);
  free(od_ssa_a);
  free(od_asym_a);

  // c++ model
  model = aero_new_cpp_model(test_my_model_create_cpp_model(), true);
  state = model->create_state(model);
  model_grid = model->optics_grid(model);
  interfaces = aero_grid_interfaces(model_grid);

  // AERO_ASSERT(strcmp(model->name(model), "my model") == 0);
  size = interfaces->size(interfaces);
  AERO_ASSERT(size == 4);
  od      = aero_array_from_dimensions(size, 0.0);
  od_ssa  = aero_array_from_dimensions(size, 0.0);
  od_asym = aero_array_from_dimensions(size, 0.0);
  od_a      = (aero_real_t*) malloc(size*sizeof(aero_real_t));
  od_ssa_a  = (aero_real_t*) malloc(size*sizeof(aero_real_t));
  od_asym_a = (aero_real_t*) malloc(size*sizeof(aero_real_t));

  model->compute_optics(model, state, od, od_ssa, od_asym);
  od->copy_out(od, od_a);
  od_ssa->copy_out(od_ssa, od_ssa_a);
  od->copy_out(od_asym, od_asym_a);

  AERO_ASSERT(almost_equal(od_a[1], 0.35));
  AERO_ASSERT(almost_equal(od_ssa_a[3], 0.75 * 0.88));
  AERO_ASSERT(almost_equal(od_asym_a[0], 0.27 * 0.88 * 0.3));

  od->free(od);
  od_ssa->free(od_ssa);
  od_asym->free(od_asym);
  aero_grid_free(model_grid);
  state->free(state);
  model->free(model);
  free(od_a);
  free(od_ssa_a);
  free(od_asym_a);

  // fortran model
  model = aero_new_fortran_model(test_my_model_create_fortran_model(), true);
  state = model->create_state(model);
  model_grid = model->optics_grid(model);
  interfaces = aero_grid_interfaces(model_grid);

  // AERO_ASSERT(strcmp(model->name(model), "my model") == 0);
  size = interfaces->size(interfaces);
  AERO_ASSERT(size == 4);
  od      = aero_array_from_dimensions(size, 0.0);
  od_ssa  = aero_array_from_dimensions(size, 0.0);
  od_asym = aero_array_from_dimensions(size, 0.0);
  od_a      = (aero_real_t*) malloc(size*sizeof(aero_real_t));
  od_ssa_a  = (aero_real_t*) malloc(size*sizeof(aero_real_t));
  od_asym_a = (aero_real_t*) malloc(size*sizeof(aero_real_t));

  model->compute_optics(model, state, od, od_ssa, od_asym);
  od->copy_out(od, od_a);
  od_ssa->copy_out(od_ssa, od_ssa_a);
  od->copy_out(od_asym, od_asym_a);

  AERO_ASSERT(almost_equal(od_a[1], 0.92 * 0.35));
  AERO_ASSERT(almost_equal(od_ssa_a[3], 0.92 * 0.75 * 0.88));
  AERO_ASSERT(almost_equal(od_asym_a[0], 0.92 * 0.27 * 0.88 * 0.3));

  od->free(od);
  od_ssa->free(od_ssa);
  od_asym->free(od_asym);
  aero_grid_free(model_grid);
  state->free(state);
  model->free(model);
  free(od_a);
  free(od_ssa_a);
  free(od_asym_a);

}

int main(int argc, char *argv[]) {
  test_my_model_t();
  return 0;
}
