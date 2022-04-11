! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file

!> Support functions for C/C++ grid tests
module test_grid_helper

  use aero_array,                      only : array_t, array_ptr
  use iso_c_binding

  implicit none

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates a Fortran array of grid interfaces
  type(c_ptr) function test_grid_create_fortran_interfaces()                      &
      result( array_c_ptr ) bind(c)

    use aero_constants,                only : rk => real_kind

    type(array_ptr), pointer :: array
    real(kind=rk) :: ra(11)

    ra = (/ 0.0_rk, 0.1_rk, 0.2_rk, 0.3_rk, 0.4_rk, 0.5_rk, &
            0.6_rk, 0.7_rk, 0.8_rk, 0.9_rk, 1.0_rk/)
    allocate( array )
    array%ptr_ => array_t( ra )
    array_c_ptr = c_loc( array )

  end function test_grid_create_fortran_interfaces

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module test_grid_helper
