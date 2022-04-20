################################################################################
# Test utilities

include(test_util)

################################################################################
# Tests for the Interpolator class

create_standard_test(NAME fortran_interpolator SOURCES interpolator.F90)

create_standard_test(NAME c_interpolator SOURCES interpolator.c)

create_standard_test(NAME cpp_interpolator SOURCES interpolator.cpp)

################################################################################
