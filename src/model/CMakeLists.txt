# Aerosol model implementations
foreach (src model.c model.cpp model.F90 model_bridge.cpp c_model.F90
             cpp_model.F90)
  list(APPEND model_src ${CMAKE_CURRENT_SOURCE_DIR}/${src})
endforeach()
set(model_src ${model_src} PARENT_SCOPE)

