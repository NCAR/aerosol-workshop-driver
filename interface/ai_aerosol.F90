! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Fortran wrapper for aerosol interface

!> The aerosol_t type and related functions
module ai_aerosol

  use ai_constants,                    only : double_kind
  use iso_c_binding

  implicit none
  private

  public :: aerosol_t

  type :: aerosol_t
    type(c_ptr) :: model_
  contains
    procedure :: get_optics
  end type aerosol_t

  interface aerosol_t
    module procedure :: constructor
  end interface

  interface

    !> Builds non-Fortran models
    function ai_build_non_fortran_aerosol( package_name, description_file )   &
        result( aerosol ) bind (c)
      use iso_c_binding
      type(c_ptr)                          :: aerosol
      character(kind=c_char), dimension(*) :: package_name
      character(kind=c_char), dimension(*) :: description_file
    end function ai_build_non_fortran_aerosol

  end interface

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates an aerosol model in another language
  function constructor( package_name, description_file ) result( aerosol )

    type(aerosol_t),  pointer    :: aerosol
    character(len=*), intent(in) :: package_name
    character(len=*), intent(in) :: description_file

    allocate( aerosol )
    aerosol%model_ = ai_build_non_fortran_aerosol(                            &
                        trim( package_name )//c_null_char,                    &
                        trim( description_file )//c_null_char )

  end function constructor

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine get_optics( this, optics )

    !> Aerosol model
    class(aerosol_t),       intent(inout) :: this
    !> Calculated optics properties
    real(kind=double_kind), intent(out)   :: optics(:)

  end subroutine get_optics

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module ai_aerosol
