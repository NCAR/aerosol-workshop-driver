! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file

!> The array_t type and related functions
module aero_array

  use aero_constants,                  only : real_kind

  implicit none
  private

  public :: array_t

  type :: array_t
    private
    real(kind=real_kind), allocatable :: data_(:)
  contains
    procedure, pass(to) :: copy_in
    generic :: assignment(=) => copy_in
    procedure, pass(from) :: copy_out
    procedure :: size => array_size
  end type array_t

  interface array_t
    module procedure :: constructor
    module procedure :: constructor_array
  end interface

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates an Array object from a number of elements and an initial value
  function constructor( number_of_elements, initial_value ) result( array )

    type(array_t)                              :: array
    integer,              intent(in)           :: number_of_elements
    real(kind=real_kind), intent(in), optional :: initial_value

    allocate( array%data_( number_of_elements ) )
    if( present( initial_value ) ) then
      array%data_(:) = initial_value
    else
      array%data_(:) = 0.0
    end if

  end function constructor

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates an Array based on the shape and values of a primitive type array
  function constructor_array( from_array ) result( array )

    type(array_t)                    :: array
    real(kind=real_kind), intent(in) :: from_array(:)

    array%data_ = from_array

  end function constructor_array

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Copies data into an Array
  subroutine copy_in( to, from )

    class(array_t),       intent(inout) :: to
    real(kind=real_kind), intent(in)    :: from(:)

    to%data_(:) = from(:)

  end subroutine copy_in

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Copies data out of an Array
  subroutine copy_out( to, from )

    real(kind=real_kind), intent(inout) :: to(:)
    class(array_t),       intent(in)    :: from

    to(:) = from%data_(:)

  end subroutine copy_out

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns the number of elements in an Array
  integer function array_size( this )

    class(array_t), intent(in) :: this

    array_size = 0
    if( allocated( this%data_ ) ) then
      array_size = size( this%data_ )
    end if

  end function array_size

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_array
