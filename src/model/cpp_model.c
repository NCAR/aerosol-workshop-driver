#include <aero/array/array.h>
#include <aero/array/cpp_array.h>
#include <aero/model/cpp_model.h>
#include "model_bridge.h"
#include "../state/state_bridge.h"
#include <stdlib.h>

struct aero_state_data_t {
  void *cpp_state_;
};

static void aero_cpp_state_free(aero_state_t *state) {
  aero_bridge_cpp_state_free(state->data_->cpp_state_);
  free(state->data_);
  free(state);
}

static aero_state_t* aero_cpp_state_create(aero_state_data_t *state_data) {
  aero_state_t *state = malloc(sizeof(aero_state_t));
  state->data_ = state_data;
  state->free = aero_cpp_state_free;
  return state;
}

static aero_state_t* aero_cpp_state_wrap(void *cpp_state) {
  aero_state_data_t *state_data = malloc(sizeof(aero_state_data_t));
  state_data->cpp_state_ = cpp_state;
  return aero_cpp_state_create(state_data);
}

struct aero_model_data_t {
  bool owns_model_;
  void* cpp_model_;
};

static aero_model_t* aero_cpp_model_create(aero_model_data_t *model_data);

static const char* aero_cpp_model_name(const aero_model_t *model) {
  AERO_ASSERT(false); // not implemented yet
  return aero_bridge_cpp_model_name(model->data_->cpp_model_);
}

static aero_state_t* aero_cpp_model_create_state(const aero_model_t *model) {
  return aero_cpp_state_wrap(aero_bridge_cpp_model_create_state(model->data_->cpp_model_));
}

static aero_grid_t* aero_cpp_model_optics_grid(const aero_model_t *model) {
  aero_array_t* ifaces =
    aero_new_cpp_array(aero_bridge_cpp_model_optics_grid(model->data_->cpp_model_), true);
  return aero_grid_from_interfaces(ifaces);
}

static void aero_cpp_model_compute_optics(const aero_model_t *model, aero_state_t *state,
    aero_array_t *od, aero_array_t *od_ssa, aero_array_t *od_asym) {
  // convert cpp_state and cpp_arrays to c types
  //aero_bridge_cpp_model_optics_grid(model->data_->cpp_model_, (void*) state,
  //    (void*) od, (void*) od_ssa, (void*) od_asym);
}
static void aero_cpp_model_free(aero_model_t *model) {
  if (model->data_->owns_model_)
    aero_bridge_cpp_model_free(model->data_->cpp_model_);
  free(model->data_);
  free(model);
}

static aero_model_t* aero_cpp_model_create(aero_model_data_t *model_data) {
  aero_model_t *model;
  model = malloc(sizeof(aero_model_t));
  model->data_ = model_data;
  model->name = aero_cpp_model_name;
  model->create_state = aero_cpp_model_create_state;
  model->optics_grid = aero_cpp_model_optics_grid;
  model->compute_optics = aero_cpp_model_compute_optics;
  model->free = aero_cpp_model_free;
  return model;
}

void* aero_cpp_model_wrap(void *cpp_model) {
  aero_model_data_t *model_data = malloc(sizeof(aero_model_data_t));
  model_data->cpp_model_ = cpp_model;
  model_data->owns_model_ = false;
  return (void*)aero_cpp_model_create(model_data);
}

void aero_cpp_model_unwrap(void *c_model) {
  aero_model_t *model = (aero_model_t*) c_model;
  model->free(model);
}

aero_model_t* aero_new_cpp_model(void *cpp_model, bool owns_model) {
  aero_model_t* model = (aero_model_t*) aero_cpp_model_wrap(cpp_model);
  model->data_->owns_model_ = owns_model;
  return model;
}
