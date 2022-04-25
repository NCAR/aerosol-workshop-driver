! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Fortran wrapper for aerosol models in C

!> The c_model_t type and related functions
module aero_c_model

  use aero_array,                      only : array_t
  use aero_c_array,                    only : c_array_t
  use aero_c_array,                  only : c_array_t
  use aero_model,                      only : model_t
  use aero_constants,                  only : real_kind
  use iso_c_binding

  implicit none
  private

  public :: c_model_t

  type, extends(model_t) :: c_model_t
    private
    logical :: owns_model_ = .false.
    type(c_ptr) :: model_ = c_null_ptr
  contains
    procedure :: name => model_name
    procedure :: create_state
    procedure :: optics_grid
    procedure :: compute_optics
    final :: finalize
  end type c_model_t

  interface c_model_t
    module procedure :: constructor
  end interface

interface

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine aero_bridge_c_model_free( model_c ) bind(c)
    use iso_c_binding
    type(c_ptr), value :: model_c
  end subroutine aero_bridge_c_model_free

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end interface

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Wraps a C-backed model for use in Fortran
  type(c_ptr) function aero_c_model_wrap_fortran( c_model )               &
      result( f_model ) bind(c)

    use aero_model,                    only : model_ptr
    use iso_c_binding

    type(c_ptr), value, intent(in) :: c_model

    type(model_ptr), pointer :: c_wrap

    allocate( c_wrap )
    c_wrap%ptr_ => c_model_t( c_model )
    f_model = c_loc( c_wrap )

  end function aero_c_model_wrap_fortran

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Destroys a Fortran wrapper of a C-backed model
  subroutine aero_c_model_unwrap_fortran( f_model ) bind(c)

    use aero_model,                    only : model_ptr
    use iso_c_binding

    type(c_ptr), value, intent(in) :: f_model

    type(model_ptr), pointer :: c_wrap

    call c_f_pointer( f_model, c_wrap )
    deallocate( c_wrap )

  end subroutine aero_c_model_unwrap_fortran

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns a pointer to a new Fortran wrapper of C-backed model
  function constructor( c_model_c_ptr, owns_model ) result( model )

    class(model_t),    pointer    :: model
    !> Void pointer to a C-backed model instance
    type(c_ptr),       intent(in) :: c_model_c_ptr
    !> Flag indicating whether this wrapper owns the underlying model
    logical, optional, intent(in) :: owns_model

    allocate( c_model_t :: model )
    select type( model )
    type is( c_model_t )
      model%model_ = c_model_c_ptr
      if( present( owns_model ) ) model%owns_model_ = owns_model
    end select

  end function constructor

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns the name of the aerosol model/package
  function model_name( this )

    !> Unique model name
    character(len=:), allocatable :: model_name
    !> C aerosol model
    class(c_model_t), intent(in) :: this

  end function model_name

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns a newly created aerosol state
  function create_state( this ) result( state )

    use aero_state,                    only : state_t

    !> New aerosol state
    class(state_t),    pointer    :: state
    !> C aerosol model
    class(c_model_t), intent(in) :: this

  end function create_state

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns the aerosol optics grid, discretized in wavenumber space
  function optics_grid( this )

    use aero_grid,                     only : grid_t

    !> Aerosol optical property wave number grid
    type(grid_t) :: optics_grid
    !> C aerosol model
    class(c_model_t), intent(in) :: this

  end function optics_grid

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Computes optical property data, given an aerosol state and destination
  !! arrays
  subroutine compute_optics( this, state, od, od_ssa, od_asym )

    use aero_state,                    only : state_t

    !> C aerosol model
    class(c_model_t), intent(inout) :: this
    !> Aerosol state
    class(state_t),    intent(inout) :: state
    !> Aerosol optical depth [m]
    class(array_t),    intent(inout) :: od
    !> Aerosol scattering optical depth [m]
    class(array_t),    intent(inout) :: od_ssa
    !> Aerosol asymmetric scattering optical depth [m]
    class(array_t),    intent(inout) :: od_asym

  end subroutine compute_optics

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Frees memory assicated with the given array wrapper
  subroutine finalize( this )

    type(c_model_t), intent(inout) :: this

    if( this%owns_model_ ) call aero_bridge_c_model_free( this%model_ )
    this%model_ = c_null_ptr

  end subroutine finalize

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_c_model
