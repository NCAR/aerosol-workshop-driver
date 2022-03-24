//===-- interface/aerosol_cpp.cpp -------------------------------*- C++ -*-===//
//
// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//
///
/// \file C wrapper for C++ base aerosol
///
//===----------------------------------------------------------------------===//
#include <iostream>
#include "aerosol_cpp.h"

void * ai_build_cpp_aerosol( const char * package_name,
    const char * desciprion_file ) {
  std::cout << "Building C++ aeroosl '" << package_name << "'" << std::endl;
  return NULL;
}
