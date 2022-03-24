################################################################################
# Template code for tests

set( TEMPLATE_F90_SRC template/fortran/my_aerosol.F90
                      template/fortran/aerosol_factory.F90
                      PARENT_SCOPE )

set( TEMPLATE_CPP_SRC template/cpp/my_aerosol.cpp
                      template/cpp/aerosol_factory.F90
                      PARENT_SCOPE )

################################################################################
