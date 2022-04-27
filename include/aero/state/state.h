#ifndef AERO_STATE_H
#define AERO_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

/// This opaque type represents an aerosol state implemented in C.
typedef struct aero_state_data_t aero_state_data_t;

/// Here are behaviors implemented by a C++-backed aerosol state. All of the
/// functions are passed the state data pointer
typedef struct aero_state_t aero_state_t;
typedef struct aero_state_t {
  /// Data members of the aero_state_t class
  aero_state_data_t *data_;
  /// Destroys the state's contextual data, freeing any associated resources
  void (*free)(aero_state_t* state);
} aero_state_t;

#ifdef __cplusplus
} // extern "C"
#endif

#endif
