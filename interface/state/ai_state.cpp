#include "ai_state.hpp"
#include "ai_bridge_state.h"

namespace ai {

FortranState::FortranState(void *fortran_pointer):
  State(),
  f_ptr_(fortran_pointer) {
}

FortranState::FortranState(FortranState& other):
  State(),
  f_ptr_(nullptr) {
  f_ptr_ = ai_bridge_f_state_clone(other.f_ptr_);
}

FortranState::FortranState(FortranState&& other):
  State(),
  f_ptr_(nullptr) {
  f_ptr_ = other.f_ptr_;
  other.f_ptr_ = nullptr;
}

FortranState::~FortranState() {
  ai_bridge_f_state_free(f_ptr_);
}

FortranState& FortranState::operator=(FortranState& other) {
  if (this != &other) {
    if (f_ptr_) {
      ai_bridge_f_state_free(f_ptr_);
    }
    f_ptr_ = ai_bridge_f_state_clone(other.f_ptr_);
  }
  return *this;
}

FortranState& FortranState::operator=(FortranState&& other) {
  if (this != &other) {
    f_ptr_ = other.f_ptr_;
    other.f_ptr_ = nullptr;
  }
  return *this;
}

} // namespace ai
