/* Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AERO_MODEL_FACTORY_H
#define AERO_MODEL_FACTORY_H

#include <stdbool.h>

/// Builder of all-language aerosol model objects in C
aero_model_t* create_model(const char* package_name, const char* description_file);

/// Returns whether an aerosol model is supported in C
bool is_c_model(const char* package_name);

/// Builder of C aerosol model objects
aero_model_t* create_c_model(const char* package_name, const char* description_file);

#endif // AERO_MODEL_FACTORY_H
