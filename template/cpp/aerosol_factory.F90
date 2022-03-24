! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Builder of aerosol model objects

!> The create_aerosol and related functions
module ai_aerosol_factory

  use ai_aerosol,                      only : aerosol_t

  implicit none
  private

  public :: create_aerosol, create_fortran_aerosol

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Builder of all-language aerosol model objects
  function create_aerosol( package_name, description_file ) result( aerosol )

    use ai_util,                       only : die_msg

    class(aerosol_t), pointer    :: aerosol
    character(len=*), intent(in) :: package_name
    character(len=*), intent(in) :: description_file

    ! assume model is in another language
    aerosol => aerosol_t( package_name, description_file )

  end function create_aerosol

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Builder of Fortran aerosol model objects
  function create_fortran_aerosol( package_name, description_file )           &
      result( aerosol )

    use ai_util,                       only : die_msg

    class(aerosol_t), pointer    :: aerosol
    character(len=*), intent(in) :: package_name
    character(len=*), intent(in) :: description_file

    call die_msg( 743895691, "Aerosol package '"//package_name//              &
                             "'not supported" )

  end function create_fortran_aerosol

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module ai_aerosol_factory
