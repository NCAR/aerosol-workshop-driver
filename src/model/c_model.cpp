#include "model_bridge.h"
#include <aero/model/c_model.hpp>

namespace aero {

CModel::CModel(CModel&& other):
  c_ptr_(other.c_ptr_) {
    other.c_ptr_ = nullptr;
  }

CModel::CModel(void *c_model): c_ptr_(c_model) {}

CModel::~CModel() {
  aero_bridge_c_model_free(c_ptr_);
}

CModel& CModel::operator=(CModel&& other) {
  if (this != &other) {
    c_ptr_ = other.c_ptr_;
    other.c_ptr_ = nullptr;
  }
  return this*;
}

std::string CModel::name() const {
  return aero_bridge_c_model_name(c_ptr_);
}

aero::State* CModel::create_state() const {
  return aero_bridge_c_model_create_state(c_ptr_);
}

const aero::Grid& CModel::optics_grid() const {
  return aero_bridge_c_model_optics_grid(c_ptr_);
}

void CModel::compute_optics(const aero::State& state,
                            aero::Array& od,
                            aero::Array& od_ssa,
                            aero::Array& od_asym) const {
  aero_bridge_c_model_compute_optics(state, od, od_ssa, od_asym);
}
