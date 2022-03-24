! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Implementation of an aerosol model

!> The my_aerosol_t type and related functions
module my_aerosol

  use ai_aerosol,                      only : aerosol_t
  use ai_constants,                    only : double_kind

  implicit none
  private

  public :: my_aerosol_t

  type, extends(aerosol_t) :: my_aerosol_t
  contains
    procedure :: get_optics
  end type my_aerosol_t

  interface my_aerosol_t
    module procedure :: constructor
  end interface

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates and configure the aerosol model
  function constructor( description_file ) result( aerosol )

    type(my_aerosol_t), pointer    :: aerosol
    character(len=*),   intent(in) :: description_file

    allocate( aerosol )

  end function constructor

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine get_optics( this, optics )

    !> My aerosol model
    class(my_aerosol_t),    intent(inout) :: this
    !> Calculated optical properties
    real(kind=double_kind), intent(out)   :: optics(:)

  end subroutine get_optics

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module my_aerosol
