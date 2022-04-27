################################################################################
# Aerosol model library

add_library(my_model my_model.c
                     model_factory.cpp
                     model_factory.F90)

target_link_libraries(my_model PUBLIC aero)

################################################################################
