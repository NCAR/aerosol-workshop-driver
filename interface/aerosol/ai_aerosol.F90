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

  type, abstract :: aerosol_t
  contains
    procedure(get_optics), deferred :: get_optics
  end type aerosol_t

interface

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns optical properties on the native aerosol model wavelength grid
  subroutine get_optics( this, optics )

    use ai_constants,                  only : double_kind
    import :: aerosol_t

    !> Aerosol model
    class(aerosol_t),       intent(inout) :: this
    !> Calculated optics properties
    real(kind=double_kind), intent(out)   :: optics(:)

  end subroutine get_optics

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end interface

end module ai_aerosol
