! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Fortran wrapper for aerosol models in C++

!> The cpp_model_t type and related functions
module aero_cpp_model

  use aero_model,                      only : model_t
  use aero_constants,                  only : real_kind
  use iso_c_binding

  implicit none
  private

  public :: cpp_model_t

  type, extends(model_t) :: cpp_model_t
    type(c_ptr) :: model_
  contains
    procedure :: get_optics
  end type cpp_model_t

  interface cpp_model_t
    module procedure :: constructor
  end interface

  interface

    !> Returns whether a C++ aerosol model is supported
    function aero_bridge_cpp_supports_model( package_name )   &
        result( exists ) bind (c)
      use iso_c_binding
      logical(kind=c_bool)                 :: exists
      character(kind=c_char), dimension(*) :: package_name
    end function aero_bridge_cpp_supports_model

    !> Builds a C++ aerosol model
    function aero_bridge_cpp_new_model( package_name, description_file )   &
        result( model ) bind (c)
      use iso_c_binding
      type(c_ptr)                          :: model
      character(kind=c_char), dimension(*) :: package_name
      character(kind=c_char), dimension(*) :: description_file
    end function aero_bridge_cpp_new_model

  end interface

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates a C++ aerosol model
  !!
  !! If the model is not a supported model in C++, a null pointer is returned
  function constructor( package_name, description_file ) result( model )

    type(cpp_model_t),  pointer    :: model
    character(len=*),   intent(in) :: package_name
    character(len=*),   intent(in) :: description_file

    if( aero_bridge_cpp_supports_model( trim( package_name )//c_null_char ) ) &
      then
      allocate( model )
      model%model_ = aero_bridge_cpp_new_model(                             &
                       trim( package_name )//c_null_char,                    &
                       trim( description_file )//c_null_char )
    else
      model => null( )
    end if

  end function

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine get_optics( this, optics )

    !> Aerosol model
    class(cpp_model_t),   intent(inout) :: this
    !> Calculated optics properties
    real(kind=real_kind), intent(out)   :: optics(:)

  end subroutine

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module
