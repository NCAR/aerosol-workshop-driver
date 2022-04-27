// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#include <aero/model/model.hpp>

/// \brief My aerosol model
class MyModel : public aero::Model {

public:
  MyModel(const char* description_file);
  MyModel(const MyModel& other) = delete;
  MyModel(MyModel&& other) = delete;
  ~MyModel();
  MyModel& operator=(const MyModel& other) = delete;
  MyModel& operator=(MyModel&& other) = delete;
  std::string name() const override;
  aero::State* create_state() const override;
  aero::Grid* optics_grid() const override;
  void compute_optics(aero::State& state,
                      aero::Array& od,
                      aero::Array& od_ssa,
                      aero::Array& od_asym) const override;

private:

  aero::Grid* create_grid_();
  aero::Grid* grid_;
};
