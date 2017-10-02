/*
 * debug.c
 *
 *  Created on: Sep 29, 2017
 *      Author: monish 
 */
#include <debug.h>

void print_memory(uint8_t * start, uint32_t length)
{
	short i;
	for (i=0;i<length;i++)
	{
		printf("%x",*(start+i));
	}
}
