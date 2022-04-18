################################################################################
# Tests for the Interpolator class

add_executable(test_fortran_interpolator interpolator.c)
target_link_libraries(test_fortran_interpolator PRIVATE aero)
target_include_directories(test_fortran_interpolator PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_fortran_interpolator PUBLIC ${CMAKE_BINARY_DIR}/include)
add_test(NAME fortran_interpolator COMMAND test_fortran_interpolator)

add_executable(test_c_interpolator interpolator.c)
target_link_libraries(test_c_interpolator PRIVATE aero)
target_include_directories(test_c_interpolator PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_c_interpolator PUBLIC ${CMAKE_BINARY_DIR}/include)
add_test(NAME c_interpolator COMMAND test_c_interpolator)

add_executable(test_cpp_interpolator interpolator.cpp)
target_link_libraries(test_cpp_interpolator PRIVATE aero)
target_include_directories(test_cpp_interpolator PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_cpp_interpolator PUBLIC ${CMAKE_BINARY_DIR}/include)
add_test(NAME cpp_interpolator COMMAND test_cpp_interpolator)

################################################################################
