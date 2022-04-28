################################################################################
# Aerosol library helper function

include(model_config)

################################################################################
# Aerosol model build configuration

create_aerosol_model(NAME "my model"        # String a host model will use to find your model
                     TYPE my_model          # Prefix used in constructor for your model
                     HEADER_FILE my_model.h # Header file for your model class
                     LIBRARY my_model       # Name of the library your model will be built into
                     SOURCE my_model.c)     # Space-separated list of all your aerosol model source files

################################################################################
