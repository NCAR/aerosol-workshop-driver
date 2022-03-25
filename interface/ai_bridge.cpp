//===-- interface/aerosol_cpp.cpp -------------------------------*- C++ -*-===//
//
// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//
///
/// \file C/C++ <--> Fortran bridge functions
///
//===----------------------------------------------------------------------===//
#include <iostream>
#include "ai_bridge.h"

void* ai_bridge_c_new_aerosol(const char *package_name,
                              const char *description_file) {
  std::cout << "Building C aerosol '" << package_name << "'" << std::endl;
  return nullptr;
}

void* ai_bridge_cpp_new_aerosol(const char *package_name,
                                const char *description_file) {
  std::cout << "Building C++ aerosol '" << package_name << "'" << std::endl;
  return nullptr;
}

void ai_bridge_c_aerosol_free(void *aerosol) {
}

void ai_bridge_cpp_aerosol_free(void *aerosol) {
}

void* ai_bridge_c_state_clone(void *state) {
  return nullptr;
}

void* ai_bridge_cpp_state_clone(void *state) {
  return nullptr;
}

void ai_bridge_c_state_free(void *aerosol) {
}

void ai_bridge_cpp_state_free(void *aerosol) {
}

void* ai_bridge_c_array_clone(void *state) {
  return nullptr;
}

void* ai_bridge_cpp_array_clone(void *state) {
  return nullptr;
}

void ai_bridge_c_array_free(void *aerosol) {
}

void ai_bridge_cpp_array_free(void *aerosol) {
}

void* ai_bridge_c_grid_clone(void *state) {
  return nullptr;
}

void* ai_bridge_cpp_grid_clone(void *state) {
  return nullptr;
}

void ai_bridge_c_grid_free(void *aerosol) {
}

void ai_bridge_cpp_grid_free(void *aerosol) {
}

