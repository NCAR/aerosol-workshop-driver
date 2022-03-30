#include <iostream>
#include <string>
#include "aero/model/model.hpp"

namespace {

void usage(const std::string &exe_name) {
  std::cerr << exe_name << ": Usage\n";
  std::cerr << exe_name << " <package_name> <input_file>\n";
  exit(1);
}

// This helper creates an array whose data conforms to the given grid.
//aero::Array create_array_from_grid(const aero::Grid &grid) {
  // TODO
//}

// This helper plots the aerosol optics data on the given grid.
//void plot_optics(const aero::Grid &grid, const aero::Array &od,
//                 const aero::Array &od_ssa, const aero::Array &od_asym) {
  // TODO
//}

} // anonymous namespace

int main(int argc, char *argv[]) {

  if (argc < 3) {
    usage(argv[0]);
  }

  std::string package_name(argv[1]);
  std::string desc_file(argv[2]);

  // Construct an aerosol model from the given package name and
  // descriptor file.
  aero::Model* model; // = aero::create_model(package_name, desc_file);

  // Use the model to create an aerosol state.
//  aero::State state = model.create_state();

  // The host wavelength grid to which optical properties are interpolated.
//  aero::Grid host_grid = create_host_wavelength_grid();

  // The grid the model uses to compute optical properties.
//  aero::Grid aero_grid = model.optics_grid();

  // An interpolator that interpolates data from aero_grid to host_grid,
  // using a pre-selected scheme.
//  aero::Interp interp = create_interpolator(aero_grid, host_grid);

  // Make some arrays to store optical properties on the host and model grids.
//  aero::Array host_od      = create_array_from_grid(host_grid);
//  aero::Array host_od_ssa  = create_array_from_grid(host_grid);
//  aero::Array host_od_asym = create_array_from_grid(host_grid);
//  aero::Array aero_od      = create_array_from_grid(aero_grid);
//  aero::Array aero_od_ssa  = create_array_from_grid(aero_grid);
//  aero::Array aero_od_asym = create_array_from_grid(aero_grid);

  // Have the aerosol model compute its optical properties on its native grid.
//  model.compute_optics(state, aero_od, aero_od_ssa, aero_od_asym);

  // Interpolate the aerosol optics to the host grid.
//  interp.interpolate(aero_od, host_od);
//  interp.interpolate(aero_od_ssa, host_od_ssa);
//  interp.interpolate(aero_od_asym, host_od_asym);

  // Plot the results.
//  plot_optics(host_grid, host_od, host_od_ssa, host_od_asym);

  // Clean up.
  // delete model;

  std::cout << "Finished!" << std::endl;
  return 0;
}
