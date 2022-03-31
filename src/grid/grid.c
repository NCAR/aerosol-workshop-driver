#include <aero/grid/grid.h>

struct aero_grid_t {
  // Arrays for grid interfaces and midpoints.
  aero_array_t *interfaces, *midpoints;
  // Lower and upper bounds.
  aero_grid_bounds_t bounds;
};

aero_grid_t* aero_grid_from_interfaces(aero_array_t *interfaces) {
  // The grid takes ownership of this interfaces array.
  aero_grid_t *grid = malloc(sizeof(aero_grid_t));
  grid->interfaces = interfaces;
  // TODO: Extract data from interfaces array.
  grid->midpoints = NULL;
  return grid;
}

void aero_grid_free(aero_grid_t *grid) {
  // The grid owns its arrays, so it deletes them.
  aero_array_free(grid->interfaces);
  aero_array_free(grid->midpoints);
  free(grid);
}

aero_grid_bounds_t aero_grid_bounds(aero_grid_t *grid) {
  return grid->bounds;
}

aero_array_t* aero_grid_interfaces(aero_grid_t *grid) {
  return grid->interfaces;
}

aero_array_t* aero_grid_midpoints(aero_grid_t *grid) {
  return grid->midpoints;
}

