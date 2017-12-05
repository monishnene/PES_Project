
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "System_MKL25Z4.h"
#include "MKL25Z4.h"

/***********************************************************************
 * @brief my_memmove()
 * copies a length of bytes from source to destination location without any overalp.
 * @src source pointer
 * @dst destination pointer
 * @length length of data to be transferred
 * @return destination pointer
 ***********************************************************************/
uint8_t* my_memmove(uint8_t* src, uint8_t* dst, uint32_t length)
{ uint8_t flag=0,i;
  if( (src !=NULL) && (dst !=NULL) && (length >=0) )
  {

	for(i=0;i<length;i++)
	{
		if(dst==src+i)
		{
			flag=1;
		}
	}

	for(i=0;i<length;i++)
	{
		if(dst+length-1==src+i) /*For handling overlap condition for every iteration*/
		{
			flag=0;
		}
	}
	if(flag==0)
	{
		for(i=0;i<length;i++)
		{
			*(dst+i)=*(src+i); /*Copies from source to destination for every iteration*/
		}
	}
	if(flag==1)
	{
		for(i=0;i<length;i++)
		{
			*(dst+length-1-i)=*(src+length-i-1); /*Copies from source to destination for every iteration*/
		}
	}

   return dst;
   }
   else if (src == NULL)
   {
   return src;
   }
   else
   {
   return dst;
   }
}

/***********************************************************************
 * @brief my_memcpy()
 * copies a length of bytes from source to destination location and it may or maynot corrupt the data.
 * @src source pointer
 * @dst destination pointer
 * @length length of data to be transferred
 * @return destination pointer
 ***********************************************************************/
uint8_t* my_memcpy(uint8_t* src, uint8_t* dst, uint32_t length)
{   uint8_t i;
    if( (src !=NULL) && (dst !=NULL) && (length >=0) )
    {

	for(i=0;i<length;i++)
	{
		*(dst+i)=*(src+i); /*Copies from source to destination for every iteration*/
	}
      }

	return dst;
}

/***********************************************************************
 * @brief my_memset()
 * sets a value to all the addresses given
 * @src source pointer
 * @value vallue to be set
 * @length length of data to be set
 * @return source pointer
 ***********************************************************************/
uint8_t* my_memset(uint8_t* src, uint32_t length, uint8_t value)
{
	uint8_t i;
        if( (src !=NULL) && (length >=0) )
  {
	for(i=0;i<length;i++)
	{
		*(src+i)=value; /*Sets the char value to the memory location for every iteration*/
	}

  }
	return src;
}

/***********************************************************************
 * @brief my_memzero()
 * initializes 0 to all the addresses given
 * @src source pointer
 * @length length of data to be set 0
 * @return source pointer
 ***********************************************************************/
uint8_t* my_memzero(uint8_t* src, size_t length)
{
	uint8_t i;
        if( (src !=NULL) && (length >=0) )
  {
	for(i=0;i<length;i++)
	{
		*(src+i)=0; /*Clears the source location for every iteration*/
	}
  }

	return src;
}

/***********************************************************************
 * @brief my_reverse()
 * reversing the bytes in a memory.
 * @src source pointer
 * @length length of data to be reversed
 * @return source pointer
 ***********************************************************************/
uint8_t* my_reverse(uint8_t* src, uint32_t length) /*Function for reversing bytes*/
{
	int8_t temp;
	size_t i,n;
        if( (src !=NULL) && (length >=0) )
      {
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
		 temp = *(src+i);
		 *(src+i) = *(src+length-i-1);
		 *(src+length-i-1) = temp;
	}
       }

	return src;

}

/***********************************************************************
 * @brief reserve_words()
 * allocate memory dynamically in heap
 * @length length of data to be allocated dynamically
 * @return pointer to starting address of the allocated memory
 ***********************************************************************/
int32_t* reserve_words(uint32_t length)
{
  int32_t* src;
  src=malloc(((sizeof(int32_t))*length)); /*To reserve words = length in memory*/
  if (src != NULL)
  {
     return src;
  }
     return src;
}

/***********************************************************************
 * @brief free_words()
 * deallocate memory allocated o a pointer
 * @src pointer whose dynamic memory is to be deallocated
 ***********************************************************************/
void free_words(uint32_t* src) /*Function to free memory*/
{
 if(src != NULL)
  {
    /* Free the dynamic memory allocation by calling free()*/
    free(src);
  }

return;
}
/***************************************************************************
*****************************************************************************/
void memmove_dma(uint8_t* src, uint8_t* dst, uint32_t length)
{
	uint8_t i=1,j=2,k=4;
		uint8_t a= 0,b=2,c=1;
		SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;
		SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
		DMAMUX0_CHCFG0 &= ~DMAMUX_CHCFG_ENBL_MASK;
		DMA_SAR0 = (uint32_t) src;
		DMA_DAR0 = (uint32_t) dst;

		/*if(length%k == 0)
		{
			DMA_DSR_BCR0 |= length;
			DMA_DCR0 &= ~DMA_DCR_SINC_MASK;
			DMA_DCR0 |= DMA_DCR_SSIZE(a);
			DMA_DCR0 |= DMA_DCR_DINC_MASK;
			DMA_DCR0 |= DMA_DCR_DSIZE(a);
		}*/
		/*else if(length%j == 0)
		{
			DMA_DSR_BCR0 |= length;
			DMA_DCR0 &= ~DMA_DCR_SINC_MASK;
			DMA_DCR0 |= DMA_DCR_SSIZE(b);
			DMA_DCR0 |= DMA_DCR_DINC_MASK;
			DMA_DCR0 |= DMA_DCR_DSIZE(b);
		}*/
		//else
		//{
			DMA_DSR_BCR0 |= length;
			DMA_DCR0 |= DMA_DCR_SINC_MASK;
			DMA_DCR0 |= DMA_DCR_SSIZE(c);
			DMA_DCR0 |= DMA_DCR_DINC_MASK;
			DMA_DCR0 |= DMA_DCR_DSIZE(c);

		//}
		/*DMA_DCR0 |= DMA_DCR_EINT_MASK;
		NVIC_EnableIRQ(DMA0_IRQn);
		__enable_irq;*/
		DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;
		DMA_DCR0 |= DMA_DCR_START_MASK;
		while(DMA_DSR_BCR0 != DMA_DSR_BCR_DONE_MASK);
		{
			DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
		}
	}

void memset_dma(uint8_t* dst, uint32_t length, uint32_t value)
{
	uint8_t i=1,j=2,k=4;
	uint8_t a= 0,b=2,c=1;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	DMAMUX0_CHCFG0 &= ~DMAMUX_CHCFG_ENBL_MASK;
	DMA_SAR0 = (uint32_t) &value;
	DMA_DAR0 = (uint32_t) dst;

	/*if(length%k == 0)
	{
		DMA_DSR_BCR0 |= length;
		DMA_DCR0 &= ~DMA_DCR_SINC_MASK;
		DMA_DCR0 |= DMA_DCR_SSIZE(a);
		DMA_DCR0 |= DMA_DCR_DINC_MASK;
		DMA_DCR0 |= DMA_DCR_DSIZE(a);
	}*/
	/*else if(length%j == 0)
	{
		DMA_DSR_BCR0 |= length;
		DMA_DCR0 &= ~DMA_DCR_SINC_MASK;
		DMA_DCR0 |= DMA_DCR_SSIZE(b);
		DMA_DCR0 |= DMA_DCR_DINC_MASK;
		DMA_DCR0 |= DMA_DCR_DSIZE(b);
	}*/
	//else
	//{
		DMA_DSR_BCR0 |= length;
		DMA_DCR0 &= ~DMA_DCR_SINC_MASK;
		DMA_DCR0 |= DMA_DCR_SSIZE(c);
		DMA_DCR0 |= DMA_DCR_DINC_MASK;
		DMA_DCR0 |= DMA_DCR_DSIZE(c);

	//}
	/*DMA_DCR0 |= DMA_DCR_EINT_MASK;
	NVIC_EnableIRQ(DMA0_IRQn);
	__enable_irq;*/
	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;
	DMA_DCR0 |= DMA_DCR_START_MASK;
	while(DMA_DSR_BCR0 != DMA_DSR_BCR_DONE_MASK);
	{
		DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
	}
}

