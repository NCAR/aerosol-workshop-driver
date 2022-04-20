! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Fortran utility functions

!> Fortran utility functions
module aero_util

  implicit none

  !> Error output id
  integer, parameter :: kErrorId = 0

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Errors immediately and prints a provided message
  subroutine die_msg( code, error_message )

    !> Unique code for the failure
    integer, intent(in) :: code
    !> Message to display with failure
    character(len=*), intent(in) :: error_message

    call assert_msg( code, .false., error_message )

  end subroutine die_msg

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Asserts condition to be true or fails
  subroutine assert( code, condition )

    !> Unique code for the assertion
    integer, intent(in) :: code
    !> Condition to evaluate
    logical, intent(in) :: condition

    call assert_msg( code, condition, 'assertion failed' )

  end subroutine assert

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Asserts condition to be true or fails with provided message
  subroutine assert_msg( code, condition, error_message )

    !> Unique code for the assertion
    integer, intent(in) :: code
    !> Condition to evaluate
    logical, intent(in) :: condition
    !> Message to display on failure
    character(len=*), intent(in) :: error_message

    character(len=50) :: str_code

    if( .not. condition ) then
      write(str_code,'(i30)') code
      write(kErrorId,*) "ERROR (Musica-"//trim( adjustl( str_code ) )//"): "  &
                        //error_message
      stop 3
    end if

  end subroutine assert_msg

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Compares two floating point numbers
  !!
  !! If the absolute difference between the numbers is within the given
  !! tolerance, the function returns true, otherwise it returns false
  !!
  !! If no tolerance is provided, a default tolerance based on the precision
  !! of \c real_kind is used.
  pure logical function almost_equal( a, b, tolerance )

    use aero_constants,                only : rk => real_kind

    real(kind=rk), intent(in) :: a
    real(kind=rk), intent(in) :: b
    real(kind=rk), intent(in), optional :: tolerance

    real(kind=rk) :: l_tol

    almost_equal = .true.
    if( a == 0.0_rk .and. b == 0.0_rk ) return
    l_tol = 5.0_rk * epsilon( a )
    if( present( tolerance ) ) l_tol = abs( tolerance )
    if( abs( a - b ) * 2.0_rk / abs( a + b ) < l_tol ) return
    almost_equal = .false.

  end function almost_equal

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_util
