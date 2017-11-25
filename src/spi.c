#include "MKL25Z4.h"
#include "SPI.h"

void SPI_init(void) {
	
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;
	PTC_BASE_PTR->PDDR |= 0x10; 
	PTC_BASE_PTR->PDOR |= 0x10; 
	PORTC->PCR[4] = PORT_PCR_MUX(1);  
	PORTC->PCR[5] = PORT_PCR_MUX(2);  
	PORTC->PCR[6] = PORT_PCR_MUX(2); 
	PORTC->PCR[7] = PORT_PCR_MUX(2); 

	PTC_BASE_PTR->PSOR = 1<<4;
	SPI0->C1 = 0x50;
	SPI0_BR = (SPI_BR_SPPR(0x03) | SPI_BR_SPR(0x08));  


void SPI_read_byte(uint8_t byte)
{

   uint8_t i=0;
   while ((SPI_status() & 0x10) == 0x10)
   i = SPI0->D;
   return 0;
}
                   

uint8_t SPI_write_byte(uint8_t byte) 

{
                uint8_t x;
                while ((SPI_status() & 0x20) != 0x20); 
		SPI0->D = x;
		while ((SPI_status() & 0x80) != 0x80); 
		return SPI0->D; 
}


void SPI_send_packet(uint8_t* p, size_t length)
{
             uint8_t i=0;
             while((SPI_status() & 0x20) != 0x20);
             for(i=0;i<length;i++)
          {
              SPI0->D = *(p+i);
          }
            while((SPI_status() & 0x80) != 0x80);
            return 0;
}

void spi_flush() 
{
	SPI0_C1&=0xBF;
	SPI_init();
}


