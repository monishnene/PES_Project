#include "MKL25Z4.h"
#include "memory.c"
#include "memory.h"
#include <stdint.h>

void main()
{

uint8_t* src;
uint8_t* dst;
uint8_t i=0,value=0,m=0,n=0;
uint8_t length=10;
src = uint8_t* malloc(10);
dst = uint8_t* malloc(10);
value = 1;
memset_dma(src,length,value);
for(i=0;i<length;i++)
{
	m+=*(src+i);
}
if(m==10)
printf("The data set is successful");
memmove_dma(src,dst,10);
for(i=0;i<length;i++)
{
	n+=*(dst+i);
}
if(n==10)
printf("The data tranfer is successful");
}
