module compute_aero_optics_mod

  use ai_array, ai_grid, ai_model, ai_state

  implicit none

contains

  subroutine usage()
    character(len=255) :: exe_name

    call get_command_argument(0, exe_name)
    print *, trim(exe_name), ": Usage:\n"
    print *, trim(exe_name), " package_name> <input_file>\n"
    stop
  end subroutine

  ! This helper creates an array whose data conforms to the given grid.
  type(array_t) function create_array_from_grid(grid)
    type(grid_t), intent(in) :: grid

    type(array_t) :: array
    return array
  end function

  ! This helper plots the aerosol optics data on the given grid.
  subroutine plot_optics(grid, od, od_ssa, od_asym)
    type(grid_t),  intent(in) :: grid
    type(array_t), intent(in) :: od, od_ssa, od_asym
  end subroutine

end module


program compute_aero_optics

  character(len=255) :: package_name, desc_file

  model_t  :: model
  state_t  :: state
  grid_t   :: host_grid, aero_grid
  array_t  :: host_od, host_od_ssa, host_od_asym
  array_t  :: aero_od, aero_od_ssa, aero_od_asym
  interp_t :: interp

  if (command_argument_count() < 3) then
    call usage()
  end if

  call get_command_argument(1, package_name)
  call get_command_argument(2, desc_file)

  ! Construct an aerosol model from the given package name and
  ! descriptor file.
  model = create_model(package_name, desc_file)

  ! Use the model to create an aerosol state.
  state = ai_model_create_state(model)

  ! The host wavelength grid to which optical properties are interpolated.
  host_grid = create_host_wavelength_grid();

  ! The grid the model uses to compute optical properties.
  aero_grid = model%optics_grid()

  ! An interpolator that interpolates data from aero_grid to host_grid,
  ! using a pre-selected scheme.
  interp = create_interpolator(aero_grid, host_grid)

  ! Make some arrays to store optical properties on the host and model grids.
  host_od      = create_array_from_grid(host_grid)
  host_od_ssa  = create_array_from_grid(host_grid)
  host_od_asym = create_array_from_grid(host_grid)
  aero_od      = create_array_from_grid(aero_grid)
  aero_od_ssa  = create_array_from_grid(aero_grid)
  aero_od_asym = create_array_from_grid(aero_grid)

  ! Have the aerosol model compute its optical properties on its native grid.
  call model%compute_optics(model, state, aero_od, aero_od_ssa, aero_od_asym)

  ! Interpolate the aerosol optics to the host grid.
  call interp%interpolate(aero_od, host_od)
  call interp%interpolate(aero_od_ssa, host_od_ssa)
  call interp%interpolate(aero_od_asym, host_od_asym)

  ! Plot the results.
  call plot_optics(host_grid, host_od, host_od_ssa, host_od_asym)

  ! Clean up.
  call aero_od%free(aero_od)
  call aero_od_ssa%free(aero_od_ssa)
  call aero_od_asym%free(aero_od_asym)
  call host_od%free(host_od)
  call host_od_ssa%free(host_od_ssa)
  call host_od_sym%free(host_od_asym)

  call interp%free()
  call aero_grid%free()
  call host_grid%free()
  call state%free()
  call model%free()

end program
