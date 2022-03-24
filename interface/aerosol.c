/*===-- interface/aerosol.c -------------------------------------*- C++ -*-===//
 *
 * Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 *
 *===----------------------------------------------------------------------===//
 *
 * Aerosol base class functions
 *
 *===----------------------------------------------------------------------===//
 */
#include "aerosol.h"
#include "aerosol_cpp.h"

void * ai_build_non_fortran_aerosol( const char * package_name,
    const char * description_file ) {
  return ai_build_cpp_aerosol( package_name, description_file );
}
