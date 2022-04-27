! Copyright (C) 2022 National Center for Atmospheric Research,
! National Technology & Engineering Solutions of Sandia, LLC (NTESS),
! and the U.S. Environmental Protection Agency (USEPA)
!
! SPDX-License-Identifier: Apache-2.0
!
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

  !> Creates a new state for use with the given Fortran model
  type(c_ptr) function aero_bridge_fortran_model_create_state( model_c_ptr )  &
    result( state_c_ptr ) bind(c)

    use aero_state,                    only : state_ptr

    type(c_ptr), value, intent(in) :: model_c_ptr

    type(model_ptr), pointer :: model_f_ptr
    type(state_ptr), pointer :: state_f_ptr

    call c_f_pointer( model_c_ptr, model_f_ptr )
    allocate( state_f_ptr )
    state_f_ptr%ptr_ => model_f_ptr%ptr_%create_state( )
    state_c_ptr = c_loc( state_f_ptr )

  end function aero_bridge_fortran_model_create_state

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns a copy of the optics grid interfaces used by the model
  type(c_ptr) function aero_bridge_fortran_model_optics_grid( model_c_ptr )   &
      result( ifaces_c_ptr ) bind(c)

    use aero_grid,                     only : grid_t
    use aero_array,                    only : array_t, array_ptr

    type(c_ptr), value, intent(in) :: model_c_ptr

    type(model_ptr), pointer :: model_f_ptr
    type(grid_t) :: grid
    class(array_t), pointer :: grid_ifaces
    type(array_ptr), pointer :: array_f_ptr

    call c_f_pointer( model_c_ptr, model_f_ptr )
    allocate( array_f_ptr )
    grid = model_f_ptr%ptr_%optics_grid( )
    grid_ifaces => grid%interfaces( )
    array_f_ptr%ptr_ => grid_ifaces%clone( )
    ifaces_c_ptr = c_loc( array_f_ptr )

  end function aero_bridge_fortran_model_optics_grid

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Copmutes aerosol optical properties for a given state
  subroutine aero_bridge_fortran_model_compute_optics( model_c_ptr,           &
      state_c_ptr, od_c_ptr, od_ssa_c_ptr, od_asym_c_ptr ) bind(c)

    use aero_array,                    only : array_ptr
    use aero_state,                    only : state_ptr

    type(c_ptr), value, intent(in) :: model_c_ptr
    type(c_ptr), value, intent(in) :: state_c_ptr
    type(c_ptr), value, intent(in) :: od_c_ptr
    type(c_ptr), value, intent(in) :: od_ssa_c_ptr
    type(c_ptr), value, intent(in) :: od_asym_c_ptr

    type(model_ptr), pointer :: model_f_ptr
    type(state_ptr), pointer :: state_f_ptr
    type(array_ptr), pointer :: od_f_ptr, od_ssa_f_ptr, od_asym_f_ptr

    call c_f_pointer( model_c_ptr,   model_f_ptr   )
    call c_f_pointer( state_c_ptr,   state_f_ptr   )
    call c_f_pointer( od_c_ptr,      od_f_ptr      )
    call c_f_pointer( od_ssa_c_ptr,  od_ssa_f_ptr  )
    call c_f_pointer( od_asym_c_ptr, od_asym_f_ptr )

    call model_f_ptr%ptr_%compute_optics( state_f_ptr%ptr_, od_f_ptr%ptr_,    &
           od_ssa_f_ptr%ptr_, od_asym_f_ptr%ptr_ )

  end subroutine aero_bridge_fortran_model_compute_optics

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_model_bridge
