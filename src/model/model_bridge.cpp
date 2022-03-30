//===-- interface/aerosol/ai_bridge_aerosol.cpp -----------------*- C++ -*-===//
//
// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//
///
/// \file C/C++ <--> Fortran bridge functions for the Aerosol class
///
//===----------------------------------------------------------------------===//
#include "model_bridge.h"

#include <iostream>

void* aero_bridge_c_new_model(const char *package_name,
                              const char *description_file) {
  std::cout << "Building C aerosol '" << package_name << "'" << std::endl;
  return nullptr;
}

void* aero_bridge_cpp_new_model(const char *package_name,
                                const char *description_file) {
  std::cout << "Building C++ aerosol '" << package_name << "'" << std::endl;
  return nullptr;
}

bool aero_bridge_c_supports_model(const char *package_name) {
  return true;
}

bool aero_bridge_cpp_supports_model(const char *package_name) {
  return true;
}

void aero_bridge_c_model_free(void *model) {
}

void aero_bridge_cpp_model_free(void *model) {
}
