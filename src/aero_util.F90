! Copyright (C) 2022 National Center for Atmospheric Research,
! National Technology & Engineering Solutions of Sandia, LLC (NTESS),
! and the U.S. Environmental Protection Agency (USEPA)
!
! SPDX-License-Identifier: Apache-2.0
!
module aero_util

  implicit none

  !> Error output id
  integer, parameter :: kErrorId = 0

  interface c_f_string
    module procedure :: c_f_string_char
    module procedure :: c_f_string_ptr
  end interface

  ! c support functions
  interface
    type(c_ptr) function aero_util_offset_pointer( ptr, offset ) bind (c)
      use iso_c_binding
      type(c_ptr), value :: ptr
      integer(kind=c_int), value :: offset
    end function aero_util_offset_pointer
  end interface

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

  !> Errors immediately and prints a generic messgae
  subroutine die( code )

    !> Unique code for the failure
    integer, intent(in) :: code

    call die_msg( code, "Internal error" )

  end subroutine die

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

  !> Converts a c string to a fortran string
  subroutine c_f_string_char( c_str, f_str )

    use iso_c_binding

    character(kind=c_char), dimension(*), intent(in)  :: c_str
    character(len=:),       allocatable,  intent(out) :: f_str

    integer :: i, l_str

    l_str = 0
    do
      if( c_str( l_str + 1 ) == c_null_char ) exit
      l_str = l_str + 1
    end do
    allocate( character(len=l_str) :: f_str )
    do i = 1, l_str
      f_str(i:i) = c_str(i)
    end do

  end subroutine c_f_string_char

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Converts a c string void pointer to a fortran string
  recursive subroutine c_f_string_ptr( c_str_ptr, f_str )

    use iso_c_binding

    type(c_ptr),                    intent(in)  :: c_str_ptr
    character(len=:), allocatable,  intent(out) :: f_str

    integer :: i
    character(kind=c_char), dimension(:), pointer :: c_str
    character(len=256) :: temp_str
    logical :: found_end

    nullify( c_str )
    call c_f_pointer( c_str_ptr, c_str, [256] )
    if( .not. associated( c_str ) ) then
      f_str = ""
      return
    end if

    found_end = .false.
    temp_str = ""
    do i = 1, 256
      if( c_str( i ) == c_null_char ) then
        found_end = .true.
        exit
      end if
      temp_str(i:i) = c_str(i)
    end do
    if( found_end ) then
      f_str = trim( temp_str )
      return
    end if
    call c_f_string_ptr( aero_util_offset_pointer( c_str_ptr, 256 ), f_str )
    f_str = temp_str // f_str

  end subroutine c_f_string_ptr

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_util
