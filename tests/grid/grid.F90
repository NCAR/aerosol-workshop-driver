! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Array tests

!> The of the array_t class and C/C++ extending classes
program test_array

  use aero_array,                      only : array_t
  use aero_c_array,                    only : c_array_t
  use aero_cpp_array,                  only : cpp_array_t
  use aero_grid,                       only : grid_t
  use iso_c_binding

  implicit none

  ! c support functions
  interface
    type(c_ptr) function test_grid_create_c_interfaces() bind(c)
      use iso_c_binding
    end function test_grid_create_c_interfaces
  end interface

  ! cpp support functions
  interface
    type(c_ptr) function test_grid_create_cpp_interfaces() bind(c)
      use iso_c_binding
    end function test_grid_create_cpp_interfaces
  end interface

  call test_grid_t( )

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine test_grid_t( )

    use aero_constants,                only : rk => real_kind
    use aero_util,                     only : assert

    real(kind=rk)           :: points(11)
    class(array_t), pointer :: interfaces
    type(grid_t)            :: f_grid, c_grid, cpp_grid

    ! Test using native Fortran interfaces
    points = (/ 0.0_rk, 0.1_rk, 0.2_rk, 0.3_rk, 0.4_rk, 0.5_rk, &
                0.6_rk, 0.7_rk, 0.8_rk, 0.9_rk, 1.0_rk /)
    interfaces => array_t( points )
    f_grid = grid_t(interfaces)
    call assert( 535729854, f_grid%interfaces%size() == 11)
    call assert( 535729853, f_grid%midpoints%size() == 10)
    call assert( 535729852, abs(f_grid%lower_bound) < epsilon(0._rk))
    call assert( 535729851, abs(f_grid%upper_bound - 1_rk) < epsilon(0._rk))

    ! Now use C grid interfaces
    interfaces => c_array_t( test_grid_create_c_interfaces( ) )
    c_grid = grid_t(interfaces)
    call assert( 635729854, c_grid%interfaces%size() == 11)
    call assert( 635729853, c_grid%midpoints%size() == 10)
    call assert( 635729852, abs(c_grid%lower_bound) < epsilon(0._rk))
    call assert( 635729851, abs(c_grid%upper_bound - 1_rk) < epsilon(0._rk))

    ! Now use C++ grid interfaces
    interfaces => cpp_array_t( test_grid_create_cpp_interfaces( ) )
    cpp_grid = grid_t(interfaces)
    call assert( 735729854, cpp_grid%interfaces%size() == 11)
    call assert( 735729853, cpp_grid%midpoints%size() == 10)
    call assert( 735729852, abs(cpp_grid%lower_bound) < epsilon(0._rk))
    call assert( 735729851, abs(cpp_grid%upper_bound - 1_rk) < epsilon(0._rk))

  end subroutine test_grid_t

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end program test_array
