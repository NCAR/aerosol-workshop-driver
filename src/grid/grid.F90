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

  public :: grid_t

  !> This type represents a computional grid consisting of a set of contiguous
  !> segments separated by interfaces. The grid keeps track of the midpoints
  !> between interfaces.
  type :: grid_t
    !> array storing interface coordinates (in ascending order)
    class(array_t), pointer :: interfaces
    !> array storing coordinates of midpoints between interfaces (in ascending
    !> order)
    class(array_t), pointer :: midpoints
    !> lower bound (minimum interface coordinate), provided for convenience
    real(kind=real_kind) :: lower_bound
    !> upper bound (maximum interface coordinate), provided for convenience
    real(kind=real_kind) :: upper_bound
  contains
    final :: grid_finalize
  end type grid_t

  ! Constructors
  interface grid_t
    module procedure :: grid_from_interfaces
  end interface

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !> Creates a grid from an array containing points delimiting the interfaces
  !> between segments. The grid assumes ownership of this array.
  function grid_from_interfaces(interfaces) result(grid)
    type(grid_t)                        :: grid
    class(array_t), pointer, intent(in) :: interfaces

    integer                           :: n_iface, n_midpt, i
    real(kind=real_kind), allocatable :: iface_data(:), midpt_data(:)

    n_iface = interfaces%size()
    allocate(iface_data(n_iface), midpt_data(n_iface-1))
    call interfaces%copy_out(iface_data)
    do i = 1,n_iface-1
      midpt_data(i) = 0.5 * (iface_data(i) + iface_data(i+1));
    end do

    grid%interfaces  => interfaces%clone()
    grid%midpoints   => array_t(midpt_data)
    grid%lower_bound =  iface_data(1)
    grid%upper_bound =  iface_data(n_iface)

    deallocate(iface_data, midpt_data)
  end function grid_from_interfaces

  !> Finalize a grid, freeing its resources
  subroutine grid_finalize(grid)
    type(grid_t), intent(inout) :: grid
    if (associated(grid%interfaces)) deallocate(grid%interfaces)
    if (associated(grid%midpoints))  deallocate(grid%midpoints)
  end subroutine
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_grid
