! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
program test_my_model

  use my_model,                        only : my_model_t

  implicit none

  ! c support functions
  interface
    type(c_ptr) function test_my_model_create_c_model() bind(c)
      use iso_c_binding
    end function test_my_model_create_c_model
  end interface

  ! c++ support functions
  interface
    type(c_ptr) function test_my_model_create_cpp_model() bind(c)
      use iso_c_binding
    end function test_my_model_create_cpp_model
  end interface

  call test_my_model_t( )

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Tests the my_model_t stub class
  subroutine test_my_model_t( )

    use aero_array,                      only : array_t
    use aero_constants,                  only : rk => real_kind
    use aero_grid,                       only : grid_t
    use aero_model,                      only : model_t
    use aero_c_model,                    only : c_model_t
    use aero_cpp_model,                  only : cpp_model_t
    use aero_state,                      only : state_t
    use aero_util,                       only : assert, almost_equal

    class(model_t), pointer :: model
    class(state_t), pointer :: state
    type(grid_t) :: optics_grid
    class(array_t), pointer :: interfaces, od, od_ssa, od_asym
    real(kind=rk), allocatable :: od_a(:), od_ssa_a(:), od_asym_a(:)

    ! fortran model
    model => my_model_t( "" )
    state => model%create_state( )
    optics_grid = model%optics_grid( )
    interfaces => optics_grid%interfaces( )

    call assert( 158605235, interfaces%size( ) == 4 )
    od      => array_t( interfaces%size( ), 0.0_rk )
    od_ssa  => array_t( interfaces%size( ), 0.0_rk )
    od_asym => array_t( interfaces%size( ), 0.0_rk )
    allocate( od_a(      interfaces%size( ) ) )
    allocate( od_ssa_a(  interfaces%size( ) ) )
    allocate( od_asym_a( interfaces%size( ) ) )

    call model%compute_optics( state, od, od_ssa, od_asym )
    call od%copy_out(      od_a      )
    call od_ssa%copy_out(  od_ssa_a  )
    call od_asym%copy_out( od_asym_a )

    call assert( 990690356, almost_equal( od_a(2),      0.92_rk * 0.35_rk ) )
    call assert( 359278219, almost_equal( od_ssa_a(4),  0.92_rk * 0.75_rk * 0.88_rk ) )
    call assert( 754071813, almost_equal( od_asym_a(1), 0.92_rk * 0.27_rk * 0.88_rk * 0.3_rk ) )

    deallocate( od      )
    deallocate( od_ssa  )
    deallocate( od_asym )
    deallocate( state   )
    deallocate( model   )

    ! c model
    model => c_model_t( test_my_model_create_c_model( ), owns_model = .true. )

    deallocate( model )

    ! c++ model
    model => cpp_model_t( test_my_model_create_cpp_model( ), owns_model = .true. )

    deallocate( model )

  end subroutine test_my_model_t

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end program test_my_model
