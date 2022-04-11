! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file

!> Bridge functions for the array_t type
module aero_grid_bridge

  use aero_grid,                       only : grid_t
  use aero_array,                      only : array_t, array_ptr
  use aero_c_array,                    only : c_array_t
  use aero_cpp_array,                  only : cpp_array_t
  use aero_constants,                  only : real_kind
  use iso_c_binding

  implicit none

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns a pointer to the array of interfaces for the given grid pointer.
  type(c_ptr) function aero_bridge_fortran_grid_interfaces( grid_c_ptr )          &
      result( ifaces_c_ptr ) bind(c)

    type(c_ptr), value, intent(in) :: grid_c_ptr

    type(grid_t),    pointer :: grid_ptr
    type(array_ptr), pointer :: ifaces_ptr

    call c_f_pointer( grid_c_ptr, grid_ptr )
    allocate( ifaces_ptr )
    allocate( ifaces_ptr%ptr_, SOURCE = grid_ptr%interfaces() )
    ifaces_c_ptr = c_loc( ifaces_ptr )

  end function aero_bridge_fortran_grid_interfaces

end module aero_grid_bridge
