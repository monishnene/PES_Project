#include "MKL25Z4.h"
#include "memory.c"
#include "memory.h"
#include <stdint.h>

void main()
{

uint8_t* src;
uint8_t* dst;
uint8_t value;
uint8_t length;
uint8_t m[10];
uint8_t n[10];
src = uint8_t* malloc(10);
dst = uint8_t* malloc(10);
src = &m[0];
dst = &n[0];
length = 10;
value = 1;
memset_dma(src,length,value);
m = *(src)+*(src+1)+*(src+2)+*(src+3)+*(src+4)+*(src+5)+*(src+6)+*(src+7)+*(src+8)+*(src+9);
if(m==10)
printf("The data set is successful");
memmove_dma(src,dst,10);
n = *(dst)+*(dst+1)+*(dst+2)+*(dst+3)+*(dst+4)+*(dst+5)+*(dst+6)+*(dst+7)+*(dst+8)+*(dst+9);
if(n==10)
printf("The data tranfer is successful");

}
