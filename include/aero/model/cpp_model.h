#ifndef AERO_CPP_MODEL_H
#define AERO_CPP_MODEL_H

#include "model.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Creates a model by wrapping a C++-backed model
aero_model_t* aero_cpp_model_wrap(void *model);

/// "Unwraps" a wrapped C++-backed model, freeing the wrapper resources but
/// leaving the original C++ model intact.
void aero_cpp_model_unwrap(aero_model_t *model);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
