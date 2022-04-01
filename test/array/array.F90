! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Array tests

!> The of the array_t class and C/C++ extending classes
program test_array

  use aero_array,                      only : array_t
  use aero_c_array,                    only : c_array_t
  use iso_c_binding

  implicit none

  ! c support functions
  interface
    type(c_ptr) function test_array_create_c_array() bind(c)
      use iso_c_binding
    end function test_array_create_c_array
  end interface

  call test_array_t( )

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine test_array_t( )

    use aero_constants,                only : rk => real_kind
    use aero_util,                     only : assert

    class(array_t), pointer :: a, b
    real(kind=rk) :: ra(4), rb(4)

    ra = (/ 12.5_rk, 32.6_rk, -132.45_rk, 0.0_rk /)

    a => array_t( ra )
    call assert( 117236040, a%size( ) == 4 )
    call a%copy_out( rb )
    call assert( 454191075, rb(3) == -132.45_rk )
    deallocate( a )
    a => array_t( 4, 32.4_rk )
    call assert( 496689008, a%size( ) == 4 )
    call a%copy_out( rb )
    call assert( 609007353, rb(3) == 32.4_rk )
    call a%copy_in( ra )
    call a%copy_out( rb )
    call assert( 772446711, rb(3) == -132.45_rk )
    b => a%clone()
    call assert( 865135504, rb(3) == -132.45_rk )
    deallocate( a )
    deallocate( b )

    ! c array
    a => c_array_t( test_array_create_c_array( ) )
    call assert( 389444235, a%size( ) == 4 )
    call a%copy_out( rb )
    call assert( 378915621, rb(3) == 0.523_rk )
    call a%copy_in( ra )
    call a%copy_out( rb )
    call assert( 717776190, rb(3) == -132.45_rk )
    b => a%clone( )
    rb(:) = 0.0_rk
    call b%copy_out( rb )
    call assert( 368839302, rb(3) == -132.45_rk )
    deallocate( a )
    deallocate( b )

  end subroutine test_array_t

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end program test_array
