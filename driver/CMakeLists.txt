################################################################################
# utility functions

# Sets suffix based on the given language string (fortran, cpp, c).
function(get_suffix_from_language language suffix)
  if (language STREQUAL "fortran")
    set(${suffix} "F90" PARENT_SCOPE)
  else()
    set(${suffix} ${language} PARENT_SCOPE) # suffix is same as language string
  endif()
endfunction()

# Sets template_src to the template source for a given language
function(get_template_source_from_language language template_src)
  if (language STREQUAL "fortran")
    set(${template_src} "${TEMPLATE_F90_SRC}" PARENT_SCOPE)
  elseif (language STREQUAL "cpp")
    set(${template_src} "${TEMPLATE_CPP_SRC}" PARENT_SCOPE)
  elseif (language STREQUAL "c")
    set(${template_src} "${TEMPLATE_C_SRC}" PARENT_SCOPE)
  endif()
endfunction()

################################################################################
# model drivers built from my_model/ code

if (NOT AERO_TESTS_ONLY)
  foreach (lang fortran cpp c)
    get_suffix_from_language(${lang} suffix)
    add_executable(${lang}_driver compute_aero_optics.${suffix})
    target_link_libraries(${lang}_driver PRIVATE ${AERO_MODEL_LIB_NAME})
    target_include_directories(${lang}_driver PUBLIC ${CMAKE_SOURCE_DIR})
    target_include_directories(${lang}_driver PUBLIC ${CMAKE_SOURCE_DIR}/my_model)
    target_include_directories(${lang}_driver PUBLIC ${CMAKE_BINARY_DIR}/my_model)
  endforeach(lang)

  # Make sure the Fortran driver is linked using Fortran's linker.
  set_target_properties(fortran_driver PROPERTIES LINKER_LANGUAGE "Fortran")
endif()

################################################################################
# tests built from template code

if (AERO_TESTS_ONLY)
  include(test_util)

  foreach (model_lang fortran cpp c)
    foreach (driver_lang fortran cpp c)
      # Define test executables.
      get_suffix_from_language(${driver_lang} suffix)
      set (test_name ${model_lang}_aero_${driver_lang}_driver)
      set(driver_name test_${test_name})
      get_template_source_from_language(${model_lang} template_src)
      add_executable(${driver_name} compute_aero_optics.${suffix} ${template_src})
      target_link_libraries(${driver_name} PRIVATE my_model_${model_lang}_stub)
      target_include_directories(${driver_name} PUBLIC ${CMAKE_SOURCE_DIR})
      target_include_directories(${driver_name} PUBLIC ${CMAKE_BINARY_DIR}/my_model/template)

      # Add tests to the test suite
      set(driver_args [[my model]] "../../aerosol/my_model/template/${model_lang}/my_model_data.nc")
      add_aero_test(${test_name} ${driver_name} "${driver_args}")

      # Make sure the Fortran drivers are linked using Fortran's linker.
      if (driver_lang STREQUAL "Fortran")
        set_target_properties(${driver_name} PROPERTIES LINKER_LANGUAGE "Fortran")
      endif()
    endforeach()
  endforeach()
endif()

