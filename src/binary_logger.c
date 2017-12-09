/*
 * binary_logger.c
 *
 *  Created on: Nov 25, 2017
 *      Author: monish
 */

#include "circbuf.h"
#include "uart.h"
#include "binary_logger.h"
#include "conversion.h"
#include <stdint.h>
#include "System_MKL25Z4.h"
#include "MKL25Z4.h"
#include "profiling.h"
#define log_size 100
#define log_queue_size 20

/********************************************************************
 * @brief log_buffer_configure()
 * Function that is used to configure the log_buffer
 *
 ********************************************************************/

void log_buffer_configure(void)
{
	uint8_t i;
	i = CB_init(&log_information,log_size);
	log_information.head = log_information.buffptr;
	log_information.tail = log_information.buffptr;
	log_information.count = 0;
	log_information.length = log_size;
	i = CB_init(&log_error,log_size);
	log_error.head = log_error.buffptr;
	log_error.tail = log_error.buffptr;
	log_error.count = 0;
	log_error.length = log_size;
	i = CB_init(&log_warning,log_size);
	log_warning.head = log_warning.buffptr;
	log_warning.tail = log_warning.buffptr;
	log_warning.count = 0;
	log_warning.length = log_size;
	i = CB_init(&log_profiling_result,4*log_size);
	log_profiling_result.head = log_profiling_result.buffptr;
	log_profiling_result.tail = log_profiling_result.buffptr;
	log_profiling_result.count = 0;
	log_profiling_result.length = log_size;
	i = CB_init(&log_queue,log_queue_size);
	log_queue.head = log_queue.buffptr;
	log_queue.tail = log_queue.buffptr;
	log_queue.count = 0;
	log_queue.length = log_size;
	return;
}
/*********************************************************
 * @brief log_item(uint8_t log_id_current)
 * Function that generates log_item
 * It handles different cases
 * CASE Logger is initialized
 * CASE GPIO is initialized
 * CASE SYSTEM_INITIALIZED
 * CASE SYSTEM_HALTED
 * CASE ERROR
 * CASE INFO
 * CASE WARNING
 * CASE PROFILING_STARTED
 * CASE PROFILING_RESULT
 * CASE DATA_RECEIVED
 * CASE PROFILING_COMPLETED
 * CASE DATA_ANALAYSIS_STARTED
 * CASE DATA_ALPHA_COUNT
 * CASE DATA_PUNCTUATION_COUNT
 * CASE DATA_NUMERIC_COUNT
 * CASE DATA_MISC_COUNT
 * CASE DATA_ANALYSIS_COMPLETED
 * CASE HEARTBEAT
 ********************************************************************************/
void log_item(uint8_t log_id_current)
{
	uint32_t real_time=RTC_TSR;;
	uint32_t* real_time_ptr= &real_time;
	uint32_t count=0,i=0,j=0,count_char=0;
	uint8_t temp=0,header='!';
	uint8_t* temp_ptr = &temp;
	count+=log_string(&header,1);
	count+=log_string(&log_id_current,1);
	count+=log_data(real_time_ptr,1);
	switch(log_id_current)
	{
		case LOGGER_INITIALIZED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case GPIO_INITIALIZED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case SYSTEM_INITIALIZED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case SYSTEM_HALTED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case INFO:
		{
			count+=log_integer(log_information.count);
			while(CB_is_empty(&log_information)!=Buffer_Empty)
			{
				j = CB_buffer_remove_item(&log_information,temp_ptr);
				count += log_string(temp_ptr,1);
			}
			count+=log_integer(count);
			break;
		}

		case WARNING:
		{
			count+=log_integer(log_warning.count);
			while(CB_is_empty(&log_warning)!=Buffer_Empty)
			{
				j = CB_buffer_remove_item(&log_warning,temp_ptr);
				count += log_string(temp_ptr,1);
			}
			count+=log_integer(count);
			break;
		}

		case ERROR:
		{
			count+=log_integer(log_error.count);
			while(CB_is_empty(&log_error)!=Buffer_Empty)
			{
				j = CB_buffer_remove_item(&log_error,temp_ptr);
				count += log_string(temp_ptr,1);
			}
			count+=log_integer(count);
			break;
		}

		case PROFILING_STARTED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case PROFILING_RESULT:
		{
			count+=log_integer(log_profiling_result.count);
			while(CB_is_empty(&log_profiling_result)!=Buffer_Empty)
			{
				j = CB_buffer_remove_item(&log_profiling_result,temp_ptr);
				count += log_string(temp_ptr,1);
			}
			count+=log_integer(count);
			break;
		}

		case DATA_RECEIVED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case PROFILING_COMPLETED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case DATA_ANALYSIS_STARTED:
		{
			count+=log_string(&log_id_current,1);
			count+=log_data(real_time_ptr,1);
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case DATA_ALPHA_COUNT:
		{
			count_char = get_alpha_count();
			count+=log_integer(1);
			count+=log_integer(count_char);
			count+=log_integer(count);
			break;
		}

		case DATA_NUMERIC_COUNT:
		{
			count_char = get_nums_count();
			count+=log_integer(1);
			count+=log_integer(count_char);
			count+=log_integer(count);
			break;
		}

		case DATA_PUNCTUATION_COUNT:
		{
			count_char = get_punc_count();
			count+=log_integer(1);
			count+=log_integer(count_char);
			count+=log_integer(count);
			break;
		}

		case DATA_MISC_COUNT:
		{
			count_char = get_misc_count();
			count+=log_integer(1);
			count+=log_integer(count_char);
			count+=log_integer(count);
			break;
		}

		case DATA_ANALYSIS_COMPLETED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case HEARTBEAT:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}
	}
}
/*****************************************************
 * @brief log_data 
 * Function that pushes the log data
 * returns the count for data
 *****************************************************/

uint32_t log_data(uint32_t* src, uint32_t length)
{
	uint8_t* src2=(uint8_t*) src;
	uint8_t i=0,k=0,count=0;
	for(i=0;i<4*length;i++)
	{
		CB_buffer_add_item(&buffer,*(src2+i));
		count += get_count_of_1(*src2+i);
	}
	return count;
}
/***************************************************
 * @brief log_string
 * Function that passes a log string
 * returns the count for string
 ***************************************************/
uint32_t log_string(uint8_t* src, uint32_t length)
{

	uint8_t i=0,k=0,count=0;
	for(i=0;i<length;i++)
	{
		CB_buffer_add_item(&buffer,*(src+i));
		count += get_count_of_1(*(src+i));
	}
	return count;
}
/***************************************************
 * @brief log_integer
 * Function that passes a log integer
 * returns the count for integer values
 ***************************************************/

uint32_t log_integer(uint32_t src)
{
	uint8_t i=0,j=0,k=0,count=0;
	uint8_t array[20];
	uint8_t* value = array;
	j = my_itoa(src,value,10);
	for(i=0;i<j;i++)
	{
		CB_buffer_add_item(&buffer,*(value+i));
		count += get_count_of_1(*(value+i));
	}
	return count;
}
/***************************************************
 * @brief log_flush
 * Function that flushes out the log
 * returns success or failure
 ***************************************************/

uint8_t log_flush(void)
{
	uint8_t i=CB_is_empty(&buffer);
	return i;
}
