################################################################################
# Test utilities

include(test_util)

################################################################################
# Tests for the model stubs

create_standard_test( NAME fortran_model_stub SOURCES my_model.F90
                      ${CMAKE_SOURCE_DIR}/my_model/template/fortran/my_model.F90)

################################################################################
