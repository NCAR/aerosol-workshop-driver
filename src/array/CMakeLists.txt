# Aerosol array implementations
foreach (src array.c array.cpp array_bridge.cpp)
  list(APPEND array_src ${CMAKE_CURRENT_SOURCE_DIR}/${src})
endforeach()
set(array_src ${array_src} PARENT_SCOPE)
