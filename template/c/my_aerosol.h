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

#ifndef AI_MY_AEROSOL_H
#define AI_MY_AEROSOL_H

#include "interface/ai_aerosol.h"

/// Implement this function to create your aerosol model.
ai_aerosol_t* my_aerosol_new(const char *description_file);

#endif // AI_MY_AEROSOL_H
