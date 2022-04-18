################################################################################
# Test utilities

include(test_util)

################################################################################
# Tests for the Array class

set(test_src array.F90 array_helper.c array_helper.cpp)
create_standard_test(fortran_array "${test_src}")

set(test_src array.c array_helper.F90 array_helper.cpp)
create_standard_test(c_array "${test_src}")

set(test_src array.cpp array_helper.F90)
create_standard_test(cpp_array "${test_src}")

################################################################################
