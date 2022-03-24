/*===-- interface/aerosol.h -------------------------------------*- C++ -*-===//
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
#pragma once

void * ai_build_non_fortran_aerosol( const char * package_name,
    const char * description_file );

