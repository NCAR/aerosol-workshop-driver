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
  use iso_c_binding

  implicit none

  ! c support functions
  interface
    type(c_ptr) function test_array_create_c_array() bind(c)
      use iso_c_binding
    end function test_array_create_c_array
  end interface

  ! cpp support functions
  interface
    type(c_ptr) function test_array_create_cpp_array() bind(c)
      use iso_c_binding
    end function test_array_create_cpp_array
  end interface

  call test_array_t( )

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine test_array_t( )

    use aero_constants,                only : rk => real_kind
    use aero_util,                     only : assert, almost_equal

    class(array_t), pointer :: a, b
    real(kind=rk) :: ra(4), rb(4)
    real(kind=rk), pointer :: rp(:)

    ra = (/ 12.5_rk, 32.6_rk, -132.45_rk, 0.0_rk /)

    a => array_t( ra )
    call assert( 117236040, a%size( ) == 4 )
    call a%copy_out( rb )
    call assert( 454191075, almost_equal( rb(3), -132.45_rk ) )
    deallocate( a )
    a => array_t( 4, 32.4_rk )
    call assert( 496689008, a%size( ) == 4 )
    call a%copy_out( rb )
    call assert( 609007353, almost_equal( rb(3), 32.4_rk ) )
    call a%copy_in( ra )
    call a%copy_out( rb )
    call assert( 772446711, almost_equal( rb(3), -132.45_rk ) )
    b => a%clone()
    call assert( 865135504, almost_equal( rb(3), -132.45_rk ) )
    rp => b%data()
    call assert( 418683137, almost_equal( rp(3), -132.45_rk ) )
    deallocate( a )
    deallocate( b )

    ! c array
    a => c_array_t( test_array_create_c_array( ), owns_array = .true. )
    call assert( 389444235, a%size( ) == 4 )
    call a%copy_out( rb )
    call assert( 378915621, almost_equal( rb(3), 0.523_rk ) )
    call a%copy_in( ra )
    call a%copy_out( rb )
    call assert( 717776190, almost_equal( rb(3), -132.45_rk ) )
    b => a%clone( )
    rb(:) = 0.0_rk
    call b%copy_out( rb )
    call assert( 368839302, almost_equal( rb(3), -132.45_rk ) )
    rp => b%data()
    call assert( 890250635, almost_equal( rp(3), -132.45_rk ) )
    deallocate( a )
    deallocate( b )

    ! cpp array
    a => cpp_array_t( test_array_create_cpp_array( ), owns_array = .true. )
    call assert( 437330843, a%size( ) == 4 )
    call a%copy_out( rb )
    call assert( 267173939, almost_equal( rb(3), -1.0e9_rk ) )
    call a%copy_in( ra )
    call a%copy_out( rb )
    call assert( 714541785, almost_equal( rb(3), -132.45_rk ) )
    b => a%clone( )
    rb(:) = 0.0_rk
    call b%copy_out( rb )
    call assert( 544384881, almost_equal( rb(3), -132.45_rk ) )
    rp => b%data()
    call assert( 444788323, almost_equal( rp(3), -132.45_rk ) )
    deallocate( a )
    deallocate( b )

  end subroutine test_array_t

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end program test_array
