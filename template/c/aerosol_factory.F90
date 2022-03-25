! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Builder of aerosol model objects

!> The create_aerosol and related functions
module ai_aerosol_factory

  use ai_aerosol,                      only : aerosol_t
  use ai_c_aerosol,                    only : c_aerosol_t
  use ai_cpp_aerosol,                  only : cpp_aerosol_t
  use my_aerosol,                      only : my_aerosol_t

  implicit none
  private

  public :: create_aerosol, is_fortran_aerosol, create_fortran_aerosol

contains

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Builder of all-language aerosol model objects
  function create_aerosol( package_name, description_file ) result( aerosol )

    use ai_util,                       only : die_msg

    class(aerosol_t), pointer    :: aerosol
    character(len=*), intent(in) :: package_name
    character(len=*), intent(in) :: description_file

    aerosol => c_aerosol_t( package_name, description_file )
    if( .not. associated( aerosol ) ) then
      aerosol => cpp_aerosol_t( package_name, description_file )
    endif
    if( .not. associated( aerosol ) ) then
      call die_msg( 743895691, "Aerosol package '"//package_name//            &
                               "'not supported" )
    end if

  end function create_aerosol

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Returns whether a aerosol model is supported in Fortran
  pure logical function is_fortran_aerosol( package_name )

    character(len=*), intent(in) :: package_name

    is_fortran_aerosol = .false.

  end function is_fortran_aerosol

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  !> Builder of Fortran aerosol model objects
  function create_fortran_aerosol( package_name, description_file )           &
      result( aerosol )

    use ai_util,                       only : die_msg

    class(aerosol_t), pointer    :: aerosol
    character(len=*), intent(in) :: package_name
    character(len=*), intent(in) :: description_file

    call die_msg( 611497899, "Aerosol package '"//package_name//              &
                             "'not supported in Fortran" )

  end function create_fortran_aerosol

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end module ai_aerosol_factory
