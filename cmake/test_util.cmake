################################################################################
# Utility functions for creating tests

################################################################################
# build and add a standard test

function(create_standard_test test_name test_src)
  add_executable(test_${test_name} ${test_src})
  target_link_libraries(test_${test_name} PRIVATE aero)
  target_include_directories(test_${test_name} PUBLIC ${CMAKE_SOURCE_DIR}/include)
  target_include_directories(test_${test_name} PUBLIC ${CMAKE_BINARY_DIR}/include)
  add_aero_test(${test_name} test_${test_name})
endfunction(create_standard_test)

################################################################################
# Add a test

function(add_aero_test test_name test_binary)
  add_test(NAME ${test_name} COMMAND ${test_binary})
  find_program(MEMORYCHECK_COMMAND "valgrind")
  if(MEMORYCHECK_COMMAND)
    set(MEMORYCHECK_COMMAND_OPTIONS "--error-exitcode=1 --trace-children=yes --leak-check=full")
    set(memcheck "${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS}")
    separate_arguments(memcheck)
    add_test(memcheck_${test_name} ${memcheck} ${CMAKE_BINARY_DIR}/${test_binary})
  endif()
endfunction(add_aero_test)

################################################################################
