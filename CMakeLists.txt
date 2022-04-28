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
option(AERO_ENABLE_NETCDF "Enable NetCDF support" ON)

################################################################################
# NetCDF library

if(AERO_ENABLE_NETCDF)
  find_path(NETCDF_INCLUDE_DIR netcdf.mod NETCDF.mod
    DOC "NetCDF include directory (must contain netcdf.mod)"
    PATHS
      $ENV{NETCDF_HOME}/include
      /usr/lib/gfortran/modules
      /usr/lib64/gfortran/modules
      /opt/local/include)
  find_library(NETCDF_C_LIB netcdf
    DOC "NetCDF C library"
    PATHS
      $ENV{NETCDF_HOME}/lib
      $ENV{NETCDF_HOME}/lib64
      /usr/lib
      /usr/lib64
      /opt/local/lib)
  find_library(NETCDF_FORTRAN_LIB netcdff
    DOC "NetCDF Fortran library"
    PATHS
      $ENV{NETCDF_HOME}/lib
      $ENV{NETCDF_HOME}/lib64
      /opt/local/lib)
  set(NETCDF_LIBS ${NETCDF_C_LIB})
  if(NETCDF_FORTRAN_LIB)
    set(NETCDF_LIBS ${NETCDF_LIBS} ${NETCDF_FORTRAN_LIB})
  endif()
  include_directories(${NETCDF_INCLUDE_DIR})
  add_definitions(-DAERO_USE_NETCDF)
endif()

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
else ()
  add_subdirectory(my_model/template)
endif ()

################################################################################
# aerosol interface library

add_subdirectory(include)
add_subdirectory(src)

################################################################################
# mock model driver and tests

enable_testing()
add_subdirectory(driver)
add_subdirectory(tests)
