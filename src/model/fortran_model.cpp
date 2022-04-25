#include "model_bridge.h"
#include <aero/model/fortran_model.hpp>

namespace aero {

FortranModel::FortranModel(void *fortran_model):
  f_ptr_(fortran_model),
  owns_model_(false) {}

FortranModel::FortranModel(void *fortran_model, bool owns_model):
  f_ptr_(fortran_model),
  owns_model_(owns_model) {}

FortranModel::~FortranModel() {
  if (owns_model_) aero_bridge_fortran_model_free(f_ptr_);
  f_ptr_ = nullptr;
}

std::string FortranModel::name() const {
  return nullptr; //aero_bridge_fortran_model_name(f_ptr_);
}

aero::State* FortranModel::create_state() const {
  return nullptr; //aero_bridge_fortran_model_create_state(f_ptr_);
}

aero::Grid* FortranModel::optics_grid() const {
  return nullptr; //aero_bridge_fortran_model_optics_grid(f_ptr_);
}

void FortranModel::compute_optics(const aero::State& state,
                            aero::Array& od,
                            aero::Array& od_ssa,
                            aero::Array& od_asym) const {
  //aero_bridge_fortran_model_compute_optics(state, od, od_ssa, od_asym);
}

}

#ifdef __cplusplus
extern "C" {
#endif

void* aero_fortran_model_wrap_cpp(void *fortran_model) {
  return reinterpret_cast<void*>(new aero::FortranModel(fortran_model));
}

void aero_fortran_model_unwrap_cpp(void *fortran_model) {
  delete(reinterpret_cast<aero::Model*>(fortran_model));
}

#ifdef __cplusplus
} // extern "C"
#endif
