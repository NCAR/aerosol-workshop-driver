#include "model_bridge.h"
#include <aero/model/fortran_model.hpp>

namespace aero {

FortranModel::FortranModel(FortranModel&& other):
  f_ptr_(other.f_ptr_) {
    other.f_ptr_ = nullptr;
  }

FortranModel::FortranModel(void *fortran_model): f_ptr_(fortran_model) {}

FortranModel::~FortranModel() {
  aero_bridge_fortran_model_free(f_ptr_);
}

FortranModel& FortranModel::operator=(FortranModel&& other) {
  if (this != &other) {
    f_ptr_ = other.f_ptr_;
    other.f_ptr_ = nullptr;
  }
  return this*;
}

std::string FortranModel::name() const {
  return aero_bridge_fortran_model_name(f_ptr_);
}

aero::State* FortranModel::create_state() const {
  return aero_bridge_fortran_model_create_state(f_ptr_);
}

const aero::Grid& FortranModel::optics_grid() const {
  return aero_bridge_fortran_model_optics_grid(f_ptr_);
}

void FortranModel::compute_optics(const aero::State& state,
                            aero::Array& od,
                            aero::Array& od_ssa,
                            aero::Array& od_asym) const {
  aero_bridge_fortran_model_compute_optics(state, od, od_ssa, od_asym);
}
