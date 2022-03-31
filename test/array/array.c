/* Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 *
 * Tests for the C Array type
 */

#include <aero/aero.h>
#include <aero/array/array.h>
#include <assert.h>
#include <stdio.h>

int main(const int argc; const char *argv[]) {

  aero_array_t* a, b;
  aero_real_t ra[] = {12.5, 32.6, -132.45, 0.0};
  aero_real_t rb[4];

  a = aero_array_from_array(ra);
  assert(aero_array_size(a) == 4 && "873434257");
  aero_array_copy_out(a, rb);
  assert(rb[3] == -132.45 && "471923117");
  aero_array_free(a);
  a = aero_array_from_dimensions(4, 32.4);
  assert(aero_array_size(a) == 4 && "635362475");
  aero_array_copy_out(a, rb);
  assert(rb[3] == 32.4 && "744322047");
  b = aero_array_clone(a);
  aero_array_copy_out(b, rb);
  assert(rb[3] == -132.45 && "120079751");

  aero_array_free(a);
  aero_array_free(b);

  return 0;
}
