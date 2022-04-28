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
                     SOURCE fortran/my_model.F90
                            fortran/model_factory.cpp
                            fortran/model_factory.F90)

create_aerosol_model(NAME "my model"
                     TYPE MyModel
                     HEADER_FILE cpp/my_model.hpp
                     LIBRARY my_model_cpp_stub
                     SOURCE cpp/my_model.cpp
                            cpp/model_factory.cpp
                            cpp/model_factory.F90)

create_aerosol_model(NAME "my model"
                     HEADER_FILE c/my_model.h
                     LIBRARY my_model_c_stub
                     SOURCE c/my_model.c
                            c/model_factory.cpp
                            c/model_factory.F90)

foreach (language fortran cpp c)
  target_include_directories(my_model_${language}_stub PUBLIC
                             ${CMAKE_SOURCE_DIR}/include)
  target_include_directories(my_model_${language}_stub PUBLIC
                             ${CMAKE_CURRENT_SOURCE_DIR}/${language})
endforeach()

################################################################################
