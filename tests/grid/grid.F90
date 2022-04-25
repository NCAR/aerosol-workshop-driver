! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Grid tests

!> Tests of interoperable grid type with various arrays
program test_grid

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
    use aero_util,                     only : assert, almost_equal

    real(kind=rk)           :: points(11)
    class(array_t), pointer :: interfaces, ifaces, midpts
    type(grid_t)            :: f_grid, c_grid, cpp_grid

    ! Test using native Fortran interfaces
    points = (/ 0.0_rk, 0.1_rk, 0.2_rk, 0.3_rk, 0.4_rk, 0.5_rk, &
                0.6_rk, 0.7_rk, 0.8_rk, 0.9_rk, 1.0_rk /)
    interfaces => array_t( points )
    f_grid = grid_t(interfaces)
    ifaces => f_grid%interfaces()
    midpts => f_grid%midpoints()
    call assert( 535729854, ifaces%size() == 11)
    call assert( 535729853, midpts%size() == 10)
    call assert( 535729852, almost_equal( f_grid%lower_bound(), 0._rk ) )
    call assert( 535729851, almost_equal( f_grid%upper_bound(), 1._rk ) )

    ! Now use C grid interfaces
    interfaces => c_array_t( test_grid_create_c_interfaces( ), .true. )
    c_grid = grid_t(interfaces)
    ifaces => c_grid%interfaces()
    midpts => c_grid%midpoints()
    call assert( 635729854, ifaces%size() == 11)
    call assert( 635729853, midpts%size() == 10)
    call assert( 635729852, almost_equal( c_grid%lower_bound(), 0._rk ) )
    call assert( 635729851, almost_equal( c_grid%upper_bound(), 1._rk ) )

    ! Now use C++ grid interfaces
    interfaces => cpp_array_t( test_grid_create_cpp_interfaces( ), .true. )
    cpp_grid = grid_t(interfaces)
    ifaces => cpp_grid%interfaces()
    midpts => cpp_grid%midpoints()
    call assert( 735729854, ifaces%size() == 11)
    call assert( 735729853, midpts%size() == 10)
    call assert( 735729852, almost_equal( cpp_grid%lower_bound(), 0._rk ) )
    call assert( 735729851, almost_equal( cpp_grid%upper_bound(), 1._rk ) )

  end subroutine test_grid_t

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end program test_grid
