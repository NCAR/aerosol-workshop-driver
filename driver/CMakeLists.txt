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

foreach (lang fortran cpp c)
  get_suffix_from_language(${lang} suffix)
  if (EXISTS ${CMAKE_SOURCE_DIR}/my_model/my_model.${suffix})
    # Generate a file that creates the desired model implementation.
    configure_file(
      ${CMAKE_SOURCE_DIR}/my_model/create_model.${suffix}.in
      ${CMAKE_BINARY_DIR}/my_model/create_model.${suffix}
      @ONLY
    )
    add_executable(${lang}_driver compute_aero_optics.${suffix}
                                  ${CMAKE_BINARY_DIR}/my_model/create_model.${suffix})
    target_link_libraries(${lang}_driver PRIVATE my_model)
    target_include_directories(${lang}_driver PUBLIC ${CMAKE_SOURCE_DIR})
    target_include_directories(${lang}_driver PUBLIC ${CMAKE_BINARY_DIR}/my_model)
  endif()
endforeach(lang)

################################################################################
# tests built from template code

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
    add_test(NAME ${test_name} COMMAND ${driver_name} "my model" none)
  endforeach()
endif()

