#include "grid_bridge.h"
#include <aero/grid/grid.hpp>

namespace aero {

Grid::Grid(Array&& interfaces):
  interfaces_(interfaces) {

  // TODO: Extract info from interfaces array here!
}

Grid::~Grid() {
}

} // namespace aero
