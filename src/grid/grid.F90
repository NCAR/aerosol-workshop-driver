! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Fortran wrapper for aerosol interface

!> The model_t type and related functions
module aero_grid

  use aero_constants,              only : real_kind
  use aero_array,                  only : array_t
  use iso_c_binding

  implicit none
  private

  public :: grid_t, grid_bounds_t

  !> Simple container for storing grid lower/upper bounds.
  type :: grid_bounds_t
    real(kind=real_kind :: lower, upper
  end type

  !> This type represents a computional grid consisting of a set of contiguous
  !> segments separated by interfaces. The grid keeps track of the midpoints
  !> between interfaces.
  type :: grid_t
    !> Arrays containing interfaces and segment midpoints.
    type(array_t)         :: interfaces, midpoints
    !> Lower and upper bounds.
    type(grid_bounds_t)   :: bounds
  contains
    procedure(interfaces) :: g_interfaces
    procedure(midpoints)  :: g_midpoints
    procedure(bounds)     :: g_bounds
  end type

interface

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !> Provides access to the array containing grid interfaces.
  type(array_t) function g_interfaces(this)
    class(grid_t), in(inout) :: this

    return this%interfaces
  end function

  !> Provides access to the array containing grid segment midpoints.
  type(array_t) function g_midpoints(this)
    class(grid_t), in(inout) :: this

    return this%midpoints
  end function

  !> Returns the lower and upper bounds (minimum and maximum grid interface
  !> points) for the grid.
  type(grid_bounds_t) function g_bounds(this)
    class(grid_t), in(inout) :: this

    return this%g_bounds
  end function

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end interface

end module
