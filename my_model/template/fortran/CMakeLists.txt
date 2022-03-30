################################################################################
# Aerosol source code

add_library(my_model my_model.F90 model_factory.F90)

target_link_libraries(my_model PUBLIC aero)

################################################################################
