// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
#ifndef AERO_MODEL_FACTORY_HPP
#define AERO_MODEL_FACTORY_HPP

#include <aero/model/model.hpp>

namespace aero {

  /// Builder of all-language aerosol model objects in C++
  Model* create_model(const char* package_name, const char* description_file);

  /// Returns whether an aerosol model is supported in C++
  bool is_cpp_model(const char* package_name);

  /// Builder of C++ aerosol model objects
  Model* create_cpp_model(const char* package_name, const char* description_file);

}

#endif // AERO_MODEL_FACTORY_HPP
