! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Builder of aerosol model objects

!> The create_model and related functions
module aero_model_factory

  use aero_model,                      only : model_t
  use aero_c_model,                    only : c_model_t
  use aero_cpp_model,                  only : cpp_model_t
  use my_model,                        only : my_model_t

  implicit none
  private

  public :: create_model, is_fortran_model, create_fortran_model

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Builder of all-language aerosol model objects
  function create_model( package_name, description_file ) result( model )

    use ai_util,                       only : die_msg

    class(model_t), pointer      :: model
    character(len=*), intent(in) :: package_name
    character(len=*), intent(in) :: description_file

    if( trim( package_name ) == "my model" ) then
      model => my_model_t( description_file )
      return
    end if
    model => c_model_t( package_name, description_file )
    if( .not. associated( model ) ) then
      model => cpp_model_t( package_name, description_file )
    endif
    if( .not. associated( model ) ) then
      call die_msg( 743895691, "Aerosol package '"//package_name//            &
                               "'not supported" )
    end if

  end function create_model

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns whether an aerosol model is supported in Fortran
  pure logical function is_fortran_model( package_name )

    character(len=*), intent(in) :: package_name

    is_fortran_model = .false.
    if( trim( package_name ) == "my model" ) is_fortran_model = .true.

  end function is_fortran_model

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Builder of Fortran aerosol model objects
  function create_fortran_model( package_name, description_file )             &
      result( model )

    use ai_util,                       only : die_msg

    class(model_t),   pointer    :: model
    character(len=*), intent(in) :: package_name
    character(len=*), intent(in) :: description_file

    if( trim( package_name ) == "my model" ) then
      model => my_model_t( description_file )
      return
    end if
    call die_msg( 611497899, "Aerosol package '"//package_name//              &
                             "'not supported in Fortran" )

  end function create_fortran_model

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_model_factory
