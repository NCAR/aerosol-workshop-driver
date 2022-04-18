################################################################################
# Test utilities

include(test_util)

################################################################################
# Tests for the Interpolator class

create_standard_test(fortran_interpolator interpolator.c)

create_standard_test(test_c_interpolator interpolator.c)

create_standard_test(test_cpp_interpolator interpolator.cpp)

################################################################################
