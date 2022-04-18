cmake_minimum_required(VERSION 3.12)
project(aerosol-radiation)
enable_language(Fortran)
enable_language(CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

################################################################################
# options

option(AERO_TESTS_ONLY "Build only tests (ignores code in src/)" OFF)

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
  set(AERO_C_EPSILON "FLT_EPSILON")
else() # double precision
  set(AERO_REAL_TYPE "double")
  set(AERO_REAL_KIND "kind(1.d0)")
  set(AERO_C_EPSILON "DBL_EPSILON")
endif()
message(STATUS "Using ${AERO_PRECISION} precision")

################################################################################
# Copy input data

add_custom_target(copy_input_data ALL ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data)

################################################################################
# aerosol model source

# Project-wide include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/src)

if (NOT AERO_TESTS_ONLY)
  add_subdirectory(my_model)
endif ()
add_subdirectory(my_model/template)

################################################################################
# aerosol interface library

add_subdirectory(include)
add_subdirectory(src)

################################################################################
# mock model driver and tests

enable_testing()
add_subdirectory(driver)
add_subdirectory(tests)
