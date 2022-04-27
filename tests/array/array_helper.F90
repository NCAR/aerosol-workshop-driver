! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file

!> Support functions for C/C++ Array tests
module test_array_helper

  use aero_array,                      only : array_t, array_ptr
  use iso_c_binding

  implicit none

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates a Fortran array for use in C Array tests
  type(c_ptr) function test_array_create_fortran_array()                      &
      result( array_c_ptr ) bind(c)

    use aero_constants,                only : rk => real_kind

    type(array_ptr), pointer :: array
    real(kind=rk) :: ra(4)

    ra = (/ 42.5_rk, -132.4_rk, 0.623_rk, 315.32_rk /)
    allocate( array )
    array%ptr_ => array_t( ra )
    array_c_ptr = c_loc( array )

  end function test_array_create_fortran_array

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Checks a Fortran array for a value at a given index
  subroutine test_array_check_fortran_array(f_array, index, value) bind(c)

    use aero_constants,                only : rk => real_kind
    use aero_util,                     only : assert, almost_equal

    type(c_ptr),   value, intent(in) :: f_array
    integer,       value, intent(in) :: index
    real(kind=rk), value, intent(in) :: value

    type(array_ptr), pointer :: array
    real(kind=rk), pointer :: array_data(:)

    call c_f_pointer( f_array, array )
    array_data => array%ptr_%data()
    call assert( 884004656, almost_equal( array_data( index ), value ) )

  end subroutine test_array_check_fortran_array

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module test_array_helper
