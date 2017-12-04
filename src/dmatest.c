

#include "MKL25Z4.h"
#include "memory.h"
#include <stdint.h>
#include <stdlib.h>

void main()
{

uint8_t* src;
uint8_t* dst;
uint8_t i=0,m=0,n=0;
uint32_t value = 0;
uint32_t length=10;
src = (uint8_t*) malloc(10);
dst = (uint8_t*) malloc(10);
value = 1;
memset_dma(dst,length,value);
for(i=0;i<length;i++)
{
	m+=*(src+i);
}
memmove_dma(src,dst,10);
for(i=0;i<length;i++)
{
	n+=*(dst+i);
}
}
