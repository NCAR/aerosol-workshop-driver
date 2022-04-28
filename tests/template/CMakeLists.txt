################################################################################
# Test utilities

include(test_util)

################################################################################
# Tests for the model stubs


add_executable(test_c_model_stub my_model.c
                                 my_model_helper.cpp
                                 my_model_helper.F90
                                 ${CMAKE_SOURCE_DIR}/my_model/template/c/my_model.c
                                 ${CMAKE_SOURCE_DIR}/my_model/template/cpp/my_model.cpp
                                 ${CMAKE_SOURCE_DIR}/my_model/template/fortran/my_model.F90)
target_link_libraries(test_c_model_stub PUBLIC aero ${NETCDF_LIBS})
target_include_directories(test_c_model_stub PUBLIC ${CMAKE_SOURCE_DIR}/my_model/template/c)
target_include_directories(test_c_model_stub PUBLIC ${CMAKE_SOURCE_DIR}/my_model/template/cpp)
target_include_directories(test_c_model_stub PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_c_model_stub PUBLIC ${CMAKE_BINARY_DIR}/include)
add_aero_test(c_model_stub test_c_model_stub "")

add_executable(test_cpp_model_stub my_model.cpp
                                   my_model_helper.c
                                   my_model_helper.F90
                                   ${CMAKE_SOURCE_DIR}/my_model/template/c/my_model.c
                                   ${CMAKE_SOURCE_DIR}/my_model/template/cpp/my_model.cpp
                                   ${CMAKE_SOURCE_DIR}/my_model/template/fortran/my_model.F90)
target_link_libraries(test_cpp_model_stub PUBLIC aero ${NETCDF_LIBS})
target_include_directories(test_cpp_model_stub PUBLIC ${CMAKE_SOURCE_DIR}/my_model/template/c)
target_include_directories(test_cpp_model_stub PUBLIC ${CMAKE_SOURCE_DIR}/my_model/template/cpp)
target_include_directories(test_cpp_model_stub PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_cpp_model_stub PUBLIC ${CMAKE_BINARY_DIR}/include)
add_aero_test(cpp_model_stub test_cpp_model_stub "")

add_executable(test_fortran_model_stub my_model.F90
                                       my_model_helper.c
                                       my_model_helper.cpp
                                       ${CMAKE_SOURCE_DIR}/my_model/template/c/my_model.c
                                       ${CMAKE_SOURCE_DIR}/my_model/template/cpp/my_model.cpp
                                       ${CMAKE_SOURCE_DIR}/my_model/template/fortran/my_model.F90)
target_link_libraries(test_fortran_model_stub PRIVATE aero ${NETCDF_LIBS})
target_include_directories(test_fortran_model_stub PUBLIC ${CMAKE_SOURCE_DIR}/my_model/template/c)
target_include_directories(test_fortran_model_stub PUBLIC ${CMAKE_SOURCE_DIR}/my_model/template/cpp)
target_include_directories(test_fortran_model_stub PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_fortran_model_stub PUBLIC ${CMAKE_BINARY_DIR}/include)
add_aero_test(fortran_model_stub test_fortran_model_stub "")

################################################################################
