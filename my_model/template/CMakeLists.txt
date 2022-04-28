################################################################################
# Aerosol library helper function

include(model_config)

################################################################################
# These stub libraries allow us to test the basic interface. They are linked
# against the test drivers defined in ../driver.

create_aerosol_model(NAME "my model"
                     TYPE my_model_t
                     F90_MODULE my_model
                     LIBRARY my_model_fortran_stub
                     SOURCE_DIR fortran
                     SOURCE fortran/my_model.F90)

create_aerosol_model(NAME "my model"
                     TYPE MyModel
                     HEADER_FILE cpp/my_model.hpp
                     LIBRARY my_model_cpp_stub
                     SOURCE_DIR cpp
                     SOURCE cpp/my_model.cpp)

create_aerosol_model(NAME "my model"
                     HEADER_FILE c/my_model.h
                     LIBRARY my_model_c_stub
                     SOURCE_DIR c
                     SOURCE c/my_model.c)

################################################################################
