! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
module compute_aero_optics_mod

  implicit none

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Prints the usage statement for the driver
  subroutine usage()

    character(len=255) :: exe_name

    call get_command_argument(0, exe_name)
    print *, trim(exe_name), ": Usage:"
    print *, trim(exe_name), " <package_name> <input_file>"
    stop 3

  end subroutine usage

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> This helper creates an optical wavelength
  type(grid_t) function create_host_wavelength_grid( ) result( grid )

    use aero_array,                    only : array_t
    use aero_constants,                only : rk => real_kind
    use aero_grid,                     only : grid_t

    real(kind=rk) :: wavelengths(7) = & ! [nm]
      (/ 440.0_rk, 557.5_rk, 675.0_rk, 777.5_rk, 870.0_rk, 945.0_rk, 1020.0_rk /)
    real(kind=rk) :: wave_numbers(7) ! [m-1]
    class(array_t), pointer :: interfaces
    integer :: i

    ! Convert to wave numbers for the grid's interfaces [m-1]
    do i = 1, 7
      wave_numbers(i) = 1.0e-9_rk / wavelengths(8-i)
    end do
    interfaces => array_t( wave_numbers )

    grid = grid_t( interfaces )

  end function create_host_wavelength_grid

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> This helper creates an array whose data conforms to the given grid.
  function create_array_from_grid( grid ) result( array )

    use aero_array,                    only : array_t
    use aero_constants,                only : rk => real_kind
    use aero_grid,                     only : grid_t

    class(array_t), pointer    :: array
    type(grid_t),   intent(in) :: grid

    class(array_t), pointer :: interfaces

    interfaces => grid%interfaces( )
    array => array_t( interfaces%size( ), 0.0_rk )

  end function create_array_from_grid

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> This helper writes out array data to a file
  subroutine write_array_data( file_unit, array_name, array )

    use aero_array,                    only : array_t
    use aero_constants,                only : rk => real_kind

    integer,          intent(in) :: file_unit
    character(len=*), intent(in) :: array_name
    class(array_t),   intent(in) :: array

    real(kind=rk) :: array_data( array%size( ) )

    call array%copy_out( array_data )
    write(file_unit,*) array_name, " = ["
    write(file_unit,'(g0,",")') array_data
    write(file_unit,*) "]"

  end subroutine write_array_data

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> This helper outputs optical property data
  subroutine write_optics_data( file_name, grid, od, od_ssa, od_asym )

    use aero_array,                    only : array_t
    use aero_grid,                     only : grid_t
    use aero_util,                     only : assert, assert_msg

    character(len=*), intent(in) :: file_name
    type(grid_t),     intent(in) :: grid
    class(array_t),   intent(in) :: od, od_ssa, od_asym

    integer, parameter :: file_unit = 10
    integer :: io_status
    class(array_t), pointer :: interfaces

    open( unit = file_unit, file = file_name, action = 'WRITE',               &
          iostat = io_status )
    call assert_msg( 332319671, io_status == 0, "Error opening output file '" &
                                //file_name//"'")
    interfaces => grid%interfaces( )
    call assert( 429297390, interfaces%size( ) == od%size( )      )
    call assert( 201301927, interfaces%size( ) == od_ssa%size( )  )
    call assert( 648669773, interfaces%size( ) == od_asym%size( ) )

    write(file_unit,*) "# Grid interfaces"
    call write_array_data( file_unit, "interfaces", interfaces )
    write(file_unit,*) "# Aerosol optical depth [m]"
    call write_array_data( file_unit,      "od",      od )
    write(file_unit,*) "# Aerosol scattering optical depth [m]"
    call write_array_data( file_unit,  "od_ssa",  od_ssa )
    write(file_unit,*) "# Aerosol asymmetric scattering optical depth [m]"
    call write_array_data( file_unit, "od_asym", od_asym )

    close(file_unit)

  end subroutine write_optics_data

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

program compute_aero_optics

  use aero_array,                      only : array_t
  use aero_grid,                       only : grid_t
  use aero_interpolator,               only : interpolator_t
  use aero_model,                      only : model_t
  use aero_model_factory,              only : create_model
  use aero_state,                      only : state_t
  use compute_aero_optics_mod

  character(len=255) :: package_name, desc_file

  class(model_t), pointer :: model
  class(state_t), pointer :: state
  type(grid_t)            :: host_grid, aero_grid  ! wavelength grids for radiative properties
  class(array_t), pointer :: host_od, host_od_ssa, host_od_asym
  class(array_t), pointer :: aero_od, aero_od_ssa, aero_od_asym
  type(interpolator_t)    :: interp

  if (command_argument_count() < 2) then
    call usage()
  end if

  call get_command_argument(1, package_name)
  call get_command_argument(2, desc_file)

  ! Construct an aerosol model from the given package name and
  ! descriptor file.
  model => create_model( package_name, desc_file )

  ! Use the model to create an initial aerosol state.
  state => model%create_state( )

  ! The host wavelength grid to which optical properties are interpolated.
  host_grid = create_host_wavelength_grid();

  ! The grid the model uses to compute optical properties.
  aero_grid = model%optics_grid()

  ! An interpolator that interpolates data from aero_grid to host_grid,
  ! using a pre-selected scheme.
  interp = interpolator_t( aero_grid, host_grid )

  ! Make some arrays to store optical properties on the host and model grids.
  host_od      => create_array_from_grid( host_grid )
  host_od_ssa  => create_array_from_grid( host_grid )
  host_od_asym => create_array_from_grid( host_grid )
  aero_od      => create_array_from_grid( aero_grid )
  aero_od_ssa  => create_array_from_grid( aero_grid )
  aero_od_asym => create_array_from_grid( aero_grid )

  ! Have the aerosol model compute its optical properties on its native grid.
  call model%compute_optics( state, aero_od, aero_od_ssa, aero_od_asym )

  ! Interpolate the aerosol optics to the host grid.
  call interp%interpolate( aero_od,      host_od      )
  call interp%interpolate( aero_od_ssa,  host_od_ssa  )
  call interp%interpolate( aero_od_asym, host_od_asym )

  ! Output the results
  call write_optics_data( "fortran_host_results.py", host_grid, host_od,      &
                          host_od_ssa, host_od_asym )

  ! Free memory
  deallocate( model        )
  deallocate( state        )
  deallocate( host_od      )
  deallocate( host_od_ssa  )
  deallocate( host_od_asym )
  deallocate( aero_od      )
  deallocate( aero_od_ssa  )
  deallocate( aero_od_asym )

  write(*,*) "Finished!"

end program compute_aero_optics

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
