/*
 * memory.c
 *
 *  Created on: Sep 29, 2017
 *      Author: monish and sanika
 */
#include <stdlib.h>
unsigned char* my_memmove(unsigned char* src, unsigned char* dst, int length)
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
		if(dst+length-1==src+i) /*For handling overlap condition for every iteration*/
		{
			dst=src+length;
			break;
		}
	}

	for(i=0;i<length;i++)
	{
		*(dst+i)=*(src+i); /*Copies from source to destination for every iteration*/
	}
	return dst;
}

unsigned char* my_memcpy(unsigned char* src, unsigned char* dst, int length)
{
	unsigned char i;
	for(i=0;i<length;i++)
	{
		*(dst+i)=*(src+i); /*Copies from source to destination for every iteration*/
	}
	return dst;
}

unsigned char* my_memset(unsigned char* src, int length, unsigned char value)
{
	unsigned char i;
	for(i=0;i<length;i++)
	{
		*(src+i)=value; /*Sets the char value to the memory location for every iteration*/
	}
	return src;
}

unsigned char* my_memzero(unsigned char* src, int length)
{
	unsigned char i;
	for(i=0;i<length;i++)
	{
		*(src+i)=0; /*Clears the source location for every iteration*/
	}
	return src;
}


unsigned char* my_reverse(unsigned char* src, int length) /*Function for reversing bytes*/
{
	char* temp=NULL;
	int i,n;
	if(length%2==0) /*If the length is even*/
	{
		n=length/2;
	}
	else
	{
		n=(length-1)/2; /*If the length is odd*/
	}
	for(i=0;i<n;i++) /*Loop for reversing the bytes*/
	{
		 *temp = *(src+i);
		 *(src+i) = *(src+length-i-1);
		 *(src+length-i-1) = *temp;
	}
	return src;
}

int* reserve_words(int length)
{
int* src;
int arr[length];
src= arr; /*To reserve words = length in memory*/
return src;
}

void free_words(int* src) /*Function to free memory*/
{
src=NULL;
return;
}
