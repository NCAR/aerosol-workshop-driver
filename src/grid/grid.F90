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

  public :: grid_bounds_t, grid_t

  !> Simple container for storing grid lower/upper bounds.
  type :: grid_bounds_t
    real(kind=real_kind) :: lower, upper
  end type

  !> This type represents a computional grid consisting of a set of contiguous
  !> segments separated by interfaces. The grid keeps track of the midpoints
  !> between interfaces.
  type :: grid_t
    !> Arrays containing interfaces and segment midpoints.
    type(array_t)         :: interfaces_, midpoints_
    !> Lower and upper bounds.
    type(grid_bounds_t)   :: bounds_
  contains
    procedure :: interfaces
    procedure :: midpoints
    procedure :: bounds
  end type grid_t

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !> Provides access to the array containing grid interfaces.
  type(array_t) function interfaces(this) result(ifaces)
    type(array_t)                :: ifaces
    class(grid_t), intent(inout) :: this

    ifaces = this%interfaces_
  end function interfaces

  !> Provides access to the array containing grid segment midpoints.
  type(array_t) function midpoints(this) result(midp)
    type(array_t)                :: midp
    class(grid_t), intent(inout) :: this

    midp = this%midpoints_
  end function midpoints

  !> Returns the lower and upper bounds (minimum and maximum grid interface
  !> points) for the grid.
  type(grid_bounds_t) function bounds(this) result(bnds)
    type(grid_bounds_t)          :: bnds
    class(grid_t), intent(inout) :: this

    bnds = this%bounds_
  end function bounds

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_grid
