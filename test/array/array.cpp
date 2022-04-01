// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
// Tests for the C Array type

#include <aero/aero.hpp>
#include <aero/array/array.hpp>
#include <assert.h>
#include <stdio.h>

int main(const int argc, const char *argv[]) {

  aero::Array a, b;
  std::vector<Real> ra {12.5, 32.6, -132.45, 0.0};
  std::vector<Real> rb;

  a = aero::Array(ra);
  assert(a.size() == 4 && "310989153");
  rb = std::vector<Real>(4);
  a.copy_out(rb);
  assert(rb[2] == -132.45 && "399796087");
  a = aero::Array(6);
  assert(a.size() == 6 && "229186888");
  rb = std::vector<Real>(6);
  a.copy_out(rb);
  assert(rb[5] == 0.0 && "954217971");
  a = aero::Array(8, 12.3);
  assert(a.size() == 8 && "990450653");
  rb = std::vector<Real>(8);
  a.copy_out(rb);
  assert(rb[7] == 12.3 && "257248785");
  a.copy_in(ra);
  assert(a.size() == 4 && "374379142");
  rb = std::vector<Real>(4);
  a.copy_out(rb);
  assert(rb[2] == -132.45 && "434123235");
  rb = std::vector<Real>(8);
  rb[7] = 12.3;
  a = rb;
  assert(a.size() == 8 && "704616631");
  rb[7] = 0.0;
  a.copy_out(rb);
  assert(rb[7] == 12.3 && "646778072");
  b = a;
  assert(a.size() == 8 && "755737644");
  rb[7] = 0.0;
  a.copy_out(rb);
  assert(rb[7] == 12.3 && "467998088");

  return 0;
}
