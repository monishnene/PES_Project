#include "memory.c"
#include "memory.h"
#include <stdlib.h>
#include <stdint.h>

void size( uint16_t length, uint8_t case)
{
  length = 10;
  uint8_t* dst = uint8_t* malloc(length);
  uint8_t* src = uint8_t* malloc(length);
  uint8_t* i;
  uint8_t* j;
  uint8_t value = 5;
  i = my_memset = (src, length, value);
  
  switch (case)
   
  {
    case 1: 
    memset(src,value,length);
    memmove(dst,src,length);

    case 2: 
    
    src = my_memset(src, length, value);
    dst = my_memmove( src, dst, length);
    
    case 3:
 
     src = my_memset(src, length, value);
     dst = my_memmove( src, dst, length);
    

    case 4: 
    memset_dma(uint8_t *dst, uint32_t length);
    DMA_DAR0 = dma_st memmove_dma(uint8_t *src, uint8_t *dst, uint32_t length);

}
 
size(uint16_t 100, uint8_t case)
size(uint16_t 1000, uint8_t case)
size(uint16_t 5000, uint8_t case)

free_words(dst);
free_words(src);
return 0;
}
  





