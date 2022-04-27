// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#include <aero/model/model.h>
#include <aero/model/model.hpp>
#include "model_bridge.h"
#include <iostream>
#include <string.h>

#if __cplusplus
extern "C" {
#endif

const char* aero_bridge_c_model_name(void *model) {
  aero_model_t *c_model = reinterpret_cast<aero_model_t*>(model);
  return c_model->name(c_model);
}

const char* aero_bridge_cpp_model_name(void *model) {
  aero::Model *cpp_model = reinterpret_cast<aero::Model*>(model);
  return strdup(cpp_model->name().c_str());
}

void* aero_bridge_c_model_create_state(void *model) {
  aero_model_t *c_model = reinterpret_cast<aero_model_t*>(model);
  return reinterpret_cast<void*>(c_model->create_state(c_model));
}

void* aero_bridge_cpp_model_create_state(void *model) {
  aero::Model *cpp_model = reinterpret_cast<aero::Model*>(model);
  return reinterpret_cast<void*>(cpp_model->create_state());
}

void aero_bridge_c_model_free_state(void *model, void *state) {
  aero_model_t *c_model = reinterpret_cast<aero_model_t*>(model);
  aero_state_t *c_state = reinterpret_cast<aero_state_t*>(state);
  c_model->free_state(c_model, c_state);
}

void aero_bridge_cpp_model_free_state(void *model, void *state) {
  aero::Model *cpp_model = reinterpret_cast<aero::Model*>(model);
  aero::State *cpp_state = reinterpret_cast<aero::State*>(state);
  free(cpp_state);
}

void* aero_bridge_c_model_optics_grid(void *model) {
  aero_model_t *c_model = reinterpret_cast<aero_model_t*>(model);
  aero_grid_t *grid = c_model->optics_grid(c_model);
  const aero_array_t *grid_ifaces = aero_grid_interfaces(grid);
  aero_array_t *ifaces = grid_ifaces->clone(grid_ifaces);
  aero_grid_free(grid);
  return reinterpret_cast<void*>(ifaces);
}

void* aero_bridge_cpp_model_optics_grid(void *model) {
  aero::Model *cpp_model = reinterpret_cast<aero::Model*>(model);
  aero::Grid *grid = cpp_model->optics_grid();
  aero::Array *ifaces = grid->interfaces().clone();
  delete grid;
  return reinterpret_cast<void*>(ifaces);
}

void aero_bridge_c_model_compute_optics(void *model, void *state,
    void *od, void *od_ssa, void *od_asym) {
  aero_model_t *c_model   = reinterpret_cast<aero_model_t*>(model);
  aero_state_t *c_state   = reinterpret_cast<aero_state_t*>(state);
  aero_array_t *c_od      = reinterpret_cast<aero_array_t*>(od);
  aero_array_t *c_od_ssa  = reinterpret_cast<aero_array_t*>(od_ssa);
  aero_array_t *c_od_asym = reinterpret_cast<aero_array_t*>(od_asym);
  c_model->compute_optics(c_model, c_state, c_od, c_od_ssa, c_od_asym);
}

void aero_bridge_cpp_model_compute_optics(void *model, void *state,
    void *od, void *od_ssa, void *od_asym) {
  aero::Model* cpp_model   = reinterpret_cast<aero::Model*>(model);
  aero::State* cpp_state   = reinterpret_cast<aero::State*>(state);
  aero::Array* cpp_od      = reinterpret_cast<aero::Array*>(od);
  aero::Array* cpp_od_ssa  = reinterpret_cast<aero::Array*>(od_ssa);
  aero::Array* cpp_od_asym = reinterpret_cast<aero::Array*>(od_asym);
  cpp_model->compute_optics(*cpp_state, *cpp_od, *cpp_od_ssa, *cpp_od_asym);
}

void aero_bridge_c_model_free(void *model) {
  aero_model_t *c_model = reinterpret_cast<aero_model_t*>(model);
  c_model->free(c_model);
}

void aero_bridge_cpp_model_free(void *model) {
  aero::Model* cpp_model = reinterpret_cast<aero::Model*>(model);
  delete(cpp_model);
}

#if __cplusplus
} // extern "C"
#endif
