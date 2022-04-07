#ifndef AERO_GRID_H
#define AERO_GRID_H

#include <aero/array/array.h>

#ifdef __cplusplus
extern "C" {
#endif

/// This type represents a computional grid consisting of a set of contiguous
/// segments separated by interfaces. The grid stores the locations of the
/// interfaces and the midpoints between them.
typedef struct aero_grid_t {
  /// array storing interface coordinates (in ascending order)
  aero_array_t *interfaces;
  /// array storing coordinates of midpoints between interfaces (in ascending
  /// order)
  aero_array_t *midpoints;
  /// lower bound (minimum interface coordinate), provided for convenience
  aero_real_t lower_bound;
  /// upper bound (maximum interface coordinate), provided for convenience
  aero_real_t upper_bound;
} aero_grid_t;

/// Creates a grid from an array containing points delimiting the interfaces
/// between segments. The grid assumes ownership of this array.
aero_grid_t aero_grid_from_interfaces(aero_array_t *interfaces);

/// Frees the resources associated with this grid.
void aero_grid_free(aero_grid_t grid);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
