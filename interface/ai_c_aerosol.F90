! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Fortran wrapper for aerosol models in C

!> The c_aerosol_t type and related functions
module ai_c_aerosol

  use ai_aerosol,                      only : aerosol_t
  use ai_constants,                    only : double_kind
  use iso_c_binding

  implicit none
  private

  public :: c_aerosol_t

  type, extends(aerosol_t) :: c_aerosol_t
    type(c_ptr) :: model_
  contains
    procedure :: get_optics
  end type c_aerosol_t

  interface c_aerosol_t
    module procedure :: constructor
  end interface

  interface

    !> Returns whether a C aerosol model is supported
    function ai_bridge_c_supports_aerosol( package_name )   &
        result( exists ) bind (c)
      use iso_c_binding
      logical(kind=c_bool)                 :: exists
      character(kind=c_char), dimension(*) :: package_name
    end function ai_bridge_c_supports_aerosol

    !> Builds a C aerosol model
    function ai_bridge_c_new_aerosol( package_name, description_file )   &
        result( aerosol ) bind (c)
      use iso_c_binding
      type(c_ptr)                          :: aerosol
      character(kind=c_char), dimension(*) :: package_name
      character(kind=c_char), dimension(*) :: description_file
    end function ai_bridge_c_new_aerosol

  end interface

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates a C aerosol model
  !!
  !! If the model is not a supported model in C, a null pointer is returned
  function constructor( package_name, description_file ) result( aerosol )

    type(c_aerosol_t),  pointer    :: aerosol
    character(len=*),   intent(in) :: package_name
    character(len=*),   intent(in) :: description_file

    if( ai_bridge_c_supports_aerosol( trim( package_name )//c_null_char ) )   &
      then
      allocate( aerosol )
      aerosol%model_ = ai_bridge_c_new_aerosol(                               &
                        trim( package_name )//c_null_char,                    &
                        trim( description_file )//c_null_char )
    else
      aerosol => null( )
    end if

  end function constructor

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine get_optics( this, optics )

    !> Aerosol model
    class(c_aerosol_t),     intent(inout) :: this
    !> Calculated optics properties
    real(kind=double_kind), intent(out)   :: optics(:)

  end subroutine get_optics

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module ai_c_aerosol
