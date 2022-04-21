// Include your aerosol model here.
#include "../my_model/template/c/my_model.h"

#include <aero/grid/grid.h>
#include <aero/interpolator/interpolator.h>

#include <stdio.h>
#include <stdlib.h>

void usage(const char *exe_name) {
  fprintf(stderr, "%s: Usage:\n", exe_name);
  fprintf(stderr, "%s <package_name> <input_file>\n", exe_name);
  exit(1);
}

// This helper creates a grid used by the host model.
aero_grid_t* create_host_wavelength_grid(void) {
  return NULL;
}

// This helper creates an array whose data conforms to the interfaces in the
// given grid.
aero_array_t* create_array_from_grid(aero_grid_t *grid) {
  const aero_array_t *interfaces = aero_grid_interfaces(grid);
  size_t n = interfaces->size(interfaces);
  return aero_array_from_dimensions(n, 0.0);
}

// This helper plots the aerosol optics data on the given grid.
void plot_optics(aero_grid_t *grid, aero_array_t *od, aero_array_t *od_ssa,
                 aero_array_t *od_asym) {
  // TODO
}

int main(int argc, char *argv[]) {

  if (argc < 3) {
    usage((const char*)argv[0]);
  }

  const char *package_name = (const char*)argv[1];
  const char *desc_file    = (const char*)argv[2];

  // Construct your aerosol model from the given description file.
  aero_model_t *model = my_model_new(desc_file);

  // Use the model to create an aerosol state.
  aero_state_t *state = aero_model_create_state(model);

  // The host wavelength grid to which optical properties are interpolated.
  aero_grid_t *host_grid = create_host_wavelength_grid();

  // The grid the model uses to compute optical properties.
  aero_grid_t *aero_grid = aero_model_optics_grid(model);

  // An interpolator that interpolates data linearly from aero_grid to
  // host_grid.
  aero_interpolator_t *interp = aero_linear_interpolator(aero_grid, host_grid);

  // Make some arrays to store optical properties on the host and model grids.
  aero_array_t *host_od      = create_array_from_grid(host_grid);
  aero_array_t *host_od_ssa  = create_array_from_grid(host_grid);
  aero_array_t *host_od_asym = create_array_from_grid(host_grid);
  aero_array_t *aero_od      = create_array_from_grid(aero_grid);
  aero_array_t *aero_od_ssa  = create_array_from_grid(aero_grid);
  aero_array_t *aero_od_asym = create_array_from_grid(aero_grid);

  // Have the aerosol model compute its optical properties on its native grid.
  aero_model_compute_optics(model, state, aero_od, aero_od_ssa, aero_od_asym);

  // Interpolate the aerosol optics to the host grid.
  interp->interpolate(interp, aero_od, host_od);
  interp->interpolate(interp, aero_od_ssa, host_od_ssa);
  interp->interpolate(interp, aero_od_asym, host_od_asym);

  // Plot the results.
  plot_optics(host_grid, host_od, host_od_ssa, host_od_asym);

  // Clean up.
  aero_od->free(aero_od);
  aero_od_ssa->free(aero_od_ssa);
  aero_od_asym->free(aero_od_asym);
  host_od->free(host_od);
  host_od_ssa->free(host_od_ssa);
  host_od_asym->free(host_od_asym);

  interp->free(interp);
  aero_grid_free(aero_grid);
  aero_grid_free(host_grid);
  aero_model_free_state(model, state);
  aero_model_free(model);

  printf("\nFinished!\n\n");
  return 0;
}
