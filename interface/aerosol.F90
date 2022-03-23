! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Fortran wrapper for aerosol interface

!> The aerosol_t type and related functions
module ai_aerosol

  use ai_constants,                    only : double_kind

  implicit none
  private

  public :: aerosol_t

  type :: aerosol_t
  contains
    procedure :: get_optics
  end type aerosol_t

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine get_optics( this, optics )

    !> Aerosol model
    class(aerosol_t),       intent(inout) :: this
    !> Calculated optics properties
    real(kind=double_kind), intent(out)   :: optics(:)

  end subroutine get_optics

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module ai_aerosol
