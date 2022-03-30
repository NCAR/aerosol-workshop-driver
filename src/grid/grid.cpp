#include "grid_bridge.h"
#include <aero/grid/grid.hpp>

namespace aero {

FortranGrid::FortranGrid(void *fortran_pointer):
  f_ptr_(fortran_pointer) {}

FortranGrid::FortranGrid(FortranGrid& other):
  f_ptr_(nullptr) {
  f_ptr_ = aero_bridge_fortran_grid_clone(other.f_ptr_);
}

FortranGrid::FortranGrid(FortranGrid&& other):
  f_ptr_(nullptr) {
  f_ptr_ = other.f_ptr_;
  other.f_ptr_ = nullptr;
}

FortranGrid::~FortranGrid() {
  aero_bridge_fortran_grid_free(f_ptr_);
}

FortranGrid& FortranGrid::operator=(FortranGrid& other) {
  if (this != &other) {
    if (f_ptr_) {
      aero_bridge_fortran_grid_free(f_ptr_);
    }
    f_ptr_ = aero_bridge_fortran_grid_clone(other.f_ptr_);
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

} // namespace aero
