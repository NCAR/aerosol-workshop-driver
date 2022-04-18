################################################################################
# Test utilities

include(test_util)

################################################################################
# Tests for the Array class

create_standard_test(NAME fortran_array SOURCES array.F90
                                                array_helper.c
                                                array_helper.cpp)

create_standard_test(NAME c_array SOURCES array.c
                                          array_helper.F90
                                          array_helper.cpp)

create_standard_test(NAME cpp_array SOURCES array.cpp
                                            array_helper.F90)

################################################################################
