/* Copyright (C) 2022 National Center for Atmospheric Research,
 * National Technology & Engineering Solutions of Sandia, LLC (NTESS),
 * and the U.S. Environmental Protection Agency (USEPA)
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AERO_CPP_MODEL_H
#define AERO_CPP_MODEL_H

#include "model.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Creates a new C++-backed Model
/// The flag \c owns_model is used to indicate whether this wrapper owns
/// the underlying model
aero_model_t* aero_new_cpp_model(void *cpp_model, bool owns_model);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
