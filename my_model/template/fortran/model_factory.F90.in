! Copyright (C) 2022 National Center for Atmospheric Research,
! National Technology & Engineering Solutions of Sandia, LLC (NTESS),
! and the U.S. Environmental Protection Agency (USEPA)
!
! SPDX-License-Identifier: Apache-2.0
!
module aero_model_factory

  use aero_model,                      only : model_t
  use aero_c_model,                    only : c_model_t
  use aero_cpp_model,                  only : cpp_model_t
  use my_model,                        only : my_model_t
  use iso_c_binding

  implicit none
  private

  public :: create_model

interface

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  type(c_ptr) function aero_factory_new_c_model( package_name,                &
      description_file ) bind(c)
    use iso_c_binding
    character(kind=c_char), dimension(*), intent(in) :: package_name
    character(kind=c_char), dimension(*), intent(in) :: description_file
  end function aero_factory_new_c_model

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  type(c_ptr) function aero_factory_new_cpp_model( package_name,              &
      description_file ) bind(c)
    use iso_c_binding
    character(kind=c_char), dimension(*), intent(in) :: package_name
    character(kind=c_char), dimension(*), intent(in) :: description_file
  end function aero_factory_new_cpp_model

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end interface

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Builder of all-language aerosol model objects
  function create_model( package_name, description_file ) result( model )

    use aero_util,                       only : die_msg

    class(model_t),   pointer    :: model
    character(len=*), intent(in) :: package_name
    character(len=*), intent(in) :: description_file

    type(c_ptr) :: c_model_ptr
    character(kind=c_char, len=:), allocatable :: c_name, c_file

    c_name = trim( package_name )//c_null_char
    c_file = trim( description_file )//c_null_char
    if( trim( package_name ) == "my model" ) then
      model => my_model_t( description_file )
      return
    end if
    c_model_ptr = aero_factory_new_c_model( c_name, c_file )
    if( c_associated( c_model_ptr ) ) then
      model => c_model_t( c_model_ptr, owns_model = .true. )
      return
    endif
    c_model_ptr = aero_factory_new_cpp_model( c_name, c_file )
    if( c_associated( c_model_ptr ) ) then
      model => cpp_model_t( c_model_ptr, owns_model = .true. )
      return
    endif
    call die_msg( 743895691, "Aerosol package '"//trim( package_name )//      &
                               "'not supported" )

  end function create_model

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Builder of Fortran aerosol model objects
  type(c_ptr) function aero_factory_new_fortran_model( package_name,          &
      description_file ) result( model ) bind(c)

    use aero_model,                    only : model_ptr
    use aero_util,                     only : c_f_string

    character(kind=c_char), dimension(*), intent(in) :: package_name
    character(kind=c_char), dimension(*), intent(in) :: description_file

    type(model_ptr), pointer :: wrap_model
    character(len=:), allocatable :: f_name, f_file

    call c_f_string( package_name, f_name )
    call c_f_string( description_file, f_file )
    model = c_null_ptr
    if( f_name == "my model" ) then
      allocate( wrap_model )
      wrap_model%ptr_ => my_model_t( f_file )
      model = c_loc( wrap_model )
    end if

  end function aero_factory_new_fortran_model

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_model_factory
