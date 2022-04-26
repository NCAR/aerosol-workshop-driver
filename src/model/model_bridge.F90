! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file

!> Bridge functions for the model_t type
module aero_model_bridge

  use aero_model,                      only : model_t, model_ptr
  use aero_c_model,                    only : c_model_t
  use aero_cpp_model,                  only : cpp_model_t
  use iso_c_binding

  implicit none

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Frees resources associated with the given Fortran model
  subroutine aero_bridge_fortran_model_free( model_c_ptr ) bind(c)

    type(c_ptr), value, intent(in) :: model_c_ptr

    type(model_ptr), pointer :: model_ptr

    call c_f_pointer( model_c_ptr, model_ptr )
    deallocate( model_ptr )

  end subroutine aero_bridge_fortran_model_free

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns the name of an aerosol package
  type(c_ptr) function aero_bridge_fortran_model_name( model_c_ptr )          &
      result( model_name ) bind(c)

    type(c_ptr), value, intent(in) :: model_c_ptr

    type(model_ptr), pointer :: model_ptr
    character(kind=c_char, len=:), allocatable, target :: f_name

    call c_f_pointer( model_c_ptr, model_ptr )
    f_name = model_ptr%ptr_%name( )//c_null_char
    model_name = c_loc( f_name )

  end function aero_bridge_fortran_model_name

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_model_bridge
