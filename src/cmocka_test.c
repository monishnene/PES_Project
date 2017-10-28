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

uint8_t * src, dst,store,data;
uint8_t length,position,value;
Cb_t
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
src = NULL;
dst = NULL;
length=3;
src = my_memmove(src,dst,length);
if(src == NULL)
{
  printf("Null Pointer Detected");
  assert_int_equal(*answer, 1);
}
else
{
  printf("No Null pointer");
  assert_int_equal(*answer, 1);
}
}

static void memmove_no_overlap(void **state) {
int arr[8];
length = 8;
src = arr[0];
dst = arr[5];
dst= my_memmove(src,dst,length);
for(i=0;i<length-1;i++)
{
src+length = dst;
}
if( src!= dst)
{
  printf("No overlap observed");
  assert_int_equal(*answer, 1);
}
else 
{
  printf("Overlap observed");
  assert_int_equal(*answer, 1);
}
}
static void memmove_SRC_in_DST(void **state) {
uint8_t flag = 0;
src = arr[0];
dst = arr[7];
length = 8;
dst = my_memmove(src,dst,length);
flag=1;
for(i=0; i<length-1; i++)
{ 
  *(dst+length-1-i) = *(src+length-1-i);
}
if(dst == src+i)
{
printf("Source moved in destination");
assert_int_equal(*answer, 1);
}
else
{
printf("Source not moved in Destination");
assert_int_equal(*answer, 1);
}
}
static void memmove_DST_in_SRC(void **state) {
uint8_t flag = 0;
src = arr[0];
dst = arr[7];
length = 8;
dst= my_memmove(src,dst,length);
flag=0;
for(i=0; i<length-1; i++)
{ 
  *(dst+i)=*(src+i);
}
if(dst+length-1==src+i) 
{
printf("Destination moved in source");
assert_int_equal(*answer, 1);
}
else
{
printf("Destination not moved in source");
assert_int_equal(*answer, 1);
}
}

static void memset_null_pointer_test(void **state) {
src = NULL;
dst = NULL;
length = 3;
src = my_memset(src,length,value);
if(src == NULL)
{
printf("Null pointer Detected");
assert_int_equal(*answer, 1);
}
else
{
printf("No Null pointer");
assert_int_equal(*answer, 1);
}
}

static void memset_check_region_set(void **state) {

short i;
val = 0x80;
src = val;
length = 4;
src= my_memset(src,length,value);
for(i=0;i<length;i++)
{
  *(src+0) = 4;
  *(src+1) = 6;
  *(src+2) = 2;
  *(src+3) = 3;
}
if(*src==4623)
{
printf("The value is set to the memory location");
assert_int_equal(*answer, 1);
}
else
{
printf("The value is not set to the memory location");
assert_int_equal(*answer, 1);
}
}

static void memzero_null_pointer_test(void **state) {
src = NULL;
dst = NULL;
length = 3;
src = my_memzero(src,length);
if(src == NULL)
{
printf("Null pointer Detected");
assert_int_equal(*answer, 1);
}
else
{
printf("No Null pointer");
assert_int_equal(*answer, 1);
}
}
static void memzero_check_region_zero(void **state) {
uint8_t i;
uint8_t val = 0x40;
*src = 0;
src = val;
length = 4;
src = my_memzero(src,length);
for(i=0;i<length;i++)
{
  *(src+0)= 0;
  *(src+1)= 0;
  *(src+2)= 0;
  *(src+3)= 0;
}
if(*src==0)
{
printf("Memory location is cleared");
assert_int_equal(*answer, 1);
}
else 
{
printf("Memory location is not cleared");
assert_int_equal(*answer, 1);
}
}
static void reverse_null_pointer_test(void **state) {
src = NULL;
dst = NULL;
length = 3;
src = my_reverse(src,length); 
if(src == NULL)
{
printf("Null pointer Detected");
assert_int_equal(*answer, 1);
}
else
{
printf("No Null pointer");
assert_int_equal(*answer, 1);
}
}
static void reverse_check_odd(void **state) {
short i;
length = 3;
uint8_t arr[50];
src = &arr;
for(i=0;i<3;i++)
{
 *(src+i) = 9;
 *(src+i) = 6;
 *(src+i) = 7;
}
src = my_reverse(src,length);
if( *((src+i))==769)
{
printf("Odd string reversed");
assert_int_equal(*answer, 1);
}
else 
{
printf("Odd string not reversed");
assert_int_equal(*answer, 1);
}
}
static void reverse_check_even(void **state) {
short i;
length = 4;
uint8_t arr[50];
src = &arr;
for(i=0;i<4;i++)
{
*(src+i) = 9;
*(src+i) = 6;
*(src+i) = 7;
*(src+i) = 5;
}
src = my_reverse(src,length);
if( *((src+i))==5769)
{
printf("Even string reversed");
assert_int_equal(*answer, 1);
}
else
{
printf("Even string not reversed");
assert_int_equal(*answer, 1);
}
}
static void reverse_check_all_chars(void **state) {
short i;
length = 4;
uint8_t arr[50];
src = &arr;
for(i=0;i<3;i++)
{
*(src+i) = a;
*(src+i) = b;
*(src+i) = c;
}
src = my_reverse(src,length);
if( *((src+i))==cba)
{
printf("Char string reversed");
assert_int_equal(*answer, 1);
}
else
{
printf("Char string not reversed");
assert_int_equal(*answer, 1);
}
}
static void big_to_litte_null_pointer_test(void **state) {
data = NULL;
length = 4;
data = big_to_little32(data,length);
if(data == NULL)
{
printf("Null pointer Detected");
assert_int_equal(*answer, 1);
}
else 
{
printf("No Null pointer");
assert_int_equal(*answer, 1);
}
}
static void big_to_litte_conversion_test(void **state) {
short i;
int n;
unsigned int* data;
unsigned int arr[50];
data = &arr;
for(i=0;i<4;i++)
{
*(data+0) = 0;
*(data+1)=  2;
*(data+2) = 8;
*(data+3) = 7;
}
n= big_to_little32(data,4);
if( *((data+i))== 287)
{
printf("Big to little converted");
assert_int_equal(*answer, 1);
}
else 
{
printf("Big to little not converted");
assert_int_equal(*answer, 1);
}
}

static void little_to_big_null_pointer_test(void **state) {
 data = NULL;
length = 4;
data = big_to_little32(data,length);
if(data == NULL)
{
printf("Null pointer Detected");
assert_int_equal(*answer, 1);
}
else 
{
printf("No Null pointer");
assert_int_equal(*answer, 1);
}
}
static void little_to_big_conversion_test(void **state) {
short i;
int n;
unsigned int arr[50];
unsigned int* data = arr;
for(i=0;i<4;i++)
{
*(data+i) = 0;
*(data+i )= 2;
*(data+i) = 8;
*(data+i) = 7;
}
n= big_to_little32(data,4);
if( *((data+i)) == 000000000 20000000 80000000 70000000)
{
printf("little to big converted");
assert_int_equal(*answer, 1);
}
else
{
printf("Little to big not converted");
}
} 

static void create_cicular_buffer(void **state) {
length = 10;
cbptr=CB_init(cbptr, 10);
if(cbptr != NULL)
{
printf("Circular buffer initialized");
assert_int_equal(*answer, 1);
}
else
{
printf(" Circular buffer not initialized");
assert_int_equal(*answer, 1);
}
}
static void circular_buffer_null_pointer_test(void **state) {
cbptr == NULL;
cbptr= CB_peek(cbptr,position,store);
if(cbptr== NULL)
{
printf(" Null pointer detected");
assert_int_equal(*answer, 1)
}
else
{
printf(" No Null pointer");
assert_int_equal(*answer, 1);

}
static void circular_buffer_initialized_test(void **state) {

cbptr = CB_peek(cbptr,12,store);
if(cbptr== Success)
{
printf(" Circular buffer initialized");
assert_int_equal(*answer, 1);
}
else
{
printf("Circular buffer not initialized");
assert_int_equal(*answer, 1);
}

static void circular_buffer_add_remove_test(void **state) {
cbptr = CB_buffer_add_item(cbptr,data);
cbptr = CB_buffer_remove_item(cbptr,store);
}
static void circular_buffer_full_test(void **state) {
uint8_t i;
for(i=0;i<10;i++)
{
cbptr = CB_buffer_add_item(CB_t* cbptr,int8_t* data)
}
if(i == Buffer_Full)
{
printf("Circular buffer full");
assert_int_equal(*answer, 1);
}
else
{
printf(" Circular buffer not full");
assert_int_equal(*answer, 1);
}

static void circular_buffer_empty_test(void **state) {
uint8_t i;
for(i=0;i<10;i++)
{
cbptr = CB_buffer_remove_item(CB_t* cbptr,int8_t* store)
}
if(i == Buffer_Empty)
{
printf("Circular buffer Empty");
assert_int_equal(*answer, 1);
}
else
{
printf(" Circular buffer not Empty");
assert_int_equal(*answer, 1);
}


static void circular_buffer_wrap_add_test(void **state) {

cbptr = CB_buffer_add_item(cbptr,data);
}
static void circular_buffer_wrap_remove_test(void **state) {
cbptr = CB_buffer_remove_item(cbptr,store);
}
static void circular_buffer_overfill_test(void **state) {
uint8_t i;
Success = CB_is_full(cbptr);
for(i=0;i<5;i++)
{
cbptr = CB_buffer_add_item(cbptr,data);
}
if(i>10)
{
printf(" Circular buffer overfills");
assert_int_equal(*answer, 1);
}
else
{
printf("No overfill");
assert_int_equal(*answer, 1);
}

static void circular_buffer_overempty_test (void **state) {
uint8_t i;
Success = CB_is_empty(cbptr);
for(i=0;i<5;i++)
{
cbptr = CB_buffer_remove_item(cbptr,store);
}
if(i<0)
{
printf(" Circular buffer over empty");
assert_int_equal(*answer, 1);
}
else
{
printf(" Circular buffer not over empty");
assert_int_equal(*answer, 1);
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
