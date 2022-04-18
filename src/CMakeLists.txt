################################################################################
# Aerosol interface classes

add_subdirectory(model)
add_subdirectory(array)
add_subdirectory(grid)
add_subdirectory(interpolator)
add_subdirectory(state)

################################################################################
# Aerosol interface library

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/aero_constants.F90.in
  ${CMAKE_CURRENT_BINARY_DIR}/aero_constants.F90
  @ONLY
)

add_library(aero
            ${CMAKE_CURRENT_BINARY_DIR}/aero_constants.F90
            aero_util.F90
            ${model_src}
            ${array_src}
            ${grid_src}
            ${interpolator_src}
            ${state_src})

target_include_directories(aero PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

################################################################################
