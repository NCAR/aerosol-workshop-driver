//===-- template/c/my_aerosol.h -----------------------------*- C -*-===//
//
// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//
///
/// \file Implementation of an aerosol model
///
//===----------------------------------------------------------------------===//

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
