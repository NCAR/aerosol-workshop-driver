! Copyright (C) 2022 National Center for Atmospheric Research,
! National Technology & Engineering Solutions of Sandia, LLC (NTESS),
! and the U.S. Environmental Protection Agency (USEPA)
!
! SPDX-License-Identifier: Apache-2.0
!
module aero_state_bridge

  use aero_state,                      only : state_t, state_ptr
  use aero_c_model,                    only : c_state_t
  use aero_cpp_model,                  only : cpp_state_t
  use iso_c_binding

  implicit none

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Frees resources associated wit the given Fortran state
  subroutine aero_bridge_fortran_state_free( state_c_ptr ) bind(c)

    type(c_ptr), value, intent(in) :: state_c_ptr

    type(state_ptr), pointer :: state_ptr

    call c_f_pointer( state_c_ptr, state_ptr )
    deallocate( state_ptr )

  end subroutine aero_bridge_fortran_state_free

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_state_bridge
