#ifndef AERO_GRID_H
#define AERO_GRID_H

#include <aero/array/array.h>

#ifdef __cplusplus
extern "C" {
#endif

/// This type represents a computional grid consisting of a set of contiguous
/// segments separated by interfaces. The grid keeps track of the midpoints
/// between interfaces.
typedef struct aero_grid_t aero_grid_t;

/// This type is a container for returning grid lower and upper bounds.
typedef struct aero_grid_bounds_t {
  aero_real_t lower, upper;
} aero_grid_bounds_t;

/// Creates a grid from an array containing points delimiting the interfaces
/// between segments. The grid assumes ownership of this array.
aero_grid_t* aero_grid_from_interfaces(aero_array_t *interfaces);

/// Frees the resources associated with this grid.
void aero_grid_free(aero_grid_t *grid);

/// Returns the lower and upper bounds (minimum and maximum grid interface
/// points) for the grid.
aero_grid_bounds_t aero_grid_bounds(aero_grid_t *grid);

/// Provides access to the array containing grid interfaces.
aero_array_t* aero_grid_interfaces(aero_grid_t *grid);

/// Provides access to the array containing grid segment midpoints.
aero_array_t* aero_grid_midpoints(aero_grid_t *grid);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
