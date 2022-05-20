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

    !> Number of modes
    integer :: n_mode_
    !> Number of Species
    integer :: n_spec_
    !> Species Properties
    character(12), allocatable :: specname_(:)
    real(kind=rk), allocatable :: density_(:)
    logical, allocatable       :: l_core_(:,:)
    real(kind=rk), allocatable :: mass_to_m3_(:)
    real(kind=rk), allocatable :: ref_ind_real_(:,:)
    real(kind=rk), allocatable :: ref_ind_imag_(:,:)

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
    !> Aerosol Properties
    real(kind=rk), allocatable :: num_(:)    ! Number Conc [m-3]
    real(kind=rk), allocatable :: dg_(:)     ! Mode Number Diameter [um]
    real(kind=rk), allocatable :: sg_(:)     ! Mode Standard Deviation
    real(kind=rk), allocatable :: m3_(:)     ! Mode Third Moment [m3 m-3]
    real(kind=rk), allocatable :: vol_(:)    ! Mode Volume [m3 m-3]
    real(kind=rk), allocatable :: m_(:)      ! Mode Total Mass [ug m-3]
    real(kind=rk), allocatable :: frac_(:,:) ! Species Fraction in each Mode
    real(kind=rk), allocatable :: mass_(:,:) ! Species Mass in each mode [ug m-3]
    real(kind=rk) :: layer_thickness_        ! Thickness of atmospheric layer for optics calcs

  end type my_state_t

  interface my_model_t
    module procedure :: constructor
  end interface

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Creates and configure the aerosol model
  function constructor( description_file ) result( model )

    use aero_array,                    only : array_t
    use aero_util,                     only : assert_msg
#ifdef AERO_USE_NETCDF
    use netcdf,                        only : nf90_open, nf90_close,          &
                                              NF90_NOWRITE, NF90_NOERR
#endif
    type(my_model_t), pointer    :: model
    character(len=*), intent(in) :: description_file

    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    !! Set parameters/configuration data for the aerosol package here !!
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    ! Initialize the aerosol grid with wavelength data pulled from
    ! https://acp.copernicus.org/articles/18/7815/2018/acp-18-7815-2018-f03.pdf
    real(kind=rk) :: wavelengths(7) = & ! [nm]
      (/ 294.59_rk, 303.151_rk, 310.007_rk, 316.434_rk, 333.076_rk, 381.997_rk, 607.723_rk /)
    real(kind=rk) :: wave_numbers(7) ! [m-1]
    class(array_t), pointer :: interfaces

    integer :: i, netcdf_file
#ifdef AERO_USE_NETCDF
    ! access NetCDF data
    if( len_trim( description_file ) > 0 ) then
      call assert_msg( 724306399,                                             &
          nf90_open( trim( description_file ), NF90_NOWRITE, netcdf_file )    &
            == NF90_NOERR,                                                    &
          "Error opening NetCDF file '"//trim( description_file )//"'" )
      call assert_msg( 299736143, nf90_close( netcdf_file ) == NF90_NOERR,    &
          "Error closing NetCDF file '"//trim( description_file )//"'" )
    end if
#endif
    ! Convert to wave numbers for the grid's interfaces [m-1]
    do i = 1, 7
      wave_numbers(i) = 1.0e9_rk / wavelengths(8-i)
    end do
    interfaces => array_t( wave_numbers )

    allocate( model )
    model%grid_ = grid_t( interfaces )

    ! Load the averaged optical properties from
    ! https://acp.copernicus.org/articles/18/7815/2018/acp-18-7815-2018-f03.pdf
    allocate( model%tau_(   interfaces%size()  ) )
    allocate( model%omega_( interfaces%size()  ) )
    allocate( model%g_(     interfaces%size()  ) )

    model%tau_(:)   = (/ 0.5_rk, 0.75_rk, 0.75_rk, 0.75_rk, 0.75_rk, 0.75_rk, 0.75_rk /)
    model%omega_(:) = (/0.905_rk,0.88_rk, 0.88_rk, 0.88_rk, 0.88_rk, 0.88_rk, 0.88_rk /)
    model%g_(:)     = (/0.045_rk,0.09_rk, 0.09_rk, 0.09_rk, 0.09_rk, 0.09_rk, 0.09_rk /)

    ! Allocate the mode- and species-dependent variables
    model%n_mode_ = 3
    model%n_spec_ = 11

    allocate( model%specname_( model%n_spec_ ) )
    allocate( model%density_( model%n_spec_ ) )
    allocate( model%l_core_( model%n_mode_, model%n_spec_ ) )
    allocate( model%mass_to_m3_( model%n_spec_ ) )
    
    model%specname_(:) = (/'POA  ','SOA  ','EC   ','SO4  ','NO3  ','NH4  ','CL   ','NA   ','SOIL ','H2O  ','OTHER'/)
    model%density_(:)  = (/1400._rk,1400._rk,2200._rk,1800._rk,1800._rk,1800._rk,2200._rk,2200._rk,2600._rk,1000._rk,2200._rk/)
    model%l_core_(:,:) = .FALSE.
    model%l_core_(:,3) = .TRUE.
    model%mass_to_m3_(:) = 1.0e-9_rk * 6.0_rk / 3.1415_rk / model%density_(:)

    allocate( model%ref_ind_real_( model%n_spec_, interfaces%size() ) )
    allocate( model%ref_ind_imag_( model%n_spec_, interfaces%size() ) )

    ! POA -> ORGCARB
    model%ref_ind_real_(1,:) = (/  1.634_rk,   1.624_rk,   1.602_rk,   1.601_rk,   1.601_rk,   1.601_rk,   1.601_rk/)
    model%ref_ind_imag_(1,:) = (/1.56e-2_rk, 8.87e-2_rk, 1.17e-1_rk, 1.18e-1_rk, 1.18e-1_rk, 1.18e-1_rk, 1.18e-1_rk/)

    ! SOA -> APINENE_SOA
    model%ref_ind_real_(2,:) = (/  1.496_rk,   1.515_rk,   1.527_rk,   1.533_rk,   1.536_rk,   1.539_rk,   1.543_rk/)
    model%ref_ind_imag_(2,:) = (/2.09e-4_rk, 1.91e-4_rk, 6.89e-4_rk, 1.03e-3_rk, 1.23e-3_rk, 1.61e-3_rk, 1.91e-3_rk/)

    ! EC -> Soot
    model%ref_ind_real_(3,:) = (/  1.855_rk,   1.850_rk,   1.850_rk,   1.850_rk,   1.850_rk,   1.850_rk,   1.850_rk/)
    model%ref_ind_imag_(3,:) = (/7.14e-1_rk, 7.10e-1_rk, 7.10e-1_rk, 7.10e-1_rk, 7.10e-1_rk, 7.10e-1_rk, 7.10e-1_rk/)

    ! SO4 -> Solute
    model%ref_ind_real_(4,:) = (/  1.528_rk,   1.530_rk,   1.530_rk,   1.530_rk,   1.530_rk,   1.530_rk,   1.530_rk/)
    model%ref_ind_imag_(4,:) = (/7.00e-3_rk, 5.01e-3_rk, 6.01e-3_rk, 7.01e-3_rk, 7.40e-3_rk, 7.86e-3_rk, 1.04e-2_rk/)

    ! NO3 -> Solute
    model%ref_ind_real_(5,:) = model%ref_ind_real_(4,:) 
    model%ref_ind_imag_(5,:) = model%ref_ind_imag_(4,:)

    ! NH4 -> Solute
    model%ref_ind_real_(6,:) = model%ref_ind_real_(5,:) 
    model%ref_ind_imag_(6,:) = model%ref_ind_imag_(5,:)

    ! Cl -> SeaSalt
    model%ref_ind_real_(7,:) = model%ref_ind_real_(6,:) 
    model%ref_ind_imag_(7,:) = model%ref_ind_imag_(6,:)

    ! Na -> SeaSalt
    model%ref_ind_real_(8,:) = model%ref_ind_real_(7,:) 
    model%ref_ind_imag_(8,:) = model%ref_ind_imag_(7,:)

    ! Soil -> Dust
    model%ref_ind_real_(9,:) = (/  1.528_rk,   1.530_rk,   1.530_rk,   1.530_rk,   1.530_rk,   1.530_rk,   1.530_rk/)
    model%ref_ind_imag_(9,:) = (/8.00e-3_rk, 8.00e-3_rk, 8.00e-3_rk, 8.00e-3_rk, 8.00e-3_rk, 8.06e-3_rk, 1.04e-2_rk/)

    ! Water
    model%ref_ind_real_(10,:) = (/  1.333_rk,   1.353_rk,   1.362_rk,   1.366_rk,   1.368_rk,   1.370_rk,   1.373_rk/) 
    model%ref_ind_imag_(10,:) = (/5.25e-8_rk, 1.89e-9_rk, 2.91e-9_rk, 3.29e-9_rk, 3.54e-9_rk, 3.94e-9_rk, 4.45e-9_rk/)

    ! Other -> Soil
    model%ref_ind_real_(11,:) = model%ref_ind_real_(9,:) 
    model%ref_ind_imag_(11,:) = model%ref_ind_imag_(9,:)

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

    integer im, isp

    allocate( my_state_t :: state )
    select type( state )
    class is( my_state_t )

      !! create a working array for use in calculating optical properties
      allocate( state%od_work_( size( this%tau_ ) ) )

      !! Set some intial state (in a real simulation this would evolve over
      !! time)
      state%mixed_type_ = 0.92_rk
      state%layer_thickness_ = 200 ![m]
 
      allocate( state%num_( this%n_mode_ ) )
      allocate( state%dg_( this%n_mode_ ) )
      allocate( state%sg_( this%n_mode_ ) )
      allocate( state%m3_( this%n_mode_ ) )
      allocate( state%vol_( this%n_mode_ ) )
      allocate( state%m_( this%n_mode_ ) )
      allocate( state%frac_( this%n_mode_, this%n_spec_ ) )
      allocate( state%mass_( this%n_mode_, this%n_spec_ ) )
      state%num_(:)  = (/ 9.01e9_rk, 3.46e9_rk, 1.92e6_rk/)
      state%dg_(:)   = (/ 5.05e-2_rk,2.22e-1_rk,1.51e0_rk/) * 1.0e-6_rk
      state%sg_(:)   = (/ 2.04,      1.94,      1.84     /)
      state%m3_(:)   = (/ 0.0,       0.0,       0.0      /)
      state%vol_(:)  = (/ 0.0,       0.0,       0.0      /)
      state%m_(:)    = (/ 9.15,      203.0,     32.9     /)
      state%frac_(:,1) = (/ 0.112_rk, 0.0624_rk, 0.0000_rk /)
      state%frac_(:,2) = (/ 0.017_rk, 0.3810_rk, 0.0000_rk /)
      state%frac_(:,3) = (/ 0.084_rk, 0.0545_rk, 0.0000_rk /)
      state%frac_(:,4) = (/ 0.141_rk, 0.1330_rk, 9.2e-3_rk /)
      state%frac_(:,5) = (/ 0.201_rk, 0.0762_rk, 0.2170_rk /)
      state%frac_(:,6) = (/ 0.129_rk, 0.0659_rk, 0.0591_rk /)
      state%frac_(:,7) = (/ 0.000_rk, 7.8e-5_rk, 2.2e-3_rk /)
      state%frac_(:,8) = (/ 0.000_rk, 5.4e-4_rk, 0.0111_rk /)
      state%frac_(:,9) = (/ 0.000_rk, 0.0376_rk, 0.5310_rk /)
      state%frac_(:,10)= (/ 0.260_rk, 0.1600_rk, 0.1590_rk /)
      state%frac_(:,11)= (/ 0.057_rk, 0.0283_rk, 0.0116_rk /)

      do im = 1,this%n_mode_
        state%mass_(im,:) = state%frac_(im,:) * state%m_(im)

        do isp = 1,this%n_spec_
          state%m3_(im) = state%m3_(im) + &
                          state%m_(im) * this%mass_to_m3_(isp)
        end do
        
        if ( state%m3_(im) .gt. 1.0D-23 ) then
          state%vol_(im) = 3.1415/6. * state%m3_(im)
        end if
      end do

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
    use cmaq_aero_optics,              only : aero_optical_core_shell,   &
                                              aero_optical_mie

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

    integer im, isp, iv
    complex ri_shell, ri_core
    real(kind=rk) dg_core, dg_shell, m3_core, m3_shell, m3
    real(kind=rk)  r_core, r_shell, i_core, i_shell
    real(kind=rk), allocatable :: lambda(:), bext(:), bscat(:), &
                          gbar(:)
    real(kind=rk) f_core, f_shell, vol_core, vol_shell,         &
                  bext_mode, bscat_mode, gbar_mode
    integer, parameter :: nwv = 7
    logical success

    select type( state )
    class is( my_state_t )

      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      !! Calculate optical properties for the current aerosol state here !!
      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

      ! Initialize optics variables
      allocate( lambda( nwv ) )

      !???? How do I retrieve the wavelength grid ????
      !lambda(:) = 1.0e9_rk / this%grid_%clone( )  ! wavelength [nm]
      !lambda(:) = (/ 294.59_rk, 303.151_rk, 310.007_rk, 316.434_rk, 333.076_rk, 381.997_rk, 607.723_rk /)
      lambda(:) = (/ 607.723_rk, 381.997_rk, 333.076_rk, 316.434_rk, 310.007_rk, 303.151_rk, 294.59_rk  /)
      allocate( bext( nwv ) )
      allocate( bscat( nwv ) )
      allocate( gbar( nwv ) )
      bext  = 0.0_rk
      bscat = 0.0_rk
      gbar  = 0.0_rk

      ! Calculate core and shell fractions
      do iv = 1,nwv

        ! Loop through modes and species
        do im = 1,this%n_mode_
          ! Initialize variables aerosol core/shell properies
          dg_core  = 0.0_rk
          dg_shell = 0.0_rk
          m3_core  = 0.0_rk
          m3_shell = 0.0_rk
            
          r_core  = 0.0_rk
          i_core  = 0.0_rk 
          r_shell = 0.0_rk
          i_shell = 0.0_rk

          do isp = 1,this%n_spec_
     
            ! Initialize third moment
            m3 = this%mass_to_m3_(isp) * state%mass_(im,isp)
     
            if ( this%l_core_(im,isp) ) then
              ! Sum Core third moment
              m3_core = m3_core + m3
     
              ! Compute refractive indices
              r_core = r_core + m3 * this%ref_ind_real_(isp,iv)
              i_core = i_core + m3 * this%ref_ind_imag_(isp,iv)
            else
              ! Sum Shell third moment
              m3_shell = m3_shell + m3
     
              ! Compute refractive indices
              r_shell = r_shell + m3 * this%ref_ind_real_(isp,iv)
              i_shell = i_shell + m3 * this%ref_ind_imag_(isp,iv)
            end if
          end do
     
          ! Calculate core-shell fraction and effective core diameter
          f_core  = m3_core  / state%m3_(im)
          f_shell = 1.0 - f_core
     
          if ( f_core .lt. 1.0D-9 ) then
             dg_core = 0.0
          else
             dg_core = f_core ** (1./3.) * state%dg_(im)
          end if
          dg_shell = state%dg_(im)
     
          ! Calculate Mode-Dependent Refractive Indices for Core and Shell 
          if ( m3_core .gt. 0.0_rk ) then
              r_core = r_core / m3_core
              i_core = i_core / m3_core
          end if
          if ( m3_shell .gt. 0.0_rk ) then
              r_shell = r_shell / m3_shell
              i_shell = i_shell / m3_shell
          end if
     
          ! Calculate extinction and scattering coeeficients in [1/m] and 
          ! the asymmetry factor for aerosols. 
          ri_shell = cmplx( r_shell, i_shell )
     
          !if ( dg_core .gt. 0.0_rk .and. dg_core/dg_shell .lt. 0.999_rk ) then
              ! Solve the optical parameters for the core-shell morphology
          !    vol_core = 3.1415 / 6.0 * m3_core
          !    vol_shell = 3.1415 / 6.0 * m3_shell
     
          !    ri_core = cmplx( r_core, i_core )
     
          !    print *,''
          !    print *,'core/shell: iv=',iv,'  im=',im
          !    print *,'lambda=',lambda(iv)
          !    print *,'r_core=',r_core,'  i_core=',i_core
          !    print *,'r_shell=',r_shell,'  i_shell=',i_shell
          !    print *,'ri_core=',ri_core,'  ri_shell=',ri_shell
          !    print *,'vol_core=',vol_core,' vol_shell=',vol_shell
          !    print *,'dg_core=',dg_core,' dg_shell=',dg_shell
          !    print *,'sg=',state%sg_(im)

          !    call aero_optical_core_shell( 1.0e-3_rk*lambda(iv), ri_core, ri_shell, &
          !         vol_core, vol_shell, dg_core, dg_shell, state%sg_(im),           &
          !         bext_mode, bscat_mode, gbar_mode, success )
          !     print *,'Success = ',success
          !     print *,'bext_mode: ',bext_mode
          !     print *,'bscat_mode: ',bscat_mode
          !     print *,'gbar_mode: ',gbar_mode
          !else
              if ( dg_core/dg_shell .gt. 0.5_rk ) ri_shell = ri_core
              ! Assume one phase morphology
              print *,''
              print *,'mie: iv=',iv,'  im=',im
              print *,'lambda=',lambda(iv)
              print *,'ri_shell=',ri_shell
              print *,'vol=',state%vol_(im)
              print *,'dg_shell=',dg_shell
              print *,'sg=',state%sg_(im)

              call aero_optical_mie( 1.03e-3_rk*lambda(iv), ri_shell,state%vol_(im), &
                  dg_shell, state%sg_(im), bext_mode, bscat_mode, gbar_mode, success)
               print *,'success=',success
               print *,'bext_mode: ',bext_mode
               print *,'bscat_mode: ',bscat_mode
               print *,'gbar_mode: ',gbar_mode
          !end if
     
          ! Sum up Extinction and Scattering Coefficients, and Asymmetry Factor
          bext(iv)  = bext(iv)  + bext_mode
          bscat(iv) = bscat(iv) + bscat_mode
          gbar(iv)  = gbar(iv)  + bscat_mode * gbar_mode
          
          !print *,'iv = ',iv
          !print *,'bext=',bext(iv)
          !print *,'bscat=',bscat(iv)
          !print *,'gbar=',gbar(iv)

        end do  ! Modes
      end do    ! Wavelength

      ! aerosol optical depth    
      state%od_work_(:) = bext(:) * state%layer_thickness_
      call od%copy_in( state%od_work_ )

      ! aerosol single-scattering albedo
      state%od_work_(:) = bscat(:) / bext(:)
      call od_ssa%copy_in( state%od_work_ )

      ! aerosol asymmetric scattering optical depth
      state%od_work_(:) = gbar(:)
      call od_asym%copy_in( state%od_work_ )

    end select

  end subroutine compute_optics

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module my_model
