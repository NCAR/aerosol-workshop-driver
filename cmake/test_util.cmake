################################################################################
# Utility functions for creating tests

find_program(MEMORYCHECK_COMMAND "valgrind")

################################################################################
# build and add a standard test

function(create_standard_test)
  set(prefix TEST)
  set(singleValues NAME)
  set(multiValues SOURCES)
  include(CMakeParseArguments)
  cmake_parse_arguments(${prefix} " " "${singleValues}" "${multiValues}" ${ARGN})
  add_executable(test_${TEST_NAME} ${TEST_SOURCES})
  target_link_libraries(test_${TEST_NAME} PRIVATE aero)
  target_include_directories(test_${TEST_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
  target_include_directories(test_${TEST_NAME} PUBLIC ${CMAKE_BINARY_DIR}/include)
  add_aero_test(${TEST_NAME} test_${TEST_NAME})
endfunction(create_standard_test)

################################################################################
# Add a test

function(add_aero_test test_name test_binary)
  add_test(NAME ${test_name} COMMAND ${test_binary})
  if(MEMORYCHECK_COMMAND)
    set(MEMORYCHECK_COMMAND_OPTIONS "--error-exitcode=1 --trace-children=yes --leak-check=full")
    set(memcheck "${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS}")
    separate_arguments(memcheck)
    add_test(memcheck_${test_name} ${memcheck} ${CMAKE_BINARY_DIR}/${test_binary})
  endif()
endfunction(add_aero_test)

################################################################################
