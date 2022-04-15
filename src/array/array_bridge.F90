! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file

!> Bridge functions for the array_t type
module aero_array_bridge

  use aero_array,                      only : array_t, array_ptr
  use aero_c_array,                    only : c_array_t
  use aero_cpp_array,                  only : cpp_array_t
  use aero_constants,                  only : real_kind
  use iso_c_binding

  implicit none

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns a pointer to a newly cloned (deep-copied) array implemented in
  !! Fortran
  type(c_ptr) function aero_bridge_fortran_array_clone( from_c_ptr )          &
      result( to_c_ptr ) bind(c)

    type(c_ptr), value, intent(in) :: from_c_ptr

    type(array_ptr), pointer :: from_ptr, to_ptr

    call c_f_pointer( from_c_ptr, from_ptr )
    allocate( to_ptr )
    to_ptr%ptr_ => from_ptr%ptr_%clone( )
    to_c_ptr = c_loc( to_ptr )

  end function aero_bridge_fortran_array_clone

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Frees resources associated with the given Fortran array
  subroutine aero_bridge_fortran_array_free( array_c_ptr ) bind(c)

    type(c_ptr), value, intent(in) :: array_c_ptr

    type(array_ptr), pointer :: array_ptr

    call c_f_pointer( array_c_ptr, array_ptr )
    deallocate( array_ptr )

  end subroutine aero_bridge_fortran_array_free

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Copies data into the given Fortran array
  subroutine aero_bridge_fortran_array_copy_in( array_c_ptr, input_c_ptr )    &
      bind(c)

    type(c_ptr), value, intent(in) :: array_c_ptr
    type(c_ptr), value, intent(in) :: input_c_ptr

    type(array_ptr),      pointer :: array_ptr
    real(kind=real_kind), pointer :: input_ptr(:)

    call c_f_pointer( array_c_ptr, array_ptr )
    call c_f_pointer( input_c_ptr, input_ptr, (/ array_ptr%ptr_%size( ) /) )
    call array_ptr%ptr_%copy_in( input_ptr )

  end subroutine aero_bridge_fortran_array_copy_in

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Copies data out of the given Fortran array
  subroutine aero_bridge_fortran_array_copy_out( array_c_ptr, output_c_ptr )  &
      bind(c)

    type(c_ptr), value, intent(in) :: array_c_ptr
    type(c_ptr), value, intent(in) :: output_c_ptr

    type(array_ptr),      pointer :: array_ptr
    real(kind=real_kind), pointer :: output_ptr(:)

    call c_f_pointer( array_c_ptr, array_ptr )
    call c_f_pointer( output_c_ptr, output_ptr, (/ array_ptr%ptr_%size( ) /) )
    call array_ptr%ptr_%copy_out( output_ptr )

  end subroutine aero_bridge_fortran_array_copy_out

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns the number of elements in the given Fortran array
  integer(kind=c_size_t) function aero_bridge_fortran_array_size(             &
      array_c_ptr ) result( array_size ) bind(c)

    type(c_ptr), value, intent(in) :: array_c_ptr

    type(array_ptr), pointer :: array_ptr

    call c_f_pointer( array_c_ptr, array_ptr )
    array_size = array_ptr%ptr_%size( )

  end function aero_bridge_fortran_array_size

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_array_bridge
