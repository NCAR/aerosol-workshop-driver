! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Fortran wrapper for aerosol models in C

!> The cpp_model_t type and related functions
module aero_cpp_model

  use aero_array,                      only : array_t
  use aero_c_array,                    only : c_array_t
  use aero_cpp_array,                  only : cpp_array_t
  use aero_model,                      only : model_t
  use aero_constants,                  only : real_kind
  use iso_c_binding

  implicit none
  private

  public :: cpp_model_t

  type, extends(model_t) :: cpp_model_t
    private
    logical :: owns_model_ = .false.
    type(c_ptr) :: model_ = c_null_ptr
  contains
    procedure :: name => model_name
    procedure :: create_state
    procedure :: optics_grid
    procedure :: compute_optics
    final :: finalize
  end type cpp_model_t

  interface cpp_model_t
    module procedure :: constructor
  end interface

interface

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  subroutine aero_bridge_cpp_model_free( model_cpp ) bind(c)
    use iso_c_binding
    type(c_ptr), value :: model_cpp
  end subroutine aero_bridge_cpp_model_free

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  type(c_ptr) function aero_bridge_cpp_model_name( model_cpp ) bind(c)
    use iso_c_binding
    type(c_ptr), value :: model_cpp
  end function aero_bridge_cpp_model_name

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end interface

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Wraps a C++-backed model for use in Fortran
  type(c_ptr) function aero_cpp_model_wrap_fortran( cpp_model )               &
      result( f_model ) bind(c)

    use aero_model,                    only : model_ptr
    use iso_c_binding

    type(c_ptr), value, intent(in) :: cpp_model

    type(model_ptr), pointer :: cpp_wrap

    allocate( cpp_wrap )
    cpp_wrap%ptr_ => cpp_model_t( cpp_model )
    f_model = c_loc( cpp_wrap )

  end function aero_cpp_model_wrap_fortran

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Destroys a Fortran wrapper of a C++-backed model
  subroutine aero_cpp_model_unwrap_fortran( f_model ) bind(c)

    use aero_model,                    only : model_ptr
    use iso_c_binding

    type(c_ptr), value, intent(in) :: f_model

    type(model_ptr), pointer :: cpp_wrap

    call c_f_pointer( f_model, cpp_wrap )
    deallocate( cpp_wrap )

  end subroutine aero_cpp_model_unwrap_fortran

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns a pointer to a new Fortran wrapper of C++-backed model
  function constructor( cpp_model_c_ptr, owns_model ) result( model )

    class(model_t),    pointer    :: model
    !> Void pointer to a C++-backed model instance
    type(c_ptr),       intent(in) :: cpp_model_c_ptr
    !> Flag indicating whether this wrapper owns the underlying model
    logical, optional, intent(in) :: owns_model

    allocate( cpp_model_t :: model )
    select type( model )
    type is( cpp_model_t )
      model%model_ = cpp_model_c_ptr
      if( present( owns_model ) ) model%owns_model_ = owns_model
    end select

  end function constructor

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns the name of the aerosol model/package
  function model_name( this )

    use aero_util,                     only : die_msg, c_f_string

    !> Unique model name
    character(len=:), allocatable :: model_name
    !> C++ aerosol model
    class(cpp_model_t), intent(in) :: this

    call die_msg( 174548945, "not implemented yet" )
    !call c_f_string( aero_bridge_cpp_model_name( this%model_ ), model_name )

  end function model_name

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns a newly created aerosol state
  function create_state( this ) result( state )

    use aero_state,                    only : state_t

    !> New aerosol state
    class(state_t),    pointer    :: state
    !> C++ aerosol model
    class(cpp_model_t), intent(in) :: this

  end function create_state

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns the aerosol optics grid, discretized in wavenumber space
  function optics_grid( this )

    use aero_grid,                     only : grid_t

    !> Aerosol optical property wave number grid
    type(grid_t) :: optics_grid
    !> C++ aerosol model
    class(cpp_model_t), intent(in) :: this

  end function optics_grid

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Computes optical property data, given an aerosol state and destination
  !! arrays
  subroutine compute_optics( this, state, od, od_ssa, od_asym )

    use aero_state,                    only : state_t

    !> C++ aerosol model
    class(cpp_model_t), intent(inout) :: this
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

    type(cpp_model_t), intent(inout) :: this

    if( this%owns_model_ ) call aero_bridge_cpp_model_free( this%model_ )
    this%model_ = c_null_ptr

  end subroutine finalize

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_cpp_model
