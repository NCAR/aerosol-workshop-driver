/* Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 *
 * Tests for the C Array type
 */

#include <aero/aero.h>
#include <aero/array/array.h>
#include <aero/array/cpp_array.h>
#include <aero/array/fortran_array.h>
#include <stdio.h>
#include "array_helper.h"

void *test_array_create_fortran_array();

int main(const int argc, const char *argv[]) {

  aero_array_t *a, *b;
  aero_real_t ra[] = {12.5, 32.6, -132.45, 0.0};
  aero_real_t rb[4];

  a = aero_array_from_array(4, ra);
  AERO_ASSERT(a->size(a) == 4);
  a->copy_out(a, rb);
  AERO_ASSERT(rb[2] == -132.45);
  a->free(a);
  a = aero_array_from_dimensions(4, 32.4);
  AERO_ASSERT(a->size(a) == 4);
  a->copy_out(a, rb);
  AERO_ASSERT(rb[2] == 32.4);
  rb[2] = 94.32;
  a->copy_in(a, rb);
  AERO_ASSERT(rb[2] == 94.32);
  b = a->clone(a);
  b->copy_out(b, rb);
  AERO_ASSERT(rb[2] == 94.32);
  a->free(a);
  b->free(b);

  // fortran array
  a = aero_fortran_array_wrap(test_array_create_fortran_array());
  AERO_ASSERT(a->size(a) == 4);
  a->copy_out(a, rb);
  AERO_ASSERT(rb[2] == 0.623);
  a->copy_in(a, ra);
  a->copy_out(a, rb);
  AERO_ASSERT(rb[2] == -132.45);
  b = a->clone(a);
  rb[2] = 0.0;
  b->copy_out(b, rb);
  AERO_ASSERT(rb[2] == -132.45);
  a->free(a);
  b->free(b);

  // cpp array
  a = aero_cpp_array_wrap(test_array_create_cpp_array());
  AERO_ASSERT(a->size(a) == 4);
  a->copy_out(a, rb);
  AERO_ASSERT(rb[2] == -1e9);
  a->copy_in(a, ra);
  a->copy_out(a, rb);
  AERO_ASSERT(rb[2] == -132.45);
  b = a->clone(a);
  rb[2] = 0.0;
  b->copy_out(b, rb);
  AERO_ASSERT(rb[2] == -132.45);
  a->free(a);
  b->free(b);

  return 0;
}
