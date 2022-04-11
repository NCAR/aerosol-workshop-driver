#ifndef AERO_GRID_H
#define AERO_GRID_H

#include <aero/array/array.h>

#ifdef __cplusplus
extern "C" {
#endif

/// This opaque type represents a computional grid consisting of a set of
/// contiguous segments separated by interfaces. The grid stores the locations
/// of the interfaces and the midpoints between them.
typedef struct aero_grid_t aero_grid_t;

/// Creates a grid from an array containing points delimiting the interfaces
/// between segments. The grid assumes ownership of this array.
aero_grid_t* aero_grid_from_interfaces(aero_array_t *interfaces);

/// Frees the resources associated with this grid.
void aero_grid_free(aero_grid_t *grid);

/// Provides const access to the grid interfaces.
const aero_array_t* aero_grid_interfaces(const aero_grid_t *grid);

/// Provides const access to the grid interface midpoints.
const aero_array_t* aero_grid_midpoints(const aero_grid_t *grid);

/// Returns the lower bound of the grid.
aero_real_t aero_grid_lower_bound(const aero_grid_t *grid);

/// Returns the upper bound of the grid.
aero_real_t aero_grid_upper_bound(const aero_grid_t *grid);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
