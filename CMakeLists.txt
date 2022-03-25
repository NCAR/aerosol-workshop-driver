cmake_minimum_required(VERSION 3.12)
project(aerosol-radiation)
enable_language(Fortran)
enable_language(CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 11)

################################################################################
# options

option(TESTS_ONLY "Build only tests (ignores code in src/)" OFF)

################################################################################
# Copy input data

add_custom_target(copy_input_data ALL ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data)

################################################################################
# aerosol model source

if (NOT TESTS_ONLY)
  add_subdirectory(src)
endif ()

################################################################################
# aerosol interface

add_subdirectory(interface)

################################################################################
# mock model driver

add_subdirectory(driver)

################################################################################
# aerosol driver executables

if (NOT TESTS_ONLY)
  add_executable(fortran_driver ${AEROSOL_SRC}
                                ${INTERFACE_SRC}
                                ${DRIVER_F90_SRC})

  add_executable(cpp_driver     ${AEROSOL_SRC}
                                ${INTERFACE_SRC}
                                ${DRIVER_CPP_SRC})

  add_executable(c_driver       ${AEROSOL_SRC}
                                ${INTERFACE_SRC}
                                ${DRIVER_C_SRC})

  target_include_directories(fortran_driver PUBLIC ${CMAKE_SOURCE_DIR})
  target_include_directories(cpp_driver     PUBLIC ${CMAKE_SOURCE_DIR})
  target_include_directories(c_driver       PUBLIC ${CMAKE_SOURCE_DIR})
endif ()

################################################################################
# tests built from template code

add_subdirectory(template)

add_executable(test_fortran_aero_fortran_driver ${TEMPLATE_F90_SRC}
                                                ${INTERFACE_SRC}
                                                ${DRIVER_F90_SRC})

add_executable(test_fortran_aero_cpp_driver     ${TEMPLATE_F90_SRC}
                                                ${INTERFACE_SRC}
                                                ${DRIVER_CPP_SRC})

add_executable(test_fortran_aero_c_driver       ${TEMPLATE_F90_SRC}
                                                ${INTERFACE_SRC}
                                                ${DRIVER_C_SRC})

add_executable(test_cpp_aero_fortran_driver     ${TEMPLATE_CPP_SRC}
                                                ${INTERFACE_SRC}
                                                ${DRIVER_F90_SRC})

add_executable(test_cpp_aero_cpp_driver         ${TEMPLATE_CPP_SRC}
                                                ${INTERFACE_SRC}
                                                ${DRIVER_CPP_SRC})

add_executable(test_cpp_aero_c_driver           ${TEMPLATE_CPP_SRC}
                                                ${INTERFACE_SRC}
                                                ${DRIVER_C_SRC})

target_include_directories(test_fortran_aero_fortran_driver PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(test_fortran_aero_cpp_driver     PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(test_fortran_aero_c_driver       PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(test_cpp_aero_fortran_driver     PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(test_cpp_aero_cpp_driver         PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(test_cpp_aero_c_driver           PUBLIC ${CMAKE_SOURCE_DIR})

################################################################################
# Add driver executables to test suite

enable_testing()
add_test(NAME fortran_aero_fortran_driver COMMAND test_fortran_aero_fortran_driver my_aerosol none)
add_test(NAME fortran_aero_cpp_driver     COMMAND test_fortran_aero_cpp_driver     my_aerosol none)
add_test(NAME fortran_aero_c_driver       COMMAND test_fortran_aero_c_driver       my_aerosol none)
add_test(NAME cpp_aero_fortran_driver     COMMAND test_cpp_aero_fortran_driver     my_aerosol none)
add_test(NAME cpp_aero_cpp_driver         COMMAND test_cpp_aero_cpp_driver         my_aerosol none)
add_test(NAME cpp_aero_c_driver           COMMAND test_cpp_aero_c_driver           my_aerosol none)

################################################################################
