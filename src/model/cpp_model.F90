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
    type(c_ptr) :: model_
  contains
    procedure :: name => model_name
    procedure :: create_state
    procedure :: optics_grid
    procedure :: compute_optics
  end type

  interface cpp_model_t
    module procedure :: constructor
  end interface

  interface

    !> Returns whether a C++ aerosol model is supported
    function aero_bridge_cpp_supports_model( package_name )   &
        result( exists ) bind (c)
      use iso_c_binding
      logical(kind=c_bool)                 :: exists
      character(kind=c_char), dimension(*) :: package_name
    end function

    !> Builds a C++ aerosol model
    function aero_bridge_cpp_new_model( package_name, description_file )   &
        result( model ) bind (c)
      use iso_c_binding
      type(c_ptr)                          :: model
      character(kind=c_char), dimension(*) :: package_name
      character(kind=c_char), dimension(*) :: description_file
    end function aero_bridge_cpp_new_model

  end interface

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates a C++ aerosol model
  !!
  !! If the model is not a supported model in C++, a null pointer is returned
  function constructor( package_name, description_file ) result( model )

    type(cpp_model_t),  pointer    :: model
    character(len=*), intent(in) :: package_name
    character(len=*), intent(in) :: description_file

    if( aero_bridge_cpp_supports_model( trim( package_name )//c_null_char ) )   &
      then
      allocate( model )
      model%model_ = aero_bridge_cpp_new_model(                  &
                       trim( package_name )//c_null_char,      &
                       trim( description_file )//c_null_char )
    else
      model => null( )
    end if

  end function

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns the name of the aerosol model/package
  function model_name( this )

    !> Unique model name
    character(len=:), allocatable :: model_name
    !> C++ aerosol model
    class(cpp_model_t), intent(in) :: this

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

end module aero_cpp_model
