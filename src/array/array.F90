! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file

!> The array_t type and related functions
module aero_array

  use aero_constants,                  only : real_kind

  implicit none
  private

  public :: array_t, array_ptr

  type :: array_t
    private
    real(kind=real_kind), pointer :: data_(:) => null( )
  contains
    procedure, pass(from) :: clone
    procedure, pass(to) :: copy_in
    procedure, pass(from) :: copy_out
    procedure :: data => array_data
    procedure :: size => array_size
    final :: finalize
  end type array_t

  interface array_t
    module procedure :: constructor
    module procedure :: constructor_array
  end interface

  type :: array_ptr
    class(array_t), pointer :: ptr_ => null( )
  contains
    final :: array_ptr_finalize
  end type array_ptr

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates an Array object from a number of elements and an initial value
  function constructor( size, initial_value ) result( array )

    class(array_t),       pointer              :: array
    integer,              intent(in)           :: size
    real(kind=real_kind), intent(in), optional :: initial_value

    allocate( array )
    allocate( array%data_( size ) )
    if( present( initial_value ) ) then
      array%data_(:) = initial_value
    else
      array%data_(:) = 0.0
    end if

  end function constructor

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates an Array based on the shape and values of a primitive type array
  function constructor_array( from_array ) result( array )

    class(array_t),       pointer    :: array
    real(kind=real_kind), intent(in) :: from_array(:)

    allocate( array )
    allocate( array%data_, SOURCE = from_array )

  end function constructor_array

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates a clone (deep-copy) of an array
  function clone( from )

    class(array_t), pointer :: clone
    class(array_t), intent(in) :: from

    select type(from)
    type is(array_t)
      ! for concrete base class, copy data_ from source
      allocate( clone )
      if( associated( from%data_ ) ) then
        allocate( clone%data_, SOURCE = from%data_ )
      end if
    class default
      ! provide default clone functionality for subclasses
      allocate( clone, SOURCE = from )
    end select

  end function clone

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Copies data into an Array
  subroutine copy_in( to, from )

    class(array_t),       intent(inout)        :: to
    real(kind=real_kind), intent(in),   target :: from(:)

    to%data_(:) = from(:)

  end subroutine copy_in

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Copies data out of an Array
  subroutine copy_out( to, from )

    real(kind=real_kind), intent(inout), target :: to(:)
    class(array_t),       intent(in)            :: from

    to(:) = from%data_(:)

  end subroutine copy_out

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns a pointer to the underlying data
  function array_data( this )

    real(kind=real_kind), pointer       :: array_data(:)
    class(array_t),       intent(inout) :: this

    array_data => this%data_

  end function array_data

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns the number of elements in an Array
  integer function array_size( this )

    class(array_t), intent(in) :: this

    array_size = 0
    if( associated( this%data_ ) ) then
      array_size = size( this%data_ )
    end if

  end function array_size

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Finalize an array
  subroutine finalize( this )

    type(array_t), intent(inout) :: this

    if( associated( this%data_ ) ) deallocate( this%data_ )

  end subroutine finalize

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Finalize an array pointer by deallocating the target
  subroutine array_ptr_finalize( this )

    type(array_ptr), intent(inout) :: this

    if( associated( this%ptr_ ) ) deallocate( this%ptr_ )

  end subroutine array_ptr_finalize

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_array
