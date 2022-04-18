! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file

!> The cpp_array_t type and related functions
module aero_cpp_array

  use aero_array,                      only : array_t
  use aero_constants,                  only : real_kind
  use iso_c_binding

  implicit none
  private

  public :: cpp_array_t

  type, extends(array_t) :: cpp_array_t
    private
    type(c_ptr) :: array_ = c_null_ptr
  contains
    procedure, pass(from) :: clone
    procedure, pass(to)   :: copy_in
    procedure, pass(from) :: copy_out
    procedure :: data => array_data
    procedure :: size => array_size
    final :: finalize
  end type cpp_array_t

  interface cpp_array_t
    module procedure :: constructor
  end interface

interface

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  type(c_ptr) function aero_bridge_cpp_array_clone( array_c ) bind(c)
    use iso_c_binding
    type(c_ptr), value :: array_c
  end function aero_bridge_cpp_array_clone

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine aero_bridge_cpp_array_free( array_c ) bind(c)
    use iso_c_binding
    type(c_ptr), value :: array_c
  end subroutine aero_bridge_cpp_array_free

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine aero_bridge_cpp_array_copy_in( array_c, input_c ) bind(c)
    use iso_c_binding
    type(c_ptr), value :: array_c
    type(c_ptr), value :: input_c
  end subroutine aero_bridge_cpp_array_copy_in

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine aero_bridge_cpp_array_copy_out( array_c, output_c ) bind(c)
    use iso_c_binding
    type(c_ptr), value :: array_c
    type(c_ptr), value :: output_c
  end subroutine aero_bridge_cpp_array_copy_out

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  function aero_bridge_cpp_array_data( array_c ) result( data_c ) bind(c)
    use iso_c_binding
    type(c_ptr)        :: data_c
    type(c_ptr), value :: array_c
  end function aero_bridge_cpp_array_data

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  integer(kind=c_int) function aero_bridge_cpp_array_size( array_c ) bind(c)
    use iso_c_binding
    type(c_ptr), value :: array_c
  end function aero_bridge_cpp_array_size

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end interface

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns a pointer to a new C++ Array
  function constructor( cpp_array_c_ptr ) result( array )

    class(array_t), pointer    :: array
    type(c_ptr),    intent(in) :: cpp_array_c_ptr

    allocate( cpp_array_t :: array )
    select type( array )
    type is( cpp_array_t )
      array%array_ = cpp_array_c_ptr
    end select

  end function constructor

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Clones an Array
  function clone( from )

    class(array_t),     pointer    :: clone
    class(cpp_array_t), intent(in) :: from

    allocate( cpp_array_t :: clone )
    select type( clone )
    class is( cpp_array_t )
      clone%array_ =  aero_bridge_cpp_array_clone( from%array_ )
    end select

  end function clone

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Copies data into an Array
  subroutine copy_in( to, from )

    class(cpp_array_t),     intent(inout)        :: to
    real(kind=real_kind), intent(in),   target :: from(:)

    type(c_ptr) :: from_c

    from_c = c_loc( from )
    call aero_bridge_cpp_array_copy_in( to%array_, from_c )

  end subroutine copy_in

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Copies data out of an Array
  subroutine copy_out( to, from )

    real(kind=real_kind), intent(inout), target :: to(:)
    class(cpp_array_t),     intent(in)            :: from

    type(c_ptr) :: to_c

    to_c = c_loc( to )
    call aero_bridge_cpp_array_copy_out( from%array_, to_c )

  end subroutine copy_out

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns a pointer to the underlying array data
  function array_data( this )

    real(kind=real_kind), pointer       :: array_data(:)
    class(cpp_array_t),   intent(inout) :: this

    call c_f_pointer( aero_bridge_cpp_array_data( this%array_ ), array_data,  &
                      shape = [ aero_bridge_cpp_array_size( this%array_ ) ] )

  end function array_data

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns the number of elements in an Array
  integer function array_size( this )

    class(cpp_array_t), intent(in) :: this

    array_size = aero_bridge_cpp_array_size( this%array_ )

  end function array_size

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Frees memory associated with the given array
  subroutine finalize( this )

    type(cpp_array_t), intent(inout) :: this

    call aero_bridge_cpp_array_free( this%array_ )
    this%array_ = c_null_ptr

  end subroutine finalize

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_cpp_array
