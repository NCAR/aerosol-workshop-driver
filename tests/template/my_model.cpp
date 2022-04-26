#include <aero/aero.hpp>
#include <aero/array/array.hpp>
#include <aero/grid/grid.hpp>
#include <my_model.hpp>
#include <iostream>

void test_my_model() {

  aero::Model *model = new MyModel("");
  aero::State *state = model->create_state();
  const aero::Grid *model_grid = model->optics_grid();
  aero::Array *od, *od_ssa, *od_asym;
  int size;

  size = model_grid->interfaces().size();
  AERO_ASSERT(size == 4);
  od      = new aero::Array(size, 0.0);
  od_ssa  = new aero::Array(size, 0.0);
  od_asym = new aero::Array(size, 0.0);
  std::vector<aero::Real> od_v(     size, 0.0);
  std::vector<aero::Real> od_ssa_v( size, 0.0);
  std::vector<aero::Real> od_asym_v(size, 0.0);


  model->compute_optics(*state, *od, *od_ssa, *od_asym);
  od->copy_out(od_v);
  od_ssa->copy_out(od_ssa_v);
  od_asym->copy_out(od_asym_v);

  AERO_ASSERT(aero::almost_equal(od_v[1], 0.35));
  AERO_ASSERT(aero::almost_equal(od_ssa_v[3], 0.75 * 0.88));
  AERO_ASSERT(aero::almost_equal(od_asym_v[0], 0.27 * 0.88 * 0.3));

  delete(od);
  delete(od_ssa);
  delete(od_asym);
  delete(model_grid);
  delete(state);
  delete(model);

}

int main(int argc, char *argv[]) {
  test_my_model();
  return 0;
}
