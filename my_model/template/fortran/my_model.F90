! Copyright (C) 2022 National Center for Atmospheric Research,
! National Technology & Engineering Solutions of Sandia, LLC (NTESS),
! and the U.S. Environmental Protection Agency (USEPA)
!
! SPDX-License-Identifier: Apache-2.0
!
module my_model

  use aero_constants,                  only : rk => real_kind
  use aero_grid,                       only : grid_t
  use aero_model,                      only : model_t
  use aero_state,                      only : state_t

  implicit none
  private

  public :: my_model_t

  !> Aerosol model parameters
  type, extends(model_t) :: my_model_t
    private
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    !! Put here configuration data for your aerosol package, parameters !!
    !! that do not vary during the course of a simulation.              !!
    !!                                                                  !!
    !! In this simplified example we include the wave number grid for   !!
    !! aerosol optical properties, as well as optical properties for    !!
    !! "mixed-type" aerosols.                                           !!
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    !> Optics grid in wave number [m-1]
    type(grid_t) :: grid_
    !> Aerosol optical depth [m]
    real(kind=rk), allocatable :: tau_(:)
    !> Single scattering albedo [-]
    real(kind=rk), allocatable :: omega_(:)
    !> Asymmetry parameter [-]
    real(kind=rk), allocatable :: g_(:)
  contains
    procedure :: name => model_name
    procedure :: create_state
    procedure :: optics_grid
    procedure :: compute_optics
  end type my_model_t

  !> Aerosol state specific to this model
  type, extends(state_t) :: my_state_t
    private
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    !! Put here state information for aerosols described by your aerosol      !!
    !! package, properties of the aerosol system that vary during the course  !!
    !! of a simulation.                                                       !!
    !!                                                                        !!
    !! In this simplified example, we track relative differences from         !!
    !! measured averages of mixed-type aerosols for each grid cell from       !!
    !! https://acp.copernicus.org/articles/18/7815/2018/acp-18-7815-2018.pdf  !!
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    !> Normalized mixed-type aerosol
    real(kind=rk), allocatable :: mixed_type_
    !> Working array for calculating optical depths
    real(kind=rk), allocatable :: od_work_(:)
  end type my_state_t

  interface my_model_t
    module procedure :: constructor
  end interface

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates and configure the aerosol model
  function constructor( description_file ) result( model )

    use aero_array,                    only : array_t

    type(my_model_t), pointer    :: model
    character(len=*), intent(in) :: description_file

    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    !! Set parameters/configuration data for the aerosol package here !!
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    ! Initialize the aerosol grid with wavelength data pulled from
    ! https://acp.copernicus.org/articles/18/7815/2018/acp-18-7815-2018-f03.pdf
    real(kind=rk) :: wavelengths(4) = & ! [nm]
      (/ 440.0_rk, 675.0_rk, 870.0_rk, 1020.0_rk /)
    real(kind=rk) :: wave_numbers(4) ! [m-1]
    class(array_t), pointer :: interfaces

    integer :: i

    ! Convert to wave numbers for the grid's interfaces [m-1]
    do i = 1, 4
      wave_numbers(i) = 1.0e-9_rk / wavelengths(5-i)
    end do
    interfaces => array_t( wave_numbers )

    allocate( model )
    model%grid_ = grid_t( interfaces )

    ! Load the averaged optical properties from
    ! https://acp.copernicus.org/articles/18/7815/2018/acp-18-7815-2018-f03.pdf
    allocate( model%tau_(   interfaces%size()  ) )
    allocate( model%omega_( interfaces%size()  ) )
    allocate( model%g_(     interfaces%size()  ) )

    model%tau_(:)   = (/ 0.27_rk,  0.35_rk,   0.5_rk, 0.75_rk /)
    model%omega_(:) = (/ 0.88_rk, 0.895_rk, 0.905_rk, 0.88_rk /)
    model%g_(:)     = (/  0.3_rk, 0.035_rk, 0.045_rk, 0.09_rk /)

  end function constructor

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns the name of the aerosol model/package
  function model_name( this )

    character(len=:), allocatable :: model_name
    class(my_model_t), intent(in) :: this

    model_name = "my model"

  end function model_name

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns a newly created aerosol state
  function create_state( this ) result( state )

    class(state_t),    pointer    :: state
    class(my_model_t), intent(in) :: this

    allocate( my_state_t :: state )
    select type( state )
    class is( my_state_t )

      !! create a working array for use in calculating optical properties
      allocate( state%od_work_( size( this%tau_ ) ) )

      !! Set some intial state (in a real simulation this would evolve over
      !! time)
      state%mixed_type_ = 0.92_rk

    end select

  end function create_state

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns the aerosol optics grid, discretized in wavenumber space
  function optics_grid( this )

    !> Copy of optical property wave number grid
    type(grid_t) :: optics_grid
    !> My aerosol model
    class(my_model_t), intent(in) :: this

    optics_grid = this%grid_%clone( )

  end function optics_grid

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Computes optical property data, given an aerosol state and destination
  !! arrays
  subroutine compute_optics( this, state, od, od_ssa, od_asym )

    use aero_array,                    only : array_t

    !> My aerosol model
    class(my_model_t), intent(inout) :: this
    !> Aerosol state
    class(state_t),    intent(inout) :: state
    !> Aerosol optical depth [m]
    class(array_t),    intent(inout) :: od
    !> Aerosol scattering optical depth [m]
    class(array_t),    intent(inout) :: od_ssa
    !> Aerosol asymmetric scattering optical depth [m]
    class(array_t),    intent(inout) :: od_asym

    select type( state )
    class is( my_state_t )

      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      !! Calculate optical properties for the current aerosol state here !!
      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

      ! aerosol optical depth
      state%od_work_(:) = state%mixed_type_ * this%tau_(:)
      call od%copy_in( state%od_work_ )

      ! aerosol scattering optical depth
      state%od_work_(:) = state%od_work_(:) * this%omega_(:)
      call od_ssa%copy_in( state%od_work_ )

      ! aerosol asymmetric scattering optical depth
      state%od_work_(:) = state%od_work_(:) * this%g_(:)
      call od_asym%copy_in( state%od_work_ )

    end select

  end subroutine compute_optics

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module my_model
