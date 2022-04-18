################################################################################
# Test utilities

include(test_util)

################################################################################
# Tests for the Grid class

create_standard_test(NAME fortran_grid SOURCES grid.F90
                                               grid_helper.cpp)

create_standard_test(NAME c_grid SOURCES grid.c
                                         grid_helper.F90
                                         grid_helper.cpp)

create_standard_test(NAME cpp_grid SOURCES grid.cpp
                                           grid_helper.F90)

################################################################################
