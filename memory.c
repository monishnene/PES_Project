/*
 * memory.c
 *
 *  Created on: Sep 29, 2017
 *      Author: monish
 */
#include <stdlib.h>

uint8_t* my_memmove(uint8_t* src, uint8_t* dst, size_t length)
{
	uint8_t i;
	for(i=0;i<length;i++)
	{
		if(dst==src+i)
		{
			dst=src+length;
			break;
		}
	}

	for(i=0;i<length;i++)
	{
		if(dst+length-1==src+i)
		{
			dst=src+length;
			break;
		}
	}

	for(i=0;i<length;i++)
	{
		*(dst+i)=*(src+i);
	}
	return dst;
}

uint8_t* my_memcpy(uint8_t* src, uint8_t* dst, size_t length)
{
	uint8_t i;
	for(i=0;i<length;i++)
	{
		*(dst+i)=*(src+i);
	}
	return dst;
}

int8_t* my_memset(uint8_t* src, size_t length, uint8_t value)
{
	uint8_t i;
	for(i=0;i<length;i++)
	{
		*(src+i)=value;
	}
	return src;
}

uint8_t* my_memzero(uint8_t* src, size_t length)
{
	uint8_t i;
	for(i=0;i<length;i++)
	{
		*(src+i)=0;
	}
	return src;
}

uint8_t* my_reverse(uint8_t* src, size_t length)
{
	char* temp;
	int i,n;
	if(length%2==0)
	{
		n=length/2;
	}
	else
	{
		n=(length-1)/2;
	}
	for(i=0;i<n;i++)
	{
		 temp = *(src+i);
		 *(src+i) = *(src+length-i-1);
		 *(src+length-i-1) = temp;
	}
	return src;
}

int32_t* reserve_words(size_t length)
{
int32_t* src = NULL;
src = int32_t* malloc(length);
return src;
}

void free_words(int32_t* src)
{
free(src);
}
