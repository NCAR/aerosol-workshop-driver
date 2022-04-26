! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file

!> The interpolator_t type and related functions
module aero_interpolator

  use aero_constants,                   only : real_kind

  implicit none
  private

  public :: interpolator_t, interpolator_ptr

  type :: interpolator_impl_t
    private
    integer,              allocatable :: from_points_(:)
    real(kind=real_kind), allocatable :: from_weights_(:)
  end type interpolator_impl_t

  type :: interpolator_t
    private
    type(interpolator_impl_t) :: impl_
  contains
    procedure :: interpolate
  end type interpolator_t

  interface interpolator_t
    module procedure :: constructor
  end interface

  type :: interpolator_ptr
    class(interpolator_t), pointer :: ptr_ => null( )
  contains
    final :: interpolator_ptr_finalize
  end type interpolator_ptr

contains

  ! This helper performs a binary search on sorted grid data, computing the index
  !of the first point within the grid data that is no larger than the desired
  ! value.
  function lower_bound(array, val) result(lb)
    real(kind=real_kind), pointer, intent(in) :: array(:)
    real(kind=real_kind),          intent(in) :: val

    integer :: lb, low, mid, high

    ! Till our paths cross...
    low = 1
    high = size(array) + 1
    do while (low < high)
      mid = low + (high - low) / 2
      if (val <= array(mid)) then
        high = mid
      else
        low = mid + 1
      end if
    end do

    if ((low < size(array)) .and. (array(low) < val)) low = low + 1
    lb = low
  end function lower_bound

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates a linear interpolator from one grid to another
  function constructor( from, to ) result( interp )

    use aero_array,                    only : array_t
    use aero_grid,                     only : grid_t

    type(interpolator_t)             :: interp
    type(grid_t),         intent(in) :: from
    type(grid_t),         intent(in) :: to

    class(array_t), pointer :: to_interfaces, from_interfaces
    real(kind=real_kind), pointer :: to_x(:), from_x(:)
    type(interpolator_impl_t) :: impl
    integer :: i, lb

    from_interfaces => from%interfaces( )
    to_interfaces   => to%interfaces( )
    from_x => from_interfaces%data( )
    to_x   => to_interfaces%data( )

    ! Build the "from" -> "to" mapping.
    allocate(interp%impl_%from_points_(2*size(to_x)))
    allocate(interp%impl_%from_points_(2*size(to_x)))
    do i = 1, size( from_x )
      lb = lower_bound(from_x, to_x(i))
      if ((lb == 1) .and. (to_x(i) < from_x(1))) then ! off the lower end!
        impl%from_points_(2*i)    = 1   ! no left neighbor
        impl%from_weights_(2*i)   = 0.0
        impl%from_points_(2*i+1)  = 1   ! right neighbor
        impl%from_weights_(2*i+1) = 1.0
      elseif (lb >= size(from_x)) then ! off the upper end!
        impl%from_points_(2*i)    = size(from_x) ! left neighbor
        impl%from_weights_(2*i)   = 1.0
        impl%from_points_(2*i+1)  = size(from_x) ! no right neighbor
        impl%from_weights_(2*i+1) = 0.0
      else
        impl%from_points_(2*i)    = lb       ! left neighbor
        impl%from_weights_(2*i)   = &
          1.0 - (to_x(i) - from_x(lb))/(from_x(lb+1)-from_x(lb))
        impl%from_points_(2*i+1)  = lb+1    ! right neighbor
        impl%from_weights_(2*i+1) = &
          1.0 - (from_x(lb+1) - to_x(i))/(from_x(lb+1)-from_x(lb))
      end if
    end do
    interp%impl_ = impl
  end function constructor

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Interpolates data from the input grid to the output grid
  subroutine interpolate( this, from, to )

    use aero_array,                    only : array_t

    class(interpolator_t), intent(in)    :: this
    class(array_t),        intent(in)    :: from
    class(array_t),        intent(inout) :: to

    integer :: i, j_left, j_right
    real(kind=real_kind) :: w_left, w_right
    real(kind=real_kind), pointer :: to_a(:)
    real(kind=real_kind), pointer :: from_a(:)

    to_a   => to%data( )
    from_a => from%data( )
    do i = 1, size( to_a )
      j_left  = this%impl_%from_points_(2*i)
      w_left  = this%impl_%from_weights_(2*i)
      j_right = this%impl_%from_points_(2*i+1)
      w_right = this%impl_%from_weights_(2*i+1)
      to_a(i) = from_a(j_left) * w_left + from_a(j_right) * w_right
    end do

  end subroutine interpolate

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Frees resources assocaited with an interpolator pointer
  subroutine interpolator_ptr_finalize( this )

    type(interpolator_ptr), intent(inout) :: this

    if( associated( this%ptr_ ) ) deallocate( this%ptr_ )

  end subroutine interpolator_ptr_finalize

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module aero_interpolator!

