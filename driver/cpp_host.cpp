//===-- driver/cpp_host.cpp -------------------------------------*- C++ -*-===//
//
// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//
///
/// \file Mock C++ host model
///
//===----------------------------------------------------------------------===//

#include "interface/aerosol.hpp"
#include <iostream>

int main(const int argc, const char *argv[]) {

  ai::Aerosol aerosol;

  // do stuff

  std::cout << "Finished!";
}
