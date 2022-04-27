/* Copyright (C) 2022 National Center for Atmospheric Research,
 * National Technology & Engineering Solutions of Sandia, LLC (NTESS),
 * and the U.S. Environmental Protection Agency (USEPA)
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AI_MY_MODEL_H
#define AI_MY_MODEL_H

#include "aero/model/model.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Implement this function to create your aerosol model.
aero_model_t* my_model_new(const char *description_file);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AI_MY_MODEL_H
