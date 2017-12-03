/*
 * profiling.c
 *
 *  Created on: Nov 30, 2017
 *      Author: monish
 */
#include "memory.h"
#include <stdint.h>
#include "System_MKL25Z4.h"
#include "MKL25Z4.h"
#include <stdlib.h>
#include <string.h>

/*********************************************************************
* Time calculation function
* pre_interrupt uses SysTick that has a LOAD pointer
* post_interrupt uses SysTick that has a LOAD pointer
* profiling time is the difference between pre and post interrupt
* returns profiling_time
***********************************************************************/

uint32_t time_calculation(/*parameter for function*/)
{
	uint32_t pre_interrupt=0,post_interrupt=0,profiling_time;
	pre_interrupt = SysTick-> LOAD; 
	//memory transfer functions
	post_interrupt = SysTick-> LOAD;
	profiling_time = pre_interrupt - post_interrupt;
	return profiling_time;
}
/**********************************************************************
* Profiling function that is used for memset and memmove function
* Case 1 uses standard C version 
* Case 2 uses memory function
* Case 3 uses memmory function using Optimized O3 flag
* Case 4 uses memset and memmove by using dma
* Free destination and free source 
***********************************************************************/

void profiling( uint16_t length, uint8_t memory_function)
{
	uint8_t* dst = (uint8_t*) malloc(length); //memory allocation to dst
	uint8_t* src = (uint8_t*) malloc(length); //memory allocation to src
	uint32_t value = 5;
	switch (memory_function)
	{
		case 1:
		src=memset((void*)src,(uint8_t)value,4*length); //using standary C version memset
		src=memmove((void*)dst,(void*)src,4*length);    //using standard C version memmove
		break;

		case 2:
		src = my_memset(src, length, (uint8_t)value); //using memory function for memset
		dst = my_memmove( src, dst, length);          //using memory function for memmove
		break;

		case 3:
		src = my_memset(src, length, (uint8_t) value); //using memory function for memset by O3 flag
		dst = my_memmove( src, dst, length);           //using memory function for memmove by O3 flag
		break;

		case 4:
		memset_dma(src,length,value);                 //using memset function by dma
		memmove_dma(src,dst,length);                  // using memmove function by dma
		break;
	}
	free_words((uint32_t*)dst);                          //frees destination
	free_words((uint32_t*)src);                          //frees source 
	return;
}



