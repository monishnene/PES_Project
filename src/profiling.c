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
#include "binary_logger.h"
#include "profiling.h"
uint32_t pre_interrupt[8],post_interrupt[8],profiling_time[8];

void SysTick_Init() //Setup TDM
{
	SysTick-> LOAD = 0xFFFFFF;
	SysTick-> VAL = 0;
	SysTick-> CTRL |= 7;
	return;
}

/*********************************************************************
* Time calculation function
* pre_interrupt uses SysTick that has a LOAD pointer
* post_interrupt uses SysTick that has a LOAD pointer
* profiling time is the difference between pre and post interrupt
* returns profiling_time
***********************************************************************/

void time_start(uint8_t state)
{
	switch(state)
	{
	     pre_interrupt[state] = SysTick-> LOAD;
	     return;
	}
}

void time_end(uint8_t state)

{
	post_interrupt[state] = SysTick-> LOAD;
	profiling_time[state] = pre_interrupt[state] - post_interrupt[state];
	return;
}

void log_result(uint32_t length, uint8_t k)
{
		uint8_t i=0;
		uint8_t* profiling_time_ptr = (uint8_t*)&profiling_time[k];
		uint8_t* length_ptr = (uint8_t*)&length;
		k=CB_buffer_add_item(&log_buffer,(uint8_t)* &k);
		for(i=0;i<4;i++)
		{
			k=CB_buffer_add_item(&log_buffer,*(length_ptr+i));
		}
		for(i=0;i<4;i++)
		{
			k=CB_buffer_add_item(&log_buffer,*(profiling_time_ptr+i));
		}
		return;
}
/**********************************************************************
* Profiling function that is used for memset and memmove function
* Case 1 uses standard C version
* Case 2 uses memory function
* Case 3 uses memmory function using Optimized O3 flag
* Case 4 uses memset and memmove by using dma
* Free destination and free source
***********************************************************************/

void profiling(uint32_t length)
{
	uint8_t i=0;
	if(length>100)
	{
		loop_for_big_memory = length/100 + 1;
		length=100;
	}
	for(i=0;i<loop_for_big_memory;i++)
	{
		uint8_t* dst = (uint8_t*) malloc(length); //memory allocation to dst
		uint8_t* src = (uint8_t*) malloc(length); //memory allocation to src
		uint8_t i=0,j=0,k=0;
		time_start(k);
		src=memset((void*)src,(uint8_t)(k+1),4*length); //using standary C version memset
		time_end(k);
		log_result(length,k);
		k++;
		time_start(k);
		src=memmove((void*)dst,(void*)src,4*length);    //using standard C version memmove
		time_end(k);
		log_result(length,k);
		k++;
		time_start(k);
		src = my_memset(src, length, (uint8_t)k); //using memory function for memset
		time_end(k);
		log_result(length,k);
		k++;
		time_start(k);
		dst = my_memmove( src, dst, length);          //using memory function for memmove
		time_end(k);
		log_result(length,k);
		k++;
		time_start(k);
		src = my_memset(src, length, (uint8_t) k); //using memory function for memset by O3 flag
		time_end(k);
		log_result(length,k);
		k++;
		time_start(k);
		dst = my_memmove( src, dst, length);           //using memory function for memmove by O3 flag
		time_end(k);
		log_result(length,k);
		k++;
		time_start(k);
		memset_dma(src,length,k,1);                 //using memset function by dma
		time_end(k);
		log_result(length,k);
		k++;
		time_start(k);
		memmove_dma(src,dst,length,1);   // using memmove function by dma
		time_end(k);
		log_result(length,k);
		k++;
		free_words((uint32_t*)dst);                          //frees destination
		free_words((uint32_t*)src);                          //frees source
	}
	return;
}

void DMA0_IRQHandler(void)
{
		static uint8_t DMA_transfers_counter = 0,i=0;
		DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
		if(overlap_flag == 0)
		{
			DMA_transfers_counter++;
		}
		else
		{
			DMA_overlap_handler();
		}
		if(DMA_transfers_counter == 128)
		{
			i=CB_buffer_add_item(&log_queue,DATA_RECEIVED);
			i=CB_buffer_add_item(&log_queue,PROFILING_COMPLETED);
			i=CB_buffer_add_item(&log_queue,PROFILING_RESULT);
		}
}

