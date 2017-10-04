/*
 * memory.h
 *
 *  Created on: Sep 29, 2017
 *      Author: monish and sanika
 */

#ifndef MEMORY_H_
#define MEMORY_H_


unsigned char* my_memmove(unsigned char* src, unsigned char* dst, int length);
unsigned char* my_memcpy(unsigned char* src, unsigned char* dst, int length);
unsigned char* my_memset(unsigned char* src, int length, unsigned char value)
unsigned char* my_memzero(unsigned char* src, int length);
unsigned char* my_reverse(unsigned char* src, int length);
int* reserve_words( length);
void free_words(int* src);


#endif /* MEMORY_H_ */
