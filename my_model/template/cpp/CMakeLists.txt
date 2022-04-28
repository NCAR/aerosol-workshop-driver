################################################################################
# Aerosol library helper function

include(model_config)

################################################################################
# Aerosol model build configuration

create_aerosol_model(NAME "my model"          # String a host model will use to find your model
                     TYPE MyModel             # Class describing your model
                     HEADER_FILE my_model.hpp # Header file for your model class
                     LIBRARY my_model         # Name of the library your model will be built into
                     SOURCE my_model.cpp)     # Space-separated list of all your aerosol model source files

################################################################################
