! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Fortran wrapper for aerosol interface

!> The model_t type and related functions
module aero_grid

  use aero_constants,              only : real_kind
  use aero_array,                  only : array_t
  use aero_c_array,                only : c_array_t
  use aero_cpp_array,              only : cpp_array_t
  use iso_c_binding

  implicit none
  private

  public :: grid_t

  !> This type represents a computional grid consisting of a set of contiguous
  !> segments separated by interfaces. The grid keeps track of the midpoints
  !> between interfaces.
  type :: grid_t
    private
    !> array storing interface coordinates (in ascending order)
    class(array_t), pointer :: interfaces_ => null( )
    !> array storing coordinates of midpoints between interfaces (in ascending
    !> order)
    class(array_t), pointer :: midpoints_ => null( )
    !> lower bound (minimum interface coordinate), provided for convenience
    real(kind=real_kind) :: lower_bound_
    !> upper bound (maximum interface coordinate), provided for convenience
    real(kind=real_kind) :: upper_bound_
  contains
    procedure :: clone       => grid_clone
    procedure :: interfaces  => grid_interfaces
    procedure :: midpoints   => grid_midpoints
    procedure :: lower_bound => grid_lower_bound
    procedure :: upper_bound => grid_upper_bound
    final     :: grid_finalize
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

    grid%interfaces_  => interfaces
    grid%midpoints_   => array_t(midpt_data)
    grid%lower_bound_ =  iface_data(1)
    grid%upper_bound_ =  iface_data(n_iface)

    deallocate(iface_data, midpt_data)
  end function grid_from_interfaces

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Copies a grid
  type(grid_t) function grid_clone( this ) result( clone )
    class(grid_t),  intent(in) :: this
    class(array_t), pointer    :: ifaces
    ifaces => this%interfaces_%clone( )
    clone = grid_t( ifaces )
  end function grid_clone

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Provides access to grid interfaces
  function grid_interfaces(grid) result(ifaces)
    class(array_t), pointer    :: ifaces
    class(grid_t),  intent(in) :: grid
    ifaces => grid%interfaces_
  end function grid_interfaces

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Provides access to grid midpoints
  function grid_midpoints(grid) result(midpts)
    class(array_t), pointer    :: midpts
    class(grid_t),  intent(in) :: grid
    midpts => grid%midpoints_
  end function grid_midpoints

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Provides access to grid lower bound
  function grid_lower_bound(grid) result(lb)
    real(kind=real_kind)      :: lb
    class(grid_t), intent(in) :: grid
    lb = grid%lower_bound_
  end function grid_lower_bound

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Provides access to grid upper bound
  function grid_upper_bound(grid) result(ub)
    real(kind=real_kind)      :: ub
    class(grid_t), intent(in) :: grid
    ub = grid%upper_bound_
  end function grid_upper_bound

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Finalize a grid, freeing its resources
  subroutine grid_finalize(grid)
    type(grid_t), intent(inout) :: grid
    if (associated(grid%interfaces_)) deallocate(grid%interfaces_)
    if (associated(grid%midpoints_))  deallocate(grid%midpoints_)
  end subroutine grid_finalize

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_grid
