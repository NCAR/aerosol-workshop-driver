################################################################################
# Builder function for aerosol model code

function(create_aerosol_model)
  set(prefix MODEL)
  set(flags " ")
  set(singleValues NAME TYPE F90_MODULE HEADER_FILE SOURCE_DIR LIBRARY)
  set(multiValues SOURCE)
  include(CMakeParseArguments)
  cmake_parse_arguments(${prefix} "${flags}" "${singleValues}" "${multiValues}" ${ARGN})
  message(STATUS "creating aerosol model '${MODEL_NAME}'")
  set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${MODEL_SOURCE_DIR}")
  set(BLD_DIR "${CMAKE_CURRENT_BINARY_DIR}/${MODEL_SOURCE_DIR}")
  generate_factory_source()
  add_library(${MODEL_LIBRARY} ${MODEL_SOURCE}
                               ${BLD_DIR}/model_factory.cpp
                               ${BLD_DIR}/model_factory.F90)
  target_link_libraries(${MODEL_LIBRARY} PUBLIC aero)
  target_include_directories(${MODEL_LIBRARY} PUBLIC ${CMAKE_SOURCE_DIR}/include)
  target_include_directories(${MODEL_LIBRARY} PUBLIC ${SRC_DIR})
endfunction(create_aerosol_model)

################################################################################
# Generate model factory code

macro(generate_factory_source)
  message(STATUS "generating factory code in '${SRC_DIR}'")
  configure_file(
    ${SRC_DIR}/model_factory.F90.in
    ${BLD_DIR}/model_factory.F90
    @ONLY)
  configure_file(
    ${SRC_DIR}/model_factory.cpp.in
    ${BLD_DIR}/model_factory.cpp
    @ONLY)
endmacro()

################################################################################
