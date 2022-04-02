################################################################################
# Tests for the Array class

add_executable(test_fortran_array array.F90 array_fortran.c array_fortran.cpp)
target_link_libraries(test_fortran_array PRIVATE aero)
target_include_directories(test_fortran_array PUBLIC ${CMAKE_SOURCE_DIR}/include)
add_test(NAME fortran_array COMMAND test_fortran_array)

add_executable(test_c_array array.c array_c.F90 array_fortran.cpp)
target_link_libraries(test_c_array PRIVATE aero)
target_include_directories(test_c_array PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_c_array PUBLIC ${CMAKE_BINARY_DIR}/include)
add_test(NAME c_array COMMAND test_c_array)

add_executable(test_cpp_array array.cpp array_c.F90)
target_link_libraries(test_cpp_array PRIVATE aero)
target_include_directories(test_cpp_array PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_cpp_array PUBLIC ${CMAKE_BINARY_DIR}/include)
add_test(NAME cpp_array COMMAND test_cpp_array)

################################################################################
