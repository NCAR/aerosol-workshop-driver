# Interpolator implementations
foreach (src interpolator.cpp)
  list(APPEND interpolator_src ${CMAKE_CURRENT_SOURCE_DIR}/${src})
endforeach()
set(interpolator_src ${interpolator_src} PARENT_SCOPE)
