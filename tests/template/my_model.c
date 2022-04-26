#include <aero/aero.h>
#include <aero/array/array.h>
#include <aero/grid/grid.h>
#include <my_model.h>
#include <stdio.h>
#include <stdlib.h>

void test_my_model_t() {

  aero_model_t *model = my_model_new("");
  aero_state_t *state = model->create_state(model);
  const aero_grid_t *model_grid = model->optics_grid(model);
  const aero_array_t *interfaces = aero_grid_interfaces(model_grid);
  aero_array_t *od, *od_ssa, *od_asym;
  aero_real_t *od_a, *od_ssa_a, *od_asym_a;
  int size;

  size = interfaces->size(interfaces);
  AERO_ASSERT(size == 4);
  od      = aero_array_from_dimensions(size, 0.0);
  od_ssa  = aero_array_from_dimensions(size, 0.0);
  od_asym = aero_array_from_dimensions(size, 0.0);
  od_a      = (aero_real_t*) malloc(size*sizeof(aero_real_t));
  od_ssa_a  = (aero_real_t*) malloc(size*sizeof(aero_real_t));
  od_asym_a = (aero_real_t*) malloc(size*sizeof(aero_real_t));

  model->compute_optics(model, state, od, od_ssa, od_asym);
  od->copy_out(od, od_a);
  od_ssa->copy_out(od_ssa, od_ssa_a);
  od->copy_out(od_asym, od_asym_a);

  AERO_ASSERT(almost_equal(od_a[1], 0.35));
  AERO_ASSERT(almost_equal(od_ssa_a[3], 0.75 * 0.88));
  AERO_ASSERT(almost_equal(od_asym_a[0], 0.27 * 0.88 * 0.3));

  od->free(od);
  od_ssa->free(od_ssa);
  od_asym->free(od_asym);
  model->free_state(model, state);
  model->free(model);
  free(od_a);
  free(od_ssa_a);
  free(od_asym_a);

}

int main(int argc, char *argv[]) {
  test_my_model_t();
  return 0;
}
