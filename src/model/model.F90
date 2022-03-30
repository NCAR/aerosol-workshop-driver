! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Fortran wrapper for aerosol interface

!> The model_t type and related functions
module aero_model

  use aero_constants,              only : real_kind

  implicit none
  private

  public :: model_t

  type, abstract :: model_t
  contains
    procedure(get_optics), deferred :: get_optics
  end type model_t

interface

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns optical properties on the native aerosol model wavelength grid
  subroutine get_optics( this, optics )

    use aero_constants,             only : real_kind
    import :: model_t

    !> Aerosol model
    class(model_t),       intent(inout) :: this
    !> Calculated optics properties
    real(kind=real_kind), intent(out) :: optics(:)

  end subroutine get_optics

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end interface

end module
