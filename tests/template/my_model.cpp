// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#include <aero/aero.hpp>
#include <aero/array/array.hpp>
#include <aero/grid/grid.hpp>
#include <aero/model/model.hpp>
#include <aero/model/c_model.hpp>
#include <aero/model/fortran_model.hpp>
#include <my_model.hpp>
#include <iostream>
#include <cstring>
#include "my_model_helper.h"

extern "C" {
  void *test_my_model_create_fortran_model();
}
void test_my_model() {

  // C++ model
  aero::Model *model = new MyModel("");
  aero::State *state = model->create_state();
  const aero::Grid *model_grid = model->optics_grid();
  aero::Array *od, *od_ssa, *od_asym;
  int size;

  AERO_ASSERT(model->name() == "my model");
  size = model_grid->interfaces().size();
  AERO_ASSERT(size == 4);
  od      = new aero::Array(size, 0.0);
  od_ssa  = new aero::Array(size, 0.0);
  od_asym = new aero::Array(size, 0.0);
  std::vector<aero::Real> od_v(     size, 0.0);
  std::vector<aero::Real> od_ssa_v( size, 0.0);
  std::vector<aero::Real> od_asym_v(size, 0.0);

  model->compute_optics(*state, *od, *od_ssa, *od_asym);
  od->copy_out(od_v);
  od_ssa->copy_out(od_ssa_v);
  od_asym->copy_out(od_asym_v);

  AERO_ASSERT(aero::almost_equal(od_v[1], 0.35));
  AERO_ASSERT(aero::almost_equal(od_ssa_v[3], 0.75 * 0.88));
  AERO_ASSERT(aero::almost_equal(od_asym_v[0], 0.27 * 0.88 * 0.3));

  delete(od);
  delete(od_ssa);
  delete(od_asym);
  delete(model_grid);
  delete(state);
  delete(model);

  // C model
  model = new aero::CModel(test_my_model_create_c_model(), true);
  state = model->create_state();
  model_grid = model->optics_grid();

  // AERO_ASSERT(model->name() == "my model");
  size = model_grid->interfaces().size();
  AERO_ASSERT(size == 4);
  od      = new aero::Array(size, 0.0);
  od_ssa  = new aero::Array(size, 0.0);
  od_asym = new aero::Array(size, 0.0);
  od_v      = std::vector<aero::Real>(size, 0.0);
  od_ssa_v  = std::vector<aero::Real>(size, 0.0);
  od_asym_v = std::vector<aero::Real>(size, 0.0);

  model->compute_optics(*state, *od, *od_ssa, *od_asym);
  od->copy_out(od_v);
  od_ssa->copy_out(od_ssa_v);
  od_asym->copy_out(od_asym_v);

  AERO_ASSERT(aero::almost_equal(od_v[1], 0.35));
  AERO_ASSERT(aero::almost_equal(od_ssa_v[3], 0.75 * 0.88));
  AERO_ASSERT(aero::almost_equal(od_asym_v[0], 0.27 * 0.88 * 0.3));

  delete(od);
  delete(od_ssa);
  delete(od_asym);
  delete(model_grid);
  delete(state);
  delete(model);

  // Fortran model
  model = new aero::FortranModel(test_my_model_create_fortran_model(), true);
  state = model->create_state();
  model_grid = model->optics_grid();

  // AERO_ASSERT(model->name() == "my model");
  size = model_grid->interfaces().size();
  AERO_ASSERT(size == 4);
  od      = new aero::Array(size, 0.0);
  od_ssa  = new aero::Array(size, 0.0);
  od_asym = new aero::Array(size, 0.0);
  od_v      = std::vector<aero::Real>(size, 0.0);
  od_ssa_v  = std::vector<aero::Real>(size, 0.0);
  od_asym_v = std::vector<aero::Real>(size, 0.0);

  model->compute_optics(*state, *od, *od_ssa, *od_asym);
  od->copy_out(od_v);
  od_ssa->copy_out(od_ssa_v);
  od_asym->copy_out(od_asym_v);

  AERO_ASSERT(aero::almost_equal(od_v[1], 0.92 * 0.35));
  AERO_ASSERT(aero::almost_equal(od_ssa_v[3], 0.92 * 0.75 * 0.88));
  AERO_ASSERT(aero::almost_equal(od_asym_v[0], 0.92 * 0.27 * 0.88 * 0.3));

  delete(od);
  delete(od_ssa);
  delete(od_asym);
  delete(model_grid);
  delete(state);
  delete(model);

}

int main(int argc, char *argv[]) {
  test_my_model();
  return 0;
}
