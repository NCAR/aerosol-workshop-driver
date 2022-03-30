# Aerosol grid implementations
foreach (src grid.c grid.cpp grid_bridge.cpp)
  list(APPEND grid_src ${CMAKE_CURRENT_SOURCE_DIR}/${src})
endforeach()
set(grid_src ${grid_src} PARENT_SCOPE)
