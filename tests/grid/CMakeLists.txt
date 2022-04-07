################################################################################
# Tests for the Grid class

#add_executable(test_fortran_grid grid.F90 ../array/array_helper.c ../array/array_helper.cpp)
#target_link_libraries(test_fortran_grid PRIVATE aero)
#target_include_directories(test_fortran_grid PUBLIC ${CMAKE_SOURCE_DIR}/include)
#add_test(NAME fortran_array COMMAND test_fortran_grid)

add_executable(test_c_grid grid.c grid_helper.F90 grid_helper.cpp)
target_link_libraries(test_c_grid PRIVATE aero)
target_include_directories(test_c_grid PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_c_grid PUBLIC ${CMAKE_BINARY_DIR}/include)
add_test(NAME c_grid COMMAND test_c_grid)

add_executable(test_cpp_grid grid.cpp grid_helper.F90)
target_link_libraries(test_cpp_grid PRIVATE aero)
target_include_directories(test_cpp_grid PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_cpp_grid PUBLIC ${CMAKE_BINARY_DIR}/include)
add_test(NAME cpp_grid COMMAND test_cpp_grid)

################################################################################
