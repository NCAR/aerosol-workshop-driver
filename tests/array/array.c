/* Copyright (C) 2022 National Center for Atmospheric Research,
 * National Technology & Engineering Solutions of Sandia, LLC (NTESS),
 * and the U.S. Environmental Protection Agency (USEPA)
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <aero/aero.h>
#include <aero/array/array.h>
#include <aero/array/cpp_array.h>
#include <aero/array/fortran_array.h>
#include <stdio.h>
#include "array_helper.h"

void *test_array_create_fortran_array();
void test_array_check_fortran_array(void* f_array, int index, aero_real_t value);

int main(const int argc, const char *argv[]) {

  aero_array_t *a, *b;
  aero_real_t ra[] = {12.5, 32.6, -132.45, 0.0};
  aero_real_t rb[4];

  a = aero_array_from_array(4, ra);
  AERO_ASSERT(a->size(a) == 4);
  a->copy_out(a, rb);
  AERO_ASSERT(almost_equal(rb[2], -132.45));
  a->free(a);
  a = aero_array_from_dimensions(4, 32.4);
  AERO_ASSERT(a->size(a) == 4);
  a->copy_out(a, rb);
  AERO_ASSERT(almost_equal(rb[2], 32.4));
  rb[2] = 94.32;
  a->copy_in(a, rb);
  AERO_ASSERT(almost_equal(rb[2], 94.32));
  b = a->clone(a);
  b->copy_out(b, rb);
  AERO_ASSERT(almost_equal(rb[2], 94.32));
  AERO_ASSERT(almost_equal(b->data(b)[2], 94.32));
  AERO_ASSERT(almost_equal(b->const_data(b)[2], 94.32));
  test_array_check_cpp_array(b->cpp_ptr(b), 2, 94.32);
  test_array_check_fortran_array(b->fortran_ptr(b), 2+1, 94.32);
  a->free(a);
  b->free(b);

  // fortran array
  a = aero_new_fortran_array(test_array_create_fortran_array(), true);
  AERO_ASSERT(a->size(a) == 4);
  a->copy_out(a, rb);
  AERO_ASSERT(almost_equal(rb[2], 0.623));
  a->copy_in(a, ra);
  a->copy_out(a, rb);
  AERO_ASSERT(almost_equal(rb[2], -132.45));
  b = a->clone(a);
  rb[2] = 0.0;
  b->copy_out(b, rb);
  AERO_ASSERT(almost_equal(rb[2], -132.45));
  AERO_ASSERT(almost_equal(b->data(b)[2], -132.45));
  AERO_ASSERT(almost_equal(b->const_data(b)[2], -132.45));
  test_array_check_fortran_array(b->fortran_ptr(b), 2+1, -132.45);
  a->free(a);
  b->free(b);

  // cpp array
  a = aero_new_cpp_array(test_array_create_cpp_array(), true);
  AERO_ASSERT(a->size(a) == 4);
  a->copy_out(a, rb);
  AERO_ASSERT(almost_equal(rb[2], -1e9));
  a->copy_in(a, ra);
  a->copy_out(a, rb);
  AERO_ASSERT(almost_equal(rb[2], -132.45));
  b = a->clone(a);
  rb[2] = 0.0;
  b->copy_out(b, rb);
  AERO_ASSERT(almost_equal(rb[2], -132.45));
  AERO_ASSERT(almost_equal(b->data(b)[2], -132.45));
  AERO_ASSERT(almost_equal(b->const_data(b)[2], -132.45));
  test_array_check_cpp_array(b->cpp_ptr(b), 2, -132.45);
  a->free(a);
  b->free(b);

  return 0;
}
