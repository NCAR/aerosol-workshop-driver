cmake_minimum_required(VERSION 3.12)
project(aerosol-radiation)
enable_language(Fortran)
enable_language(CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 11)

################################################################################
# options

################################################################################
# Copy input data

add_custom_target(copy_input_data ALL ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data)

################################################################################
# aerosol model source

add_subdirectory(src)

################################################################################
# aerosol interface

add_subdirectory(interface)

################################################################################
# mock model driver

add_subdirectory(driver)

################################################################################
# aerosol driver executables

add_executable(fortran_driver ${AEROSOL_SRC}
                              ${DRIVER_F90_SRC})

add_executable(cpp_driver     ${AEROSOL_SRC}
                              ${DRIVER_CPP_SRC})

add_executable(c_driver       ${AEROSOL_SRC}
                              ${DRIVER_C_SRC})

foreach (lang fortran cpp c)
  target_link_libraries(${lang}_driver PRIVATE ai)
  target_include_directories(${lang}_driver PUBLIC ${CMAKE_SOURCE_DIR})
  target_include_directories(${lang}_driver PUBLIC ${CMAKE_BINARY_DIR}/interface)
  target_include_directories(${lang}_driver PUBLIC ${CMAKE_BINARY_DIR}/src)
endforeach(lang)

################################################################################
# tests built from template code

enable_testing()

add_subdirectory(template)

add_executable(test_fortran_aero_fortran_driver ${TEMPLATE_F90_SRC}
                                                ${DRIVER_F90_SRC})

add_executable(test_fortran_aero_cpp_driver     ${TEMPLATE_F90_SRC}
                                                ${DRIVER_CPP_SRC})

add_executable(test_fortran_aero_c_driver       ${TEMPLATE_F90_SRC}
                                                ${DRIVER_C_SRC})

add_executable(test_cpp_aero_fortran_driver     ${TEMPLATE_CPP_SRC}
                                                ${DRIVER_F90_SRC})

add_executable(test_cpp_aero_cpp_driver         ${TEMPLATE_CPP_SRC}
                                                ${DRIVER_CPP_SRC})

add_executable(test_cpp_aero_c_driver           ${TEMPLATE_CPP_SRC}
                                                ${DRIVER_C_SRC})

add_executable(test_c_aero_fortran_driver       ${TEMPLATE_C_SRC}
                                                ${DRIVER_F90_SRC})

add_executable(test_c_aero_cpp_driver           ${TEMPLATE_C_SRC}
                                                ${DRIVER_CPP_SRC})

add_executable(test_c_aero_c_driver             ${TEMPLATE_C_SRC}
                                                ${DRIVER_C_SRC})


foreach (model_lang fortran cpp c)
  foreach (driver_lang fortran cpp c)
    set (test_name ${model_lang}_aero_${driver_lang}_driver)
    set (driver_name test_${test_name})

    # Set link libraries and include directories
    target_link_libraries(${driver_name} PRIVATE ai)
    target_include_directories(${driver_name} PUBLIC ${CMAKE_SOURCE_DIR})
    target_include_directories(${driver_name} PUBLIC ${CMAKE_BINARY_DIR}/interface)
    target_include_directories(${driver_name} PUBLIC ${CMAKE_BINARY_DIR}/template)

    # Add tests to the test suite
    add_test(NAME ${test_name} COMMAND ${driver_name} "my aerosol" none)
  endforeach()
endforeach()

################################################################################
