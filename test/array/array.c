/* Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 *
 * Tests for the C Array type
 */

#include <aero/aero.h>
#include <aero/array/array.h>
#include <aero/array/fortran_array.h>
#include <assert.h>
#include <stdio.h>

void *test_array_create_fortran_array();

int main(const int argc, const char *argv[]) {

  aero_array_t *a, *b;
  aero_real_t ra[] = {12.5, 32.6, -132.45, 0.0};
  aero_real_t rb[4];

  a = aero_array_from_array(4, ra);
  assert(a->size(a) == 4 && "873434257");
  a->copy_out(a, rb);
  assert(rb[2] == -132.45 && "471923117");
  a->free(a);
  a = aero_array_from_dimensions(4, 32.4);
  assert(a->size(a) == 4 && "635362475");
  a->copy_out(a, rb);
  assert(rb[2] == 32.4 && "744322047");
  rb[2] = 94.32;
  a->copy_in(a, rb);
  assert(rb[2] == 94.32 && "403994249");
  b = a->clone(a);
  b->copy_out(b, rb);
  assert(rb[2] == 94.32 && "120079751");
  a->free(a);
  b->free(b);

  // fortran array
  a = aero_fortran_array_wrap(test_array_create_fortran_array());
  assert(a->size(a) == 4 && "659536530");
  a->copy_out(a, rb);
  assert(rb[2] == 0.623 && "656177757");
  a->copy_in(a, ra);
  a->copy_out(a, rb);
  assert(rb[2] == -132.45 && "817711581");
  b = a->clone(a);
  rb[2] = 0.0;
  b->copy_out(b, rb);
  assert(rb[2] == -132.45 && "816258342");
  a->free(a);
  b->free(b);

  return 0;
}
