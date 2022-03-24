/*===-- interface/aerosol_cpp.h ---------------------------------*- C++ -*-===//
 *
 * Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 *
 *===----------------------------------------------------------------------===//
 *
 * C-C++ Wrappers for Aerosol base class
 *
 *===----------------------------------------------------------------------===//
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void * ai_build_cpp_aerosol( const char * package_name,
    const char * description_file );

#ifdef __cplusplus
}
#endif
