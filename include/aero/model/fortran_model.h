#ifndef AERO_FORTRAN_MODEL_H
#define AERO_FORTRAN_MODEL_H

#include "model.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Creates a model by wrapping a Fortran-backed model
aero_model_t* aero_fortran_array_wrap(void *array);

/// "Unwraps" a wrapped Fortran-backed model, freeing the wrapper resources but
/// leaving the original Fortran model intact.
void aero_fortran_model_unwrap(aero_model_t *model);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
