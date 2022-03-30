! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Implementation of an aerosol model

!> The my_model_t type and related functions
module my_model

  use aero_model,                      only : model_t
  use aero_constants,                  only : real_kind

  implicit none
  private

  public :: my_model_t

  type, extends(model_t) :: my_model_t
  contains
    procedure :: get_optics
  end type my_model_t

  interface my_model_t
    module procedure :: constructor
  end interface

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates and configure the aerosol model
  function constructor( description_file ) result( model )

    type(my_model_t), pointer    :: model
    character(len=*), intent(in) :: description_file

    allocate( model )

  end function constructor

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine get_optics( this, optics )

    !> My aerosol model
    class(my_model_t),    intent(inout) :: this
    !> Calculated optical properties
    real(kind=real_kind), intent(out)   :: optics(:)

  end subroutine get_optics

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module my_model
