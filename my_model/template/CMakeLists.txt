################################################################################
# These stub libraries allow us to test the basic interface. They are linked
# against the test drivers defined in ../driver.

add_library(my_aerosol_f90_stub
            fortran/my_aerosol.F90
            fortran/aerosol_factory.F90)

add_library(my_aerosol_cpp_stub
            cpp/my_aerosol.cpp
            cpp/aerosol_factory.F90)

add_library(my_aerosol_c_stub
            c/my_aerosol.c
            c/aerosol_factory.F90)

################################################################################
