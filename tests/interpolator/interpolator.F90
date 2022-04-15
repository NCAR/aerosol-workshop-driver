! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Array tests

!> The of the interpolator_t class
program test_interpolator

  use aero_interpolator,               only : interpolator_t

  implicit none

  call test_interpolator_t( )

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine test_interpolator_t( )

    use aero_array,                    only : array_t
    use aero_constants,                only : rk => real_kind
    use aero_grid,                     only : grid_t

    class(array_t), pointer :: from_interfaces, to_interfaces
    class(array_t), pointer :: from_data, to_data
    type(grid_t) :: from_grid, to_grid
    type(interpolator_t) :: interp
    real(kind=rk), pointer :: to_a(:)

    from_interfaces => array_t( (/ 1.0_rk, 11.0_rk, 51.0_rk, 61.0_rk /) )
    to_interfaces   => array_t( (/ 0.0_rk,  6.0_rk, 11.0_rk, 56.0_rk,         &
                                  57.0_rk /) )
    from_data       => array_t( (/ 5.0_rk, 10.0_rk, 2.0_rk /) )
    to_data         => array_t( 4, 0.0 )

    from_grid = grid_t( from_interfaces )
    to_grid   = grid_t(   to_interfaces )

    interp = interpolator_t( from_grid, to_grid )
    call interp%interpolate( from_data, to_data )
    to_a => to_data%data( )
    call assert( 843705688, to_a(1) .eq. 2.5 )
    call assert( 615710225, to_a(2) .eq. 2.5 )
    call assert( 163078072, to_a(3) .eq. 11.0 )
    call assert( 957929567, to_a(4) .eq. 0.2 )

    deallocate( from_data )
    deallocate(   to_data )

  end subroutine test_interpolator_t

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end program test_interpolator
