################################################################################
# Aerosol interface classes

add_subdirectory(aerosol)
add_subdirectory(array)
add_subdirectory(grid)
add_subdirectory(state)

################################################################################
# Aerosol interface library

add_library(aero ai_constants.F90 ai_util.F90
            ${AEROSOL_SRC}
            ${ARRAY_SRC}
            ${GRID_SRC}
            ${STATE_SRC})

target_include_directories(aero PUBLIC ${CMAKE_SOURCE_DIR}/include)

################################################################################
