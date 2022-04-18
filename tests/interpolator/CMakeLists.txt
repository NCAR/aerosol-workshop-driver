################################################################################
# Test utilities

include(test_util)

################################################################################
# Tests for the Interpolator class

create_standard_test(NAME fortran_interpolator SOURCES interpolator.c)

create_standard_test(NAME test_c_interpolator SOURCES interpolator.c)

create_standard_test(NAME test_cpp_interpolator SOURCES interpolator.cpp)

################################################################################
