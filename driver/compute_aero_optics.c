#include <stdio.h>
#include <stdlib.h>

void usage(const char *exe_name) {
  fprintf(stderr, "%s: Usage:\n", exe_name);
  fprintf(stderr, "%s <package_name> <input_file>\n", exe_name);
  exit(1);
}

// This helper creates an array whose data conforms to the given grid.
//aero_array_t* create_array_from_grid(aero_grid_t *grid) {
  // TODO
//}

// This helper plots the aerosol optics data on the given grid.
//void plot_optics(aero_grid_t *grid, aero_array_t *od, aero_array_t *od_ssa,
//                 aero_array_t *od_asym) {
  // TODO
//}

int main(int argc, char *argv[]) {

  if (argc < 3) {
    usage((const char*)argv[0]);
  }

  const char *package_name = (const char*)argv[1];
  const char *desc_file    = (const char*)argv[2];

  // Construct an aerosol model from the given package name and
  // descriptor file.
//  aero_model_t *model = create_model(package_name, desc_file);

  // Use the model to create an aerosol state.
//  aero_state_t *state = aero_model_create_state(model);

  // The host wavelength grid to which optical properties are interpolated.
//  aero_grid_t *host_grid = create_host_wavelength_grid();

  // The grid the model uses to compute optical properties.
//  aero_grid_t *aero_grid = aero_model_optics_grid(model);

  // An interpolator that interpolates data from aero_grid to host_grid,
  // using a pre-selected scheme.
//  aero_interp_t *interp = create_interpolator(aero_grid, host_grid);

  // Make some arrays to store optical properties on the host and model grids.
//  aero_array_t *host_od      = create_array_from_grid(host_grid);
//  aero_array_t *host_od_ssa  = create_array_from_grid(host_grid);
//  aero_array_t *host_od_asym = create_array_from_grid(host_grid);
//  aero_array_t *aero_od      = create_array_from_grid(aero_grid);
//  aero_array_t *aero_od_ssa  = create_array_from_grid(aero_grid);
//  aero_array_t *aero_od_asym = create_array_from_grid(aero_grid);

  // Have the aerosol model compute its optical properties on its native grid.
//  int err = aero_model_compute_optics(model, state, aero_od, aero_od_ssa,
//                                    aero_od_asym);

  // Interpolate the aerosol optics to the host grid.
//  err = aero_interp(interp, aero_od, host_od);
//  err = aero_interp(interp, aero_od_ssa, host_od_ssa);
//  err = aero_interp(interp, aero_od_asym, host_od_asym);

  // Plot the results.
//  plot_optics(host_grid, host_od, host_od_ssa, host_od_asym);

  // Clean up.
//  aero_array_free(aero_od);
//  aero_array_free(aero_od_ssa);
//  aero_array_free(aero_od_asym);
//  aero_array_free(host_od);
//  aero_array_free(host_od_ssa);
//  aero_array_free(host_od_asym);

//  aero_interp_free(interp);
//  aero_grid_free(aero_grid);
//  aero_grid_free(hoѕt_grid);
//  aero_state_free(state);
//  aero_model_free(model);

  printf("\nFinished!\n\n");
  return 0;
}
