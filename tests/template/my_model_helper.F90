! Copyright (C) 2022 National Center for Atmospheric Research,
! National Technology & Engineering Solutions of Sandia, LLC (NTESS),
! and the U.S. Environmental Protection Agency (USEPA)
!
! SPDX-License-Identifier: Apache-2.0
!
module test_my_model_helper

  use aero_model,                      only : model_t, model_ptr
  use my_model,                        only : my_model_t
  use iso_c_binding

  implicit none

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates an instance of my_model_t for use in C/C++ tests
  type(c_ptr) function test_my_model_create_fortran_model( )                  &
      result( model_c_ptr ) bind(c)

    type(model_ptr), pointer :: model

    allocate( model )
    model%ptr_ => my_model_t( "" )
    model_c_ptr = c_loc( model )

  end function test_my_model_create_fortran_model

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module test_my_model_helper
