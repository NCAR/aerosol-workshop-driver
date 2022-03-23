! Copyright (C) 2020 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Mock Fortran host model code

!> Mock Fortran host model
program host_model

  use ai_aerosol,                      only : aerosol_t

  implicit none

  class(aerosol_t), pointer :: aerosol

  ! do stuff

  write(*,*) "Finished!"

end program host_model
