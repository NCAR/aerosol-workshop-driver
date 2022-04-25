// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//

#include <aero/model/c_model.hpp>
#include <aero/model/fortran_model.hpp>
#include <string>
#include "model_factory.h"
#include "model_factory.hpp"

namespace aero {

  Model* cpp_factory_new_model(std::string package_name, std::string description_file) {
    void *model = aero_factory_new_cpp_model(package_name.c_str(), description_file.c_str());
    if (model) return reinterpret_cast<Model*>(model);
    model = aero_factory_new_c_model(package_name.c_str(), description_file.c_str());
    if (model) return new CModel(model, true);
    model = aero_factory_new_fortran_model(package_name.c_str(), description_file.c_str());
    if (model) return new FortranModel(model, true);
    return nullptr;
  }

}
