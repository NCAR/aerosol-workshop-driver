################################################################################
# Test utilities

include(test_util)

################################################################################
# Tests for the model stubs

create_standard_test( NAME fortran_model_stub SOURCES my_model.F90
                      ${CMAKE_SOURCE_DIR}/my_model/template/fortran/my_model.F90)

add_executable(test_c_model_stub my_model.c
                                 ${CMAKE_SOURCE_DIR}/my_model/template/c/my_model.c)
target_link_libraries(test_c_model_stub PRIVATE aero)
target_include_directories(test_c_model_stub PUBLIC ${CMAKE_SOURCE_DIR}/my_model/template/c)
target_include_directories(test_c_model_stub PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_c_model_stub PUBLIC ${CMAKE_BINARY_DIR}/include)
add_aero_test(c_model_stub test_c_model_stub "")

add_executable(test_cpp_model_stub my_model.cpp
                                 ${CMAKE_SOURCE_DIR}/my_model/template/cpp/my_model.cpp)
target_link_libraries(test_cpp_model_stub PRIVATE aero)
target_include_directories(test_cpp_model_stub PUBLIC ${CMAKE_SOURCE_DIR}/my_model/template/cpp)
target_include_directories(test_cpp_model_stub PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_cpp_model_stub PUBLIC ${CMAKE_BINARY_DIR}/include)
add_aero_test(cpp_model_stub test_cpp_model_stub "")

################################################################################
