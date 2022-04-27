/* Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AERO_MODEL_FACTORY_H
#define AERO_MODEL_FACTORY_H

#include <aero/model/model.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Creates a new model from any langauge in C
aero_model_t* aero_c_factory_new_model(const char* package_name,
    const char* description_file);

/// Returns a pointer to a newly created Model in the given language
/// @{
void* aero_factory_new_c_model(const char* package_name,
    const char* description_file);
void* aero_factory_new_cpp_model(const char* package_name,
    const char* description_file);
void* aero_factory_new_fortran_model(const char* package_name,
    const char* description_file);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AERO_MODEL_FACTORY_H
