/*
 * RTC.c
 *
 *  Created on: Nov 26, 2017
 *      Author: monish
 */
#include "System_MKL25Z4.h"
#include "MKL25Z4.h"
#include <stdint.h>
#include "binary_logger.h"
#include "rtc.h"

uint32_t date_to_sec(void)
{
	return 808464432;
}

void RTC_configure(void)
{
	MCG_C1 |= MCG_C1_IRCLKEN_MASK; //Enable internal reference clock
	MCG_C2 &= ~(MCG_C2_IRCS_MASK);  //Internal Reference Clock -->Slow
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;  // Enable PORT C Gate Clock
	PORTC_PCR1 |= (PORT_PCR_MUX(0x1));       //PTC1 as RTC_CLKIN
	/*SIM_SOPT2 &= ~(SIM_SOPT2_CLKOUTSEL_MASK);
	SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL_MASK;
	SIM_SOPT1 &= ~(SIM_SOPT1_OSC32KSEL_MASK);
	SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL_MASK;*/
	SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0b10);  //32 Khz clock source for RTC
	SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b100); //Clockout pin
	PORTC_PCR3 |= (PORT_PCR_MUX(0x5)); //PTC3 as CLKOUT
	SIM_SCGC6 |= SIM_SCGC6_RTC_MASK; //    Enable RTC
	// Clear RTC Registers
	RTC_CR = RTC_CR_SWR_MASK;
	RTC_CR &= ~RTC_CR_SWR_MASK;
	//RTC_CR |= RTC_CR_OSCE_MASK;
	RTC_TPR = 0x7BFF;
	RTC_TSR = date_to_sec();
	RTC_TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);
	RTC_IER = RTC_IER_TSIE_MASK;		// Enable RTC Interrupt
	NVIC_EnableIRQ(RTC_Seconds_IRQn);
	__enable_irq();
	RTC_SR |= RTC_SR_TCE_MASK;
	return;
}

void RTC_Seconds_IRQHandler()
{
	uint8_t i=CB_buffer_add_item(&log_queue,HEARTBEAT);
	RTC_TPR = 0x7BFF;
	RTC_TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);
	RTC_SR |= RTC_SR_TCE_MASK;
	//Heartbeat
}
