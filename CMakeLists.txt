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
# floating point precision

if (NOT AERO_PRECISION)
  # double precision by default
  set(AERO_PRECISION "double")
else()
  if (NOT AERO_PRECISION STREQUAL "single" AND
      NOT AERO_PRECISION STREQUAL "double")
    message(FATAL_ERROR "Invalid AERO_PRECISION: ${AERO_PRECISION} (must be single or double)")
  endif()
endif()

if (AERO_PRECISION STREQUAL "single")
  set(AERO_REAL_TYPE "float")
  set(AERO_REAL_KIND "kind(1.0)")
else() # double precision
  set(AERO_REAL_TYPE "double")
  set(AERO_REAL_KIND "kind(1.d0)")
endif()
message(STATUS "Using ${AERO_PRECISION} precision")

################################################################################
# Copy input data

add_custom_target(copy_input_data ALL ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data)

################################################################################
# aerosol model source

if (NOT TESTS_ONLY)
  add_subdirectory(my_model)
endif ()

################################################################################
# aerosol interface library

add_subdirectory(include)
add_subdirectory(src)

# Project-wide include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include)

################################################################################
# mock model driver

add_subdirectory(driver)

################################################################################
# aerosol driver executables

if (NOT TESTS_ONLY)
  add_executable(fortran_driver ${AEROSOL_SRC}
                                ${DRIVER_F90_SRC})

  add_executable(cpp_driver     ${AEROSOL_SRC}
                                ${DRIVER_CPP_SRC})

  add_executable(c_driver       ${AEROSOL_SRC}
                                ${DRIVER_C_SRC})

  foreach (lang fortran cpp c)
    target_link_libraries(${lang}_driver PRIVATE ai)
    target_include_directories(${lang}_driver PUBLIC ${CMAKE_SOURCE_DIR})
    target_include_directories(${lang}_driver PUBLIC ${CMAKE_BINARY_DIR}/my_model)
  endforeach(lang)
endif ()

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
