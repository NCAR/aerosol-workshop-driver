//===-- template/cpp/my_aerosol.cpp -----------------------------*- C++ -*-===//
//
// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//
///
/// \file My aerosol functions
///
//===----------------------------------------------------------------------===//

#include "my_model.hpp"

namespace mya {

// Aerosol state specific to this model
class MyState : public aero::State {
public:
  // (All data in the state is public for simplicity.)
  std::vector<aero::Real> od,      // aerosol optical depth [m]
                          od_ssa,  // aerosol single scattering albedo [-]
                          od_asym; // aerosol asymmetric scattering optical
                                   // depth [m]

  // Constructor
  MyState()
    : aero::State() {

    // We initialize vectors with data pulled from
    // https://acp.copernicus.org/articles/18/7815/2018/acp-18-7815-2018-f03.pdf
    // For this state, we use the "mixed type" measures, indicated by triangles.
    // Note the units in the fields of the my_model_data_t struct at the top of
    // this file. The data here corresponds to the grid interfaces shown in the
    // figure.
    od      = {0.75, 0.5, 0.35, 0.27};       // top left
    od_ssa  = {0.88, 0.905, 0.895, 0.88};    // middle left
    od_asym = {0.09, 0.045, 0.035, 0.3};     // top right
  }
};

MyModel::MyModel()
  : aero::Model(),
    grid_(nullptr) {

  // Initialize the aerosol grid with wavelength data pulled from
  // https://acp.copernicus.org/articles/18/7815/2018/acp-18-7815-2018-f03.pdf
  aero::Real wavelengths[] = {440.0, 675.0, 870.0, 1020.0}; // [nm]

  // Convert to wave numbers for the grid's interfaces.
  std::vector<aero::Real> wave_numbers;
  for (size_t i = 0; i < 4; ++i) {
    wave_numbers.push_back(1e-9 / wavelengths[i]); // [m-1]
  }

  // Create an interfaces array and, from it, a grid.
  aero::Array *interfaces = new aero::Array(wave_numbers);
  grid_ = new aero::Grid(interfaces);
}

MyModel::~MyModel() {
  delete grid_;
}

std::string MyModel::name() const {
  return "My Model";
}

aero::State* MyModel::create_state() const {
  return new MyState();
}

const aero::Grid& MyModel::optics_grid() const {
  return *grid_;
}

void MyModel::compute_optics(const aero::State& state,
                             aero::Array& od,
                             aero::Array& od_ssa,
                             aero::Array& od_asym) const {
  // We simply copy the state's optics data into place.
  const MyState& my_state = dynamic_cast<const MyState&>(state);
  od.copy_in(my_state.od);
  od_ssa.copy_in(my_state.od_ssa);
  od_asym.copy_in(my_state.od_asym);
}

} // namespace mya
