! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Fortran wrapper for aerosol models in C

!> The c_model_t type and related functions
module aero_c_model

  use aero_array,                      only : array_t
  use aero_c_array,                    only : c_array_t
  use aero_constants,                  only : real_kind
  use aero_model,                      only : model_t
  use aero_state,                      only : state_t
  use iso_c_binding

  implicit none
  private

  public :: c_model_t, c_state_t

  type, extends(state_t) :: c_state_t
    private
    type(c_ptr) :: state_ = c_null_ptr
  contains
    final :: state_finalize
  end type c_state_t

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

  type(c_ptr) function aero_bridge_c_model_name( model_c ) bind(c)
    use iso_c_binding
    type(c_ptr), value :: model_c
  end function aero_bridge_c_model_name

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  type(c_ptr) function aero_bridge_c_model_create_state( model_c ) bind(c)
    use iso_c_binding
    type(c_ptr), value :: model_c
  end function aero_bridge_c_model_create_state

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  type(c_ptr) function aero_bridge_c_model_optics_grid( model_c ) bind(c)
    use iso_c_binding
    type(c_ptr), value :: model_c
  end function aero_bridge_c_model_optics_grid

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine aero_bridge_c_model_compute_optics( model_c, state_c, od_c,      &
      od_ssa_c, od_asym_c ) bind(c)
    use iso_c_binding
    type(c_ptr), value :: model_c
    type(c_ptr), value :: state_c
    type(c_ptr), value :: od_c
    type(c_ptr), value :: od_ssa_c
    type(c_ptr), value :: od_asym_c
  end subroutine aero_bridge_c_model_compute_optics

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine aero_bridge_c_state_free( state_c ) bind(c)
    use iso_c_binding
    type(c_ptr), value :: state_c
  end subroutine aero_bridge_c_state_free

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

    use aero_util,                     only : die_msg, c_f_string

    !> Unique model name
    character(len=:), allocatable :: model_name
    !> C aerosol model
    class(c_model_t), intent(in) :: this

    call die_msg( 174548945, "not implemented yet" )
    !call c_f_string( aero_bridge_c_model_name( this%model_ ), model_name )

  end function model_name

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns a newly created aerosol state
  function create_state( this ) result( state )

    use aero_state,                    only : state_t

    !> New aerosol state
    class(state_t),    pointer    :: state
    !> C aerosol model
    class(c_model_t), intent(in) :: this

    allocate( c_state_t :: state )
    select type( state )
    type is( c_state_t )
      state%state_ = aero_bridge_c_model_create_state( this%model_ )
    end select

  end function create_state

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns the aerosol optics grid, discretized in wavenumber space
  function optics_grid( this )

    use aero_array,                    only : array_t
    use aero_c_array,                  only : c_array_t
    use aero_grid,                     only : grid_t

    !> Aerosol optical property wave number grid
    type(grid_t) :: optics_grid
    !> C aerosol model
    class(c_model_t), intent(in) :: this

    class(array_t), pointer :: ifaces

    ifaces => c_array_t( aero_bridge_c_model_optics_grid( this%model_ ),      &
                         owns_array = .true. )
    optics_grid = grid_t( ifaces )

  end function optics_grid

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Computes optical property data, given an aerosol state and destination
  !! arrays
  subroutine compute_optics( this, state, od, od_ssa, od_asym )

    use aero_state,                    only : state_t
    use aero_util,                     only : die_msg

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

    select type( state )
    class is( c_state_t )
      call aero_bridge_c_model_compute_optics( this%model_, state%state_,    &
            od%get_c_ptr( ), od_ssa%get_c_ptr( ), od_asym%get_c_ptr( ) )
    class default
      call die_msg( 699518494, "Incompatible state sent to C Model")
    end select

  end subroutine compute_optics

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Frees memory assicated with the given model wrapper
  subroutine finalize( this )

    type(c_model_t), intent(inout) :: this

    if( this%owns_model_ ) call aero_bridge_c_model_free( this%model_ )
    this%model_ = c_null_ptr

  end subroutine finalize

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Frees memory associated with the given state wrapper
  subroutine state_finalize( this )

    type(c_state_t), intent(inout) :: this

    call aero_bridge_c_state_free( this%state_ )
    this%state_ = c_null_ptr

  end subroutine state_finalize

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_c_model
