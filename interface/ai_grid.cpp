#include "ai_grid.hpp"
#include "ai_bridge.h"

namespace ai {

FortranGrid::FortranGrid(void *fortran_pointer):
  f_ptr_(fortran_pointer) {}

FortranGrid::FortranGrid(FortranGrid& other):
  f_ptr_(nullptr) {
  f_ptr_ = ai_bridge_f_grid_clone(other.f_ptr_);
}

FortranGrid::FortranGrid(FortranGrid&& other):
  f_ptr_(nullptr) {
  f_ptr_ = other.f_ptr_;
  other.f_ptr_ = nullptr;
}

FortranGrid::~FortranGrid() {
  ai_bridge_f_grid_free(f_ptr_);
}

FortranGrid& FortranGrid::operator=(FortranGrid& other) {
  if (this != &other) {
    if (f_ptr_) {
      ai_bridge_f_grid_free(f_ptr_);
    }
    f_ptr_ = ai_bridge_f_grid_clone(other.f_ptr_);
  }
  return *this;
}

FortranGrid& FortranGrid::operator=(FortranGrid&& other) {
  if (this != &other) {
    f_ptr_ = other.f_ptr_;
    other.f_ptr_ = nullptr;
  }
  return *this;
}

} // namespace ai
