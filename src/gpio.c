
#include "MKL25Z4.h"
#include "SPI.h"
#include "nordic.h"
#include "gpio.h"

void nrf_chip_enable (void) {PTC_BASE_PTR->PCOR = 1<<3;}
void nrf_chip_disable (void) {PTC_BASE_PTR->PSOR =  1<<3;}
void nrf_transmit_enable (void) {PTC_BASE_PTR->PCOR = 1<<3;}
void nrf_transmit_disable (void) {PTC_BASE_PTR->PSOR = 1<<3;}

void SPI_configure()
{
		SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;// Clock to PORT C
		SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;//Clock to SPI0
		PTC_BASE_PTR->PDDR |= 0x10; //Set pin 4 port C i.e PCS as output direction
		PTC_BASE_PTR->PDOR |= 0x10; //Set pin 4 port C i.e PCS as output
		PORTC->PCR[4] = PORT_PCR_MUX(1);   //Using Gpio for selecting chip
		PORTC->PCR[3] = PORT_PCR_MUX(2);
		PORTC->PCR[5] = PORT_PCR_MUX(2);  // SCK
		PORTC->PCR[6] = PORT_PCR_MUX(2);  // MOSI
		PORTC->PCR[7] = PORT_PCR_MUX(2);  //MISO
		PTC_BASE_PTR->PCOR = 1<<4;
		PTC_BASE_PTR->PCOR = 1<<3;
}

 void GPIO_nrf_configure()
 {
		SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;// Clock to PORT C
		//SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;//Clock to SPI0
		PTC_BASE_PTR->PDDR |= 0x10; //Set pin 4 port C i.e PCS as output direction
		PTC_BASE_PTR->PDOR |= 0x10; //Set pin 4 port C i.e PCS as output
		PORTC->PCR[4] = PORT_PCR_MUX(1);   //Using Gpio for selecting chip
		PORTC->PCR[3] = PORT_PCR_MUX(2);  // SCK
		PORTC->PCR[5] = PORT_PCR_MUX(2);  // SCK
		PORTC->PCR[6] = PORT_PCR_MUX(2);  // MOSI
		PORTC->PCR[7] = PORT_PCR_MUX(2);  //MISO
		GPIOC->PDDR |= 1<<4;
		GPIOC->PCOR |= 1<<4;
		GPIOC->PDDR |= 1<<3;
		GPIOC->PCOR |= 1<<3;
 }




