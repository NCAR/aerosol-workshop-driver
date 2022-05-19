// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#include <aero/model/model.h>
#include <aero/model/model.hpp>
#include <aero/model/c_model.hpp>
#include <aero/model/cpp_model.h>
#include <aero/model/fortran_model.h>
#include <aero/model/fortran_model.hpp>
#include "model_factory.h"

#ifdef __cplusplus
extern "C" {
#endif

aero_model_t* aero_c_factory_new_model(const char *package_name,
    const char *description_file) {
  void *model = aero_factory_new_c_model(package_name, description_file);
  if (model) return (aero_model_t*) model;
  model = aero_factory_new_cpp_model(package_name, description_file);
  if (model) return aero_new_cpp_model(model, true);
  model = aero_factory_new_fortran_model(package_name, description_file);
  if (model) return aero_new_fortran_model(model, true);
  return NULL;
}

void* aero_factory_new_c_model(const char *package_name,
    const char *description_file) {
  return NULL;
}

void* aero_factory_new_cpp_model(const char *package_name,
    const char *description_file) {
  return NULL;
}

#ifdef __cplusplus
} // extern "C"
#endif

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
