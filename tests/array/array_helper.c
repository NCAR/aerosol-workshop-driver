/* Copyright (C) 2022 National Center for Atmospheric Research
 * SPDX-License-Identifier: Apache-2.0
 *
 * Support functions for C++/Fortran array tests
 */

#include <aero/aero.h>
#include <aero/array/array.h>

void *test_array_create_c_array() {
  aero_array_t *array;
  aero_real_t ra[] = {92.32, -129.4, 0.523, 13.4};
  return (void*) aero_array_from_array(4, ra);
}

void test_array_check_c_array(void* c_array, int index, aero_real_t value) {
  aero_array_t *array = (aero_array_t*) c_array;
  AERO_ASSERT(almost_equal(array->data(array)[index], value));
}
