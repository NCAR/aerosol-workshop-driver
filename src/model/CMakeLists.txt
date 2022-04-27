# Aerosol model implementations
foreach (src c_model.cpp
             c_model.F90
             cpp_model.c
             cpp_model.F90
             fortran_model.c
             fortran_model.cpp
             model.F90
             model_bridge.cpp
             model_bridge.F90)
  list(APPEND model_src ${CMAKE_CURRENT_SOURCE_DIR}/${src})
endforeach()
set(model_src ${model_src} PARENT_SCOPE)

