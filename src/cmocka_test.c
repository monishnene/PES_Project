/*
 * Copyright 2008 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Use the unit test allocators */
#define UNIT_TESTING 1

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include <stdio.h>
#include "circbuf.h"
#include "conversion.h"
#include "memory.h"
#include <stdlib.h>

static int setup(void **state) {
    int *answer = malloc(sizeof(int));

    assert_non_null(answer);

    *answer = 1; 	

    *state = answer;

    return 0;
}

static int teardown(void **state) {
    free(*state);

    return 0;
}

/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state;
}

static void memmove_null_pointer_test(void **state) 
{
uint32_t* src = NULL;
uint32_t* dst = NULL;
uint32_t length=3;
src = my_memmove(src,dst,length);
if(src == NULL)
printf("Null Pointer Detected");
assert_int_equal(*answer, 1);
else
printf("No Null pointer");
assert_int_equal(*answer, 1);
}

static void memmove_no_overlap(void **state) {
(void) state;
my_memmove(src,dst,length);
}
static void memmove_SRC_in_DST(void **state) {
(void) state;
my_memmove(src,dst,length);
}
static void memmove_DST_in_SRC(void **state) {
(void) state;
my_memmove(src,dst,length);
}
static void memset_null_pointer_test(void **state) {
(void) state;
my_memset(src,length,value)
}
static void memset_check_region_set(void **state) {
(void) state;
my_memset(src,length,value)
}
static void memzero_null_pointer_test(void **state) {
(void) state;
my_memzero(src,length)
}
static void memzero_check_region_zero(void **state) {
(void) state;
my_memzero(src,length)
}
static void reverse_null_pointer_test(void **state) {
(void) state;
my_reverse(src,length) 
}
static void reverse_check_odd(void **state) {
(void) state;
my_reverse(src,length) 
}
static void reverse_check_even(void **state) {
(void) state;
my_reverse(src,length) 
}
static void reverse_check_all_chars(void **state) {
(void) state;
my_reverse(src,length) 
}
static void big_to_litte_null_pointer_test(void **state) {
(void) state;
big_to_little32(data,length)
}
static void big_to_litte_conversion_test(void **state) {
(void) state;
big_to_little32(data,length)
}
static void little_to_big_null_pointer_test(void **state) {
(void) state;
uint8_t little_to_big32(uint32_t * data, uint32_t length)
}
static void little_to_big_conversion_test(void **state) {
(void) state;
little_to_big32(data,length)
}
static void create_cicular_buffer(void **state) {
(void) state;
CB_init(cbptr,length)
}
static void circular_buffer_null_pointer_test(void **state) {
CB_peek(cbptr,position,store)
(void) state;
}
static void circular_buffer_initialized_test(void **state) {
CB_peek(cbptr,position,store)
(void) state;
}
static void circular_buffer_add_remove_test(void **state) {
(void) state;
CB_buffer_add_item(cbptr,data)
CB_buffer_remove_item(cbptr,store)
}
static void circular_buffer_full_test(void **state) {
CB_is_full(cbptr)
(void) state;
}
static void circular_buffer_empty_test(void **state) {
(void) state;
CB_is_empty(cbptr)
}
static void circular_buffer_wrap_add_test(void **state) {
(void) state;
CB_buffer_add_item(cbptr,data)
}
static void circular_buffer_wrap_remove_test(void **state) {
(void) state;
CB_buffer_remove_item(cbptr,store)
}
static void circular_buffer_overfill_test(void **state) {
(void) state;
CB_buffer_add_item(cbptr,data)
}
static void circular_buffer_overempty_test (void **state) {
(void) state;
CB_buffer_remove_item(cbptr,store)
}

/* A test case that does check if an int is equal. */
static void int_test_success(void **state) {
    int *answer = *state;
    
    assert_int_equal(*answer, 1);
}



int main(void) {
    const struct CMUnitTest tests[] = 
    {
	cmocka_unit_test(null_test_success),
        cmocka_unit_test_setup_teardown(int_test_success, setup, teardown),
	cmocka_unit_test_setup_teardown(memmove_null_pointer_test, setup, teardown),
	cmocka_unit_test_setup_teardown(memmove_no_overlap, setup, teardown),
	cmocka_unit_test_setup_teardown(memmove_SRC_in_DST, setup, teardown),
	cmocka_unit_test_setup_teardown(memmove_DST_in_SRC, setup, teardown),
	cmocka_unit_test_setup_teardown(memset_null_pointer_test, setup, teardown),
	cmocka_unit_test_setup_teardown(memset_check_region_set, setup, teardown),
	cmocka_unit_test_setup_teardown(memzero_null_pointer_test, setup, teardown),
	cmocka_unit_test_setup_teardown(memzero_check_region_zero, setup, teardown),
	cmocka_unit_test_setup_teardown(reverse_null_pointer_test, setup, teardown),
	cmocka_unit_test_setup_teardown(reverse_check_odd, setup, teardown),
	cmocka_unit_test_setup_teardown(reverse_check_even, setup, teardown),
	cmocka_unit_test_setup_teardown(reverse_check_all_chars, setup, teardown),
	cmocka_unit_test_setup_teardown(big_to_litte_null_pointer_test, setup, teardown),
	cmocka_unit_test_setup_teardown(big_to_litte_conversion_test, setup, teardown),
	cmocka_unit_test_setup_teardown(little_to_big_null_pointer_test, setup, teardown),
	cmocka_unit_test_setup_teardown(little_to_big_concersion_test, setup, teardown),
	cmocka_unit_test_setup_teardown(create_cicular_buffer, setup, teardown),
	cmocka_unit_test_setup_teardown(circular_bufffer_null_pointer_test, setup, teardown),
	cmocka_unit_test_setup_teardown(circular_buffer_initialized_test, setup, teardown),
	cmocka_unit_test_setup_teardown(circular_buffer_add_remove_test, setup, teardown),
	cmocka_unit_test_setup_teardown(circular_buffer_full_test, setup, teardown),
	cmocka_unit_test_setup_teardown(circular_buffer_empty_test, setup, teardown),
	cmocka_unit_test_setup_teardown(circular_buffer_wrap_add_test, setup, teardown),
	cmocka_unit_test_setup_teardown(circular_buffer_wrap_remove_test, setup, teardown),
	cmocka_unit_test_setup_teardown(circular_buffer_overfill_test, setup, teardown),
	cmocka_unit_test_setup_teardown(circular_buffer_overempty_test, setup, teardown),	
    };

    return cmocka_run_group_tests(tests, NULL, NULL);

}
