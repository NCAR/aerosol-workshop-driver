cmake_minimum_required(VERSION 3.12)
project(aerosol-radiation)
enable_language(Fortran)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

################################################################################
# options

################################################################################
# Copy input data

add_custom_target(copy_input_data ALL ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data)

################################################################################
# aerosol model source

add_subdirectory(src)
include_directories(${CMAKE_BINARY_DIR}/src)

################################################################################
# aerosol interface

add_subdirectory(interface)
include_directories(${CMAKE_BINARY_DIR}/interface)

################################################################################
# mock model driver

add_subdirectory(driver)
include_directories(${CMAKE_BINARY_DIR}/driver)

################################################################################
# aerosol driver executables

add_executable(fortran_driver ${AEROSOL_SRC}
                              ${INTERFACE_SRC}
                              ${DRIVER_F90_SRC})


################################################################################
# Add driver executables to test suite

enable_testing()
add_test(NAME fortran_host_model COMMAND fortran_driver)

################################################################################
