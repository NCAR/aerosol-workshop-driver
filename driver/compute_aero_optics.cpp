#include <model_factory.hpp>

#include <aero/interpolator/interpolator.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace {

void usage(const std::string &exe_name) {
  std::cerr << exe_name << ": Usage\n";
  std::cerr << exe_name << " <package_name> <input_file>\n";
  exit(1);
}

// This helper creates a grid used by the host model. For simplicity, we
// use a grid with twice the resolution of the aerosol wavelength grid in
// the template example. The grid's interfaces are wave numbers [m-1]; we
// specify wavelengths in descending order so their wave numbers appear in
// ascending order in the grid interfaces array.
aero::Grid create_host_wavelength_grid() {
  std::vector<aero::Real> wavelengths = {
    1020.0, 945.0, 870.0, 777.5, 675.0, 557.5, 440.0 // [nm]
  };

  // Convert to wave numbers [m-1] for the grid's interfaces.
  std::vector<aero::Real> wave_numbers;
  for (size_t i = 0; i < wavelengths.size(); ++i) {
    wave_numbers.push_back(1e-9 / wavelengths[i]);
  }

  auto *ifaces = new aero::Array(wave_numbers);
  return aero::Grid(ifaces);
}

// This helper is called by write_optics_data (below) to write array data to
// a Python module.
static void write_array_data(std::ofstream& out,
                             const std::string& array_name,
                             const aero::Array& array) {
  out << array_name << " = [";
  std::vector<aero::Real> data(array.size());
  array.copy_out(data);
  for (size_t i = 0; i < array.size(); ++i) {
    out << data[i] << ", ";
  }
  out << "]\n";
}

// This helper writes aerosol optics data to a Python module with the given
// filename.
void write_optics_data(const std::string& filename,
                       const aero::Grid &grid,
                       const aero::Array &od,
                       const aero::Array &od_ssa,
                       const aero::Array &od_asym) {
  std::ofstream out(filename);

  // Check that the arrays are properly sized.
  const aero::Array& ifaces = grid.interfaces();
  size_t num_ifaces = ifaces.size();
  AERO_ASSERT(num_ifaces == od.size());
  AERO_ASSERT(num_ifaces == od_ssa.size());
  AERO_ASSERT(num_ifaces == od_asym.size());

  // Write out grid interfaces.
  out << "# Grid interfaces\n";
  write_array_data(out, "interfaces", ifaces);

  // Write out data.
  out << "# Aerosol optical depth [m]\n";
  write_array_data(out, "od", od);
  out << "# Aerosol scattering optical depth [m]\n";
  write_array_data(out, "od_ssa", od_ssa);
  out << "# Aerosol asymmetric scattering optical depth [m]\n";
  write_array_data(out, "od_asym", od_asym);
}

} // anonymous namespace

int main(int argc, char *argv[]) {

  if (argc < 3) {
    usage(argv[0]);
  }

  std::string package_name(argv[1]);
  std::string desc_file(argv[2]);

  // Construct an aerosol model from the given package name and
  // descriptor file.
  aero::Model* model = aero::cpp_factory_new_model(package_name, desc_file);

  // Use the model to create an aerosol state.
  aero::State* state = model->create_state();

  // The host wavelength grid to which optical properties are interpolated.
  aero::Grid host_grid = create_host_wavelength_grid();

  // The grid the model uses to compute optical properties.
  aero::Grid* aero_grid = model->optics_grid();

  // An interpolator that interpolates data from aero_grid to host_grid,
  // using a pre-selected scheme.
  aero::Interpolator interp(*aero_grid, host_grid);

  // Make some arrays to store optical properties on the host and model grids.
  aero::Array host_od(host_grid.interfaces().size(), 0.0);
  aero::Array host_od_ssa(host_grid.interfaces().size(), 0.0);
  aero::Array host_od_asym(host_grid.interfaces().size(), 0.0);
  aero::Array aero_od(aero_grid->interfaces().size(), 0.0);
  aero::Array aero_od_ssa(aero_grid->interfaces().size(), 0.0);
  aero::Array aero_od_asym(aero_grid->interfaces().size(), 0.0);

  // Have the aerosol model compute its optical properties on its native grid.
//  model->compute_optics(*state, aero_od, aero_od_ssa, aero_od_asym);

  // Interpolate the aerosol optics to the host grid.
  interp.interpolate(aero_od, host_od);
  interp.interpolate(aero_od_ssa, host_od_ssa);
  interp.interpolate(aero_od_asym, host_od_asym);

  // Plot the results.
  // Write the data to a Python module named after the aerosol package.
  std::stringstream ss;
  ss << package_name << ".py";
  write_optics_data(ss.str(), host_grid, host_od, host_od_ssa, host_od_asym);

  // Clean up.
  delete aero_grid;
  delete state;
  delete model;

  std::cout << "Finished!" << std::endl;
  return 0;
}
