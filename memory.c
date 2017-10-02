/*
 * memory.c
 *
 *  Created on: Sep 29, 2017
 *      Author: monish and sanika
 */
#include <stdlib.h>
#include <memory.h>
unsigned char* my_memmove(unsigned char* src, unsigned char* dst, size_t length)
{
	unsigned char i;
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

unsigned char* my_memcpy(unsigned char* src, unsigned char* dst, size_t length)
{
	unsigned char i;
	for(i=0;i<length;i++)
	{
		*(dst+i)=*(src+i);
	}
	return dst;
}

int8_t* my_memset(unsigned char* src, size_t length, unsigned char value)
{
	unsigned char i;
	for(i=0;i<length;i++)
	{
		*(src+i)=value;
	}
	return src;
}

unsigned char* my_memzero(unsigned char* src, size_t length)
{
	unsigned char i;
	for(i=0;i<length;i++)
	{
		*(src+i)=0;
	}
	return src;
}

unsigned char* my_reverse(unsigned char* src, size_t length)
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
int32_t* src;
size_t arr[length];
src=&arr;
return src;
}

void free_words(int32_t* src)
{
src=NULL;
}
