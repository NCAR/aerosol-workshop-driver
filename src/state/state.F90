! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Aerosol model state

!> The state_t type and related functions
module aero_state

  implicit none
  private

  public :: state_t, state_ptr

  type, abstract :: state_t
  end type state_t

  type :: state_ptr
    class(state_t), pointer :: ptr_ => null( )
  contains
    final :: state_ptr_finalize
  end type state_ptr

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Frees resources associated with a state pointer
  subroutine state_ptr_finalize( this )

    type(state_ptr), intent(inout) :: this

    if( associated( this%ptr_ ) ) deallocate( this%ptr_ )

  end subroutine state_ptr_finalize

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_state
