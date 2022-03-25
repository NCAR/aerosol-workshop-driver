################################################################################
# Aerosol interface source
add_library(ai ai_aerosol.c ai_aerosol.cpp ai_aerosol.F90 ai_bridge.cpp
            ai_state.c ai_grid.c ai_array.c
            ai_state.cpp ai_grid.cpp ai_array.cpp
#            ai_state.F90 ai_grid.F90 ai_array.F90
            ai_constants.F90 ai_util.F90)

################################################################################
