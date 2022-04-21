# Aerosol state implementations
foreach (src state.c state.cpp state.F90 state_bridge.cpp)
  list(APPEND state_src ${CMAKE_CURRENT_SOURCE_DIR}/${src})
endforeach()
set(state_src ${state_src} PARENT_SCOPE)

