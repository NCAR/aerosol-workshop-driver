! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Implementation of an aerosol model

!> The my_aerosol_t type and related functions
module my_aerosol

  use ai_constants,                    only : double_kind

  implicit none
  private

  public :: my_aerosol_t

  type :: my_aerosol_t
  contains
    procedure :: get_optics
  end type my_aerosol_t

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine get_optics( this, optics )

    !> My aerosol model
    class(my_aerosol_t),    intent(inout) :: this
    !> Calculated optical properties
    real(kind=double_kind), intent(out)   :: optics(:)

  end subroutine get_optics

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module my_aerosol
