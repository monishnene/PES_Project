/*
 * Project3.c
 *
 *  Created on: Dec 2, 2017
 *      Author: monis
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "binary_logger.h"
#include "profiling.h"
#include "uart.h"
#include "System_MKL25Z4.h"
#include "MKL25Z4.h"
#include "rtc.h"
#include "memory.h"
#include "spi.h"
#include "nordic.h"
void profiling_task(void)
{
	uint8_t i=CB_buffer_add_item(&log_queue,PROFILING_STARTED);
	profiling(10);
	profiling(100);
	profiling(1000);
	profiling(5000);
	return;
}


/*
void spi_task(void)
{
	SPI_write_byte(6);
	uint8_t i = SPI_read_byte(5);
	if(i==5)
	{
		while((UART0_S1 & UART_S1_TDRE_MASK)==0);
		UART0_D = '5';
	}
	else if(i==6)
	{
		while((UART0_S1 & UART_S1_TDRE_MASK)==0);
		UART0_D = '6';
	}
	else
	{
		while((UART0_S1 & UART_S1_TDRE_MASK)==0);
		UART0_D = '7';
	}
}*/

/*
void nordic_task(void)
{

}*/

void project3(void)
{
	uint32_t time_data=0,i=0;
	uint8_t logger_id_call=0,flag=0;
	SystemInit();
	UART_configure();
	log_buffer_configure();
	SysTick_Init();
	SPI_init();
	nrf_write_config();
	nrf_read_config();
	RTC_configure();
	i=CB_buffer_add_item(&log_queue,LOGGER_INITIALIZED);
	i=CB_buffer_add_item(&log_queue,GPIO_INITIALIZED);
	i=CB_buffer_add_item(&log_queue,SYSTEM_INITIALIZED);
	while(1)
	{
		while(CB_is_empty(&log_queue)!= Buffer_Empty)
		{
			i=CB_buffer_remove_item(&log_queue,&logger_id_call);
			log_item(logger_id_call);
		}
		while(CB_is_empty(&buffer)!= Buffer_Empty)
		{
			UART_send(&buffer);
		}
		if(flag==0)
		{
			//nordic_task();
			//spi_task();
			flag++;
		}
		if(flag==1)
		{
			profiling_task();
			flag++;
		}
	}
}
