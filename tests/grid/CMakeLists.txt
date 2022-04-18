################################################################################
# Test utilities

include(test_util)

################################################################################
# Tests for the Grid class

set(test_src grid.F90 grid_helper.cpp)
create_standard_test(fortran_grid "${test_src}")

set(test_src grid.c grid_helper.F90 grid_helper.cpp)
create_standard_test(c_grid "${test_src}")

set(test_src grid.cpp grid_helper.F90)
create_standard_test(cpp_grid "${test_src}")

################################################################################
