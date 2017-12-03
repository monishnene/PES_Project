#include "MKL25Z4.h"
#include "SPI.h"


/***********************************************************************
 Function that initializes the SPI

 ***********************************************************************/


void SPI_init(void) {
	// Enable clock network to SPI0
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;// Clock for PORT C
	SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;//Clock for SPI0
	PTC_BASE_PTR->PDDR |= 0x10; //Set pin 4 port C i.e PCS as output direction
	PTC_BASE_PTR->PDOR |= 0x10; //Set pin 4 port C i.e PCS as output
	PORTC->PCR[4] = PORT_PCR_MUX(1);  // PCS
	PORTC->PCR[5] = PORT_PCR_MUX(2);  
	PORTC->PCR[6] = PORT_PCR_MUX(2);  // MOSI
	PORTC->PCR[7] = PORT_PCR_MUX(2);  // MISO

	PTC_BASE_PTR->PSOR = 1<<4;//make gpio chip high
	SPI0->C1 = 0x50;// Enable SPI as master
	SPI0_BR = (SPI_BR_SPPR(0x03) | SPI_BR_SPR(0x08));     //Set  the baud rate prescale divisor to 3 & set baud rate divisor to 512 for baud rate of 15625 hz
}
/***********************************************************************
 * @brief SPI_write_byte  
 * It checks if the transmit buffer is empty and sends the data
 * It then checks if the transfer is complete i.e. receiver buffer is full 
 *  and then returns the data
 ***********************************************************************/

uint8_t SPI_write_byte(uint8_t byte) 

{
                uint8_t byte;
                while ((SPI_status() & 0x20) != 0x20); //Checks if the transfer buffer is empty
		SPI0->D = byte;//Send  the data
		while ((SPI_status() & 0x80) != 0x80); //if receive buffer is full then the transfer is complete
		return SPI0->D; //return the  data
}

/***********************************************************************
 * @brief SPI_flush()
 * Function that flushes out the SPI transmit and the recieve buffers

 ***********************************************************************/
void spi_flush() //To flush out the  spi transmit and recieve buffers
{
	SPI0_C1&=0xBF;
	SPI_init();
}

/***********************************************************************
 * @brief SPI_send_packet
 * It checks if the transmit buffer is empty and sends the packet
 * It then checks if the transfer is complete i.e. receiver buffer is full 

 ***********************************************************************/

void SPI_send_packet(uint8_t* p, size_t length) //To send the SPI packet
{
             uint8_t i=0;
             while((SPI_status() & 0x20) != 0x20); //Checks if the transfer buffer is empty
             for(i=0;i<length;i++)
          {
              SPI0->D = *(p+i); //Send the packet
          }
            while((SPI_status() & 0x80) != 0x80); //Check if the transfer is complete if the receive buffer is full
            return 0;
}

/***********************************************************************
 * @brief SPI_read_byte
 * It checks if the transfer is complete i.e. receiver buffer is full 
 * SPI byte is read

 ***********************************************************************/

void SPI_read_byte(uint8_t byte)
{

   uint8_t byte=0;
   while ((SPI_status() & 0x80) != 0x80); //If the receive buffer is full then the transfer is complete
   byte = SPI0->D; //Read the data 
   return 0; 
}
                
