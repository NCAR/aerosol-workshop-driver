// Copyright (C) 2022 National Center for Atmospheric Research,
// National Technology & Engineering Solutions of Sandia, LLC (NTESS),
// and the U.S. Environmental Protection Agency (USEPA)
//
// SPDX-License-Identifier: Apache-2.0
//
#include <aero/aero.hpp>
#include <aero/array/array.hpp>
#include <aero/array/c_array.hpp>
#include <aero/array/fortran_array.hpp>
#include <iostream>
#include "array_helper.c"

extern "C" {
  void *test_array_create_fortran_array();
  void test_array_check_fortran_array(void* f_array, int index, aero::Real value);
}

using Real = aero::Real;

int main(const int argc, const char *argv[]) {

  aero::Array *a, *b;
  std::vector<Real> ra {12.5, 32.6, -132.45, 0.0};
  std::vector<Real> rb;

  a = new aero::Array(ra);
  AERO_ASSERT(a->size() == 4);
  rb = std::vector<Real>(4);
  a->copy_out(rb);
  AERO_ASSERT(aero::almost_equal(rb[2], -132.45));
  delete a;
  a = new aero::Array(6);
  AERO_ASSERT(a->size() == 6);
  rb = std::vector<Real>(6);
  a->copy_out(rb);
  AERO_ASSERT(aero::almost_equal(rb[5], 0.0));
  delete a;
  a = new aero::Array(8, 12.3);
  AERO_ASSERT(a->size() == 8);
  rb = std::vector<Real>(8);
  a->copy_out(rb);
  AERO_ASSERT(aero::almost_equal(rb[7], 12.3));
  delete a;
  a = new aero::Array(4);
  a->copy_in(ra);
  AERO_ASSERT(a->size() == 4);
  rb = std::vector<Real>(4);
  a->copy_out(rb);
  AERO_ASSERT(aero::almost_equal(rb[2], -132.45));
  rb = std::vector<Real>(8);
  rb[7] = 12.3;
  *a = rb;
  AERO_ASSERT(a->size() == 8);
  rb[7] = 0.0;
  a->copy_out(rb);
  AERO_ASSERT(aero::almost_equal(rb[7], 12.3));
  b = a->clone();
  AERO_ASSERT(a->size() == 8);
  rb[7] = 0.0;
  a->copy_out(rb);
  AERO_ASSERT(aero::almost_equal(rb[7], 12.3));
  AERO_ASSERT(aero::almost_equal(a->data()[7], 12.3));
  AERO_ASSERT(aero::almost_equal((reinterpret_cast<const aero::Array*>(a))->data()[7], 12.3));
  test_array_check_c_array(a->c_ptr(), 7, 12.3);
  test_array_check_fortran_array(a->fortran_ptr(), 7+1, 12.3);
  delete a;
  delete b;

  // fortran array
  a = new aero::FortranArray(test_array_create_fortran_array(), true);
  AERO_ASSERT(a->size() == 4);
  rb = std::vector<Real>(4);
  a->copy_out(rb);
  AERO_ASSERT(aero::almost_equal(rb[2], 0.623));
  a->copy_in(ra);
  a->copy_out(rb);
  AERO_ASSERT(aero::almost_equal(rb[2], -132.45));
  b = a->clone();
  rb[2] = 0.0;
  b->copy_out(rb);
  AERO_ASSERT(aero::almost_equal(rb[2], -132.45));
  AERO_ASSERT(aero::almost_equal(a->data()[2], -132.45));
  AERO_ASSERT(aero::almost_equal((reinterpret_cast<const aero::Array*>(a))->data()[2], -132.45));
  test_array_check_fortran_array(a->fortran_ptr(), 2+1, -132.45);
  delete a;
  delete b;

  // c array
  a = new aero::CArray(test_array_create_c_array(), true);
  AERO_ASSERT(a->size() == 4);
  rb = std::vector<Real>(4);
  a->copy_out(rb);
  AERO_ASSERT(aero::almost_equal(rb[2], 0.523));
  a->copy_in(ra);
  a->copy_out(rb);
  AERO_ASSERT(aero::almost_equal(rb[2], -132.45));
  b = a->clone();
  rb[2] = 0.0;
  b->copy_out(rb);
  AERO_ASSERT(aero::almost_equal(rb[2], -132.45));
  AERO_ASSERT(aero::almost_equal(a->data()[2], -132.45));
  AERO_ASSERT(aero::almost_equal((reinterpret_cast<const aero::Array*>(a))->data()[2], -132.45));
  test_array_check_c_array(a->c_ptr(), 2, -132.45);
  delete a;
  delete b;

  return 0;
}
