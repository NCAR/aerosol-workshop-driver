// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#ifndef AERO_MODEL_FACTORY_HPP
#define AERO_MODEL_FACTORY_HPP

#include <aero/model/model.hpp>
#include <string>

namespace aero {

  /// Creates a new model from any language in C++
  Model* cpp_factory_new_model(std::string package_name, std::string description_file);

}

#endif // AERO_MODEL_FACTORY_HPP
