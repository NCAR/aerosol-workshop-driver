#include "model_bridge.h"
#include <aero/model/c_model.hpp>

namespace aero {

CModel::CModel(void *c_model):
  c_ptr_(c_model),
  owns_model_(false) {}

CModel::CModel(void *c_model, bool owns_model):
  c_ptr_(c_model),
  owns_model_(owns_model) {}

CModel::~CModel() {
  if (owns_model_) aero_bridge_c_model_free(c_ptr_);
  c_ptr_ = nullptr;
}

std::string CModel::name() const {
  AERO_ASSERT(false); // not implemented yet
  return std::string(aero_bridge_c_model_name(c_ptr_));
}

aero::State* CModel::create_state() const {
  return nullptr; //reinterpret_cast<aero::State*>(aero_bridge_c_model_create_state(c_ptr_));
}

aero::Grid* CModel::optics_grid() const {
  return nullptr; //reinterpret_cast<aero::Grid*>(aero_bridge_c_model_optics_grid(c_ptr_));
}

void CModel::compute_optics(aero::State& state,
                            aero::Array& od,
                            aero::Array& od_ssa,
                            aero::Array& od_asym) const {
  //aero_bridge_c_model_compute_optics(state, od, od_ssa, od_asym);
}

}

#ifdef __cplusplus
extern "C" {
#endif

void* aero_c_model_wrap_cpp(void *c_model) {
  return reinterpret_cast<void*>(new aero::CModel(c_model));
}

void aero_c_model_unwrap_cpp(void *cpp_model) {
  delete(reinterpret_cast<aero::Model*>(cpp_model));
}

#ifdef __cplusplus
} // extern "C"
#endif
