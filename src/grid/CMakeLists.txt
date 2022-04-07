# Aerosol grid implementations
foreach (src grid.c grid.cpp grid.F90 grid_bridge.cpp grid_bridge.F90)
  list(APPEND grid_src ${CMAKE_CURRENT_SOURCE_DIR}/${src})
endforeach()
set(grid_src ${grid_src} PARENT_SCOPE)
