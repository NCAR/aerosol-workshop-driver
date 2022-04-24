# Aerosol model implementations
foreach (src c_model.F90
             cpp_model.F90
             model.F90
             model_bridge.cpp)
  list(APPEND model_src ${CMAKE_CURRENT_SOURCE_DIR}/${src})
endforeach()
set(model_src ${model_src} PARENT_SCOPE)

