/* Copyright (C) 2022 National Center for Atmospheric Research,
 * National Technology & Engineering Solutions of Sandia, LLC (NTESS),
 * and the U.S. Environmental Protection Agency (USEPA)
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AERO_INTERPOLATOR_H
#define AERO_INTERPOLATOR_H

#include <aero/aero.h>
#include <aero/array/array.h>
#include <aero/grid/grid.h>

#ifdef __cplusplus
extern "C" {
#endif

/// This opaque type represents an implementation of an interpolator
typedef struct aero_interpolator_impl_t aero_interpolator_impl_t;

/// Behaviors and data associated with an Interpolator. All of these
/// functions are passed the data pointer created by an Interplator
/// constructor.
typedef struct aero_interpolator_t aero_interpolator_t;
typedef struct aero_interpolator_t {
  /// pointer to the interpolator weights and other parameters
  aero_interpolator_impl_t *impl_;
  /// frees resources associated with an interpolator
  void (*free)(aero_interpolator_t *interp);
  /// interpolates from an array on the input grid to an array
  /// on the output grid
  void (*interpolate)(const aero_interpolator_t *interp,
    const aero_array_t *from, aero_array_t *to);
} aero_interpolator_t;

/// Creates an linear interpolator from one grid to another
aero_interpolator_t* aero_linear_interpolator(const aero_grid_t *from,
  const aero_grid_t *to);

#ifdef __cplusplus
} // extern
#endif

#endif
