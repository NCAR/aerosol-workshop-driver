! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Array tests

!> The of the array_t class and C/C++ extending classes
program test_array

  use aero_array,                      only : array_t

  implicit none

  call test_array_t( )

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine test_array_t( )

    use aero_constants,                only : rk => real_kind
    use aero_util,                     only : assert

    type(array_t) :: a, b
    real(kind=rk) :: ra(4), rb(4)

    ra = (/ 12.5_rk, 32.6_rk, -132.45_rk, 0.0_rk /)

    a = array_t( ra )
    call assert( 117236040, a%size( ) == 4 )
    call a%copy_out( rb )
    call assert( 454191075, rb(3) == -132.45_rk )
    a = array_t( 4, 32.4_rk )
    call assert( 496689008, a%size( ) == 4 )
    call a%copy_out( rb )
    call assert( 609007353, rb(3) == 32.4_rk )
    a = ra
    call a%copy_out( rb )
    call assert( 772446711, rb(3) == -132.45_rk )

  end subroutine test_array_t

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end program test_array
