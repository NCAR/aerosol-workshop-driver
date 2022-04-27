# Aerosol state implementations
foreach (src c_state.cpp
             fortran_state.cpp
             state.F90
             state_bridge.cpp
             state_bridge.F90)
  list(APPEND state_src ${CMAKE_CURRENT_SOURCE_DIR}/${src})
endforeach()
set(state_src ${state_src} PARENT_SCOPE)

