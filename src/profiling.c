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


uint32_t time_calculation(/*parameter for function*/)
{
	uint32_t pre_interrupt=0,post_interrupt=0,profiling_time;
	pre_interrupt = SysTick-> LOAD;
	//memory transfer functions
	post_interrupt = SysTick-> LOAD;
	profiling_time = pre_interrupt - post_interrupt;
	return profiling_time;
}

void profiling( uint16_t length, uint8_t memory_function)
{
	uint8_t* dst = (uint8_t*) malloc(length);
	uint8_t* src = (uint8_t*) malloc(length);
	uint32_t value = 5;
	switch (memory_function)
	{
		case 1:
		src=memset((void*)src,(uint8_t)value,4*length);
		src=memmove((void*)dst,(void*)src,4*length);
		break;

		case 2:
		src = my_memset(src, length, (uint8_t)value);
		dst = my_memmove( src, dst, length);
		break;

		case 3:
		src = my_memset(src, length, (uint8_t) value);
		dst = my_memmove( src, dst, length);
		break;

		case 4:
		memset_dma(src,length,value);
		memmove_dma(src,dst,length);
		break;
	}
	free_words((uint32_t*)dst);
	free_words((uint32_t*)src);
	return;
}



