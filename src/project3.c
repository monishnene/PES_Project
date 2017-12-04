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
//#include "RTC.h"
#include "memory.h"
uint8_t m=0,n=0,i=0,length=10;
uint8_t* src;
uint8_t* dst;

void dma_test()
{
	uint32_t value = 1;
	src = (uint8_t*) malloc(10);
	dst = (uint8_t*) malloc(10);
	memset_dma(src,length,value);
	memmove_dma(src,dst,length);
}

void DMA0_IRQHandler()
{
	if(DMA_DSR_BCR0 == DMA_DSR_BCR_DONE_MASK)
	{
		DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
		while((UART0_S1 & UART_S1_TDRE_MASK)==0);
		UART0_D = *(src+i)+48;
		while((UART0_S1 & UART_S1_TDRE_MASK)==0);
		UART0_D = *(src+i)+48;
		while((UART0_S1 & UART_S1_TDRE_MASK)==0);
		UART0_D = *(dst+i)+48;
	}
	else
	{
		DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
	}
}


void project3(void)
{
	SystemInit();
	UART_configure();
	log_buffer_configure();
	//SPI_init();
	//RTC_configure();
	while((UART0_S1 & UART_S1_TDRE_MASK)==0);
	UART0_D = 'A';
	dma_test();
	log_item(LOGGER_INITIALIZED);
	log_item(GPIO_INITIALIZED);
	log_item(SYSTEM_INITIALIZED);
	while(CB_is_empty(&buffer)!=Buffer_Empty)
	{
		UART_send(&buffer);
	}
}
