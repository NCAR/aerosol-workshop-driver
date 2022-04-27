# #################
# aero_config.cmake
# #################

# These variables are used to configure the aerosol model drivers with your own
# aerosol model.

# Set the AERO_MODEL_TYPE variable to the name of the class, type, or function
# that creates an instance of your aerosol model. The following values are valid
# for the aerosol template model code.
#set(AERO_MODEL_TYPE "my_model_t")   # Fortran derived type
set(AERO_MODEL_TYPE "MyModel")      # C++ class
#set(AERO_MODEL_TYPE "my_model_new") # C function

# Set the AERO_MODEL_SOURCE variable to the name of the source file containing
# the implementation of your aerosol model. The following values are valid for
# the aerosol template model code.
#set(AERO_MODEL_SOURCE "my_model.F90") # Fortran model implementation
set(AERO_MODEL_SOURCE "my_model.cpp") # C++ model implementation
#set(AERO_MODEL_SOURCE "my_model.c")   # C model implementation

# This sets an AERO_MODEL_HEADER variable containing the name of the appropriate
# header file used to declare the logic to create C/C++ models.
string(REPLACE ".c" ".h" AERO_MODEL_HEADER ${AERO_MODEL_SOURCE})
