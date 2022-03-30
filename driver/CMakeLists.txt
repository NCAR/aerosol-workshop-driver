# Sets suffix based on the given language string (fortran, cpp, c).
function(get_suffix_from_language language suffix)
  if (language STREQUAL "fortran")
    set(${suffix} "F90" PARENT_SCOPE)
  else()
    set(${suffix} ${language} PARENT_SCOPE) # suffix is same as language string
  endif()
endfunction()

if (NOT AERO_TESTS_ONLY)
  foreach (lang fortran cpp c)
    get_suffix_from_language(${lang} suffix)
    add_executable(${lang}_driver compute_aero_optics.${suffix})
    target_link_libraries(${lang}_driver PRIVATE my_model aero)
    target_include_directories(${lang}_driver PUBLIC ${CMAKE_SOURCE_DIR})
    target_include_directories(${lang}_driver PUBLIC ${CMAKE_BINARY_DIR}/my_model)
  endforeach(lang)
endif ()

################################################################################
# tests built from template code

enable_testing()

foreach (model_lang fortran cpp c)
  foreach (driver_lang fortran cpp c)
    # Define test executables.
    get_suffix_from_language(${driver_lang} suffix)
    set (test_name ${model_lang}_aero_${driver_lang}_driver)
    set(driver_name test_${test_name})
    add_executable(${driver_name} compute_aero_optics.${suffix})
    target_link_libraries(${driver_name} PRIVATE
                          my_aerosol_${model_lang}_stub aero)
    target_include_directories(${driver_name} PUBLIC ${CMAKE_SOURCE_DIR})
    target_include_directories(${driver_name} PUBLIC ${CMAKE_BINARY_DIR}/template)

    # Add tests to the test suite
    add_test(NAME ${test_name} COMMAND ${driver_name} "my aerosol" none)
  endforeach()
endforeach()

