################################################################################
# Aerosol library helper function

include(model_config)

################################################################################
# Aerosol model build configuration

create_aerosol_model(NAME "my model"      # String a host model will use to find your model
                     TYPE my_model_t      # Derived type describing your model
                     F90_MODULE my_model  # Fortran module where your derived type is defined
                     LIBRARY my_model     # Name of the library your model will be built into
                     SOURCE my_model.F90 cmaq_aero_optics.F90 complex_number_module.F90) # Space-separated list of all your aerosol model source files

################################################################################
