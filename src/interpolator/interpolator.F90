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

  type :: interpolator_map_t
    private
    integer :: from_
    integer :: to_
    real(kind=real_kind) :: weight_
  end type interpolator_map_t

  type :: interpolator_t
    private
    type(interpolator_map_t), allocatable :: map_(:)
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

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates a linear interpolator from one grid to another
  function constructor( from, to ) result( interp )

    use aero_array,                    only : array_t
    use aero_grid,                     only : grid_t

    type(interpolator_t)             :: interp
    type(grid_t),         intent(in) :: from
    type(grid_t),         intent(in) :: to

    class(array_t), pointer :: to_interfaces, from_interfaces
    real(kind=real_kind), pointer :: to_a(:), from_a(:)
    integer :: i, j
    real(kind=real_kind) :: weight
    type(interpolator_map_t) :: elem

    from_interfaces => from%interfaces( )
    to_interfaces   => to%interfaces( )
    from_a => from_interfaces%data( )
    to_a   => to_interfaces%data( )

    allocate( interp%map_( 0 ) )
    do i = 1, size( from_a ) - 1
      do j = 1, size( to_a ) - 1
        if( to_a(j) < from_a(i+1) .and. from_a(i) < to_a(j+1) ) then
          weight = max( 0.0, min( from_a(i+1), to_a(j+1) )                    &
                             - max( from_a(i), to_a(j) ) )
          weight = weight / ( from_a(i+1) - from_a(i) )
          elem%from_   = i
          elem%to_     = j
          elem%weight_ = weight
          interp%map_ = [ interp%map_, elem ]
        end if
      end do
    end do

  end function constructor

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Interpolates data from the input grid to the output grid
  subroutine interpolate( this, from, to )

    use aero_array,                    only : array_t

    class(interpolator_t), intent(in)    :: this
    class(array_t),        intent(in)    :: from
    class(array_t),        intent(inout) :: to

    integer :: i_map
    real(kind=real_kind), pointer :: to_a(:)
    real(kind=real_kind), pointer :: from_a(:)

    to_a   => to%data( )
    from_a => from%data( )
    to_a(:) = 0.0
    do i_map = 1, size( this%map_ )
      to_a( this%map_( i_map )%to_ ) = to_a( this%map_( i_map )%to_ ) +      &
          from_a( this%map_( i_map )%from_ ) * this%map_( i_map )%weight_
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

