# Aerosol array implementations
foreach (src array.c
             array.cpp
             array.F90
             array_bridge.cpp
             array_bridge.F90
             c_array.F90
             cpp_array.F90
             fortran_array.c)
  list(APPEND array_src ${CMAKE_CURRENT_SOURCE_DIR}/${src})
endforeach()
set(array_src ${array_src} PARENT_SCOPE)
