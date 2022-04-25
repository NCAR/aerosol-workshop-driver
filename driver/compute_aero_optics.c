// Include your aerosol model here.
#include <model_factory.h>

#include <aero/grid/grid.h>
#include <aero/interpolator/interpolator.h>

#include <stdio.h>
#include <stdlib.h>

// Prints usage information.
void usage(const char *exe_name) {
  fprintf(stderr, "%s: Usage:\n", exe_name);
  fprintf(stderr, "%s <package_name> <input_file>\n", exe_name);
  exit(1);
}

// This helper creates a grid used by the host model. For simplicity, we
// use a grid with twice the resolution of the aerosol wavelength grid in
// the template example. The grid's interfaces are wave numbers [m-1]; we
// specify wavelengths in descending order so their wave numbers appear in
// ascending order in the grid interfaces array.
aero_grid_t* create_host_wavelength_grid(void) {
  aero_real_t wavelengths[] = {
    1020.0, 945.0, 870.0, 777.5, 675.0, 557.5, 440.0 // [nm]
  };

  // Convert to wave numbers [m-1] for the grid's interfaces.
  aero_real_t wave_numbers[7];
  for (size_t i = 0; i < 7; ++i) {
    wave_numbers[i] = 1e-9 / wavelengths[i];
  }

  aero_array_t *ifaces = aero_array_from_array(7, wave_numbers);
  return aero_grid_from_interfaces(ifaces);
}

// This helper creates an array whose data conforms to the interfaces in the
// given grid.
aero_array_t* create_array_from_grid(aero_grid_t *grid) {
  const aero_array_t *interfaces = aero_grid_interfaces(grid);
  size_t n = interfaces->size(interfaces);
  return aero_array_from_dimensions(n, 0.0);
}

// This helper is called by write_optics_data (below) to write array data to
// a Python module.
static void write_array_data(FILE *fp,
                             const char *array_name,
                             const aero_array_t *array) {
  size_t size = array->size(array);
  fprintf(fp, "%s = [", array_name);
  aero_real_t data[size];
  array->copy_out(array, data);
  for (size_t i = 0; i < size; ++i) {
    fprintf(fp, "%g, ", data[i]);
  }
  fprintf(fp, "]\n");
}

// This helper writes aerosol optics data to a Python module with the given
// filename.
static void write_optics_data(const char *filename,
                              const aero_grid_t *grid,
                              const aero_array_t *od,
                              const aero_array_t *od_ssa,
                              const aero_array_t *od_asym) {
  FILE *fp = fopen(filename, "w");

  // Check that the arrays are properly sized.
  const aero_array_t *ifaces = aero_grid_interfaces(grid);
  size_t num_ifaces = ifaces->size(ifaces);
  AERO_ASSERT(num_ifaces == od->size(od));
  AERO_ASSERT(num_ifaces == od_ssa->size(od));
  AERO_ASSERT(num_ifaces == od_asym->size(od));

  // Write out grid interfaces.
  fprintf(fp, "# Grid interfaces\n");
  write_array_data(fp, "interfaces", ifaces);

  // Write out data.
  fprintf(fp, "# Aerosol optical depth [m]\n");
  write_array_data(fp, "od", od);
  fprintf(fp, "# Aerosol scattering optical depth [m]\n");
  write_array_data(fp, "od_ssa", od_ssa);
  fprintf(fp, "# Aerosol asymmetric scattering optical depth [m]\n");
  write_array_data(fp, "od_asym", od_asym);

  fclose(fp);
}

int main(int argc, char *argv[]) {

  if (argc < 3) {
    usage((const char*)argv[0]);
  }

  const char *package_name = (const char*)argv[1];
  const char *desc_file    = (const char*)argv[2];

  // Construct your aerosol model from the given description file.
  aero_model_t *model = aero_c_factory_new_model(package_name, desc_file);
#if 0
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

  // Write the data to a Python module named after the aerosol package.
  char filename[FILENAME_MAX];
  snprintf(filename, FILENAME_MAX, "%s.py", package_name);
  write_optics_data(filename, host_grid, host_od, host_od_ssa, host_od_asym);

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
#endif
  model->free(model);

  printf("\nFinished!\n\n");
  return 0;
}
