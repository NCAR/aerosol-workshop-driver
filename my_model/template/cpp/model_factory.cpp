// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//

#include "model_factory.hpp"

namespace aero {

  Model* create_model(const char* package_name, const char* description_file) {
    if (strcmp(package_name, "my model") == 0) {
      return MyModel(description_file);
    }
    Model* new_model = CModel(package_name, description_file);
    if (new_model) return new_model;
    return FortranModel(package_name, description_file);
  }

  bool is_cpp_model(const char* package_name) {
    return false;
  }

  Model* create_cpp_model(const char* package_name, const char* description_file) {
    if (strcmp(package_name, "my model") == 0) {
      return MyModel(description_file);
    }
    AERO_ASSERT( false, "Unsupported C++ aerosol model" );
  }

}
