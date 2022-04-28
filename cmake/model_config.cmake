################################################################################
# Builder function for aerosol model code

function(create_aerosol_model)
  set(prefix MODEL)
  set(singleValues NAME TYPE F90_MODULE HEADER_FILE LIBRARY)
  set(multiValues SOURCE)
  include(CMakeParseArguments)
  cmake_parse_arguments(${prefix} " " "${singleValues}" "${multiValues}" ${ARGN})
  add_library(${MODEL_LIBRARY} "${MODEL_SOURCE}")
  target_link_libraries(${MODEL_LIBRARY} PUBLIC aero)
endfunction(create_aerosol_model)

################################################################################

