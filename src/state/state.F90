! Copyright (C) 2022 National Center for Atmospheric Research
! SPDX-License-Identifier: Apache-2.0
!
!> \file
!> Aerosol model state

!> The state_t type and related functions
module aero_state

  implicit none
  private

  public :: state_t

  type, abstract :: state_t
  end type state_t

end module aero_state
