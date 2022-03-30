################################################################################
# Tests for the Array class

add_executable(test_fortran_array array.F90)

target_link_libraries(test_fortran_array PRIVATE aero)
target_include_directories(test_fortran_array PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_test(NAME fortran_array COMMAND test_fortran_array)

################################################################################
