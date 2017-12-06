



#include "MKL25Z4.h"
#include "spi.h"


/***********************************************************************
 Function that initializes the SPI
 ***********************************************************************/


void SPI_init(void) {
	// Enable clock network to SPI0
	    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
		SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;

		// configure output crossbar
		PORTD->PCR[0] = PORT_PCR_MUX(2);  // PCS
		PORTD->PCR[1] = PORT_PCR_MUX(2);  // SCK
		PORTD->PCR[2] = PORT_PCR_MUX(2);  // MOSI
		PORTD->PCR[3] = PORT_PCR_MUX(2);  // MISO

		// configure gpio address select
		/* here */

		// Config registers, turn on SPI0 as master
		// Enable chip select
		SPI0->C1 = 0x52;
		SPI0->C2 = 0x10;
		SPI0->BR = 0x00;   //Set  the baud rate prescale divisor to 3 & set baud rate divisor to 512 for baud rate of 15625 hz
}
/***************************************************************************
 * @brief SPI_state
 * It gives the state of SPI
 * returns a 8 bit pointer
****************************************************************************/
uint8_t SPI_state(void) {
	return SPI0->S;
}



/***********************************************************************
 * @brief SPI_write_byte
 * It checks if the transmit buffer is empty and sends the data
 * It then checks if the transfer is complete i.e. receiver buffer is full
 ***********************************************************************/

 uint8_t SPI_write_byte(uint8_t byte)

{
	    while((SPI_state() & 0x20) != 0x20);
		SPI0->D = byte; //Send  the data
		return SPI0->D;
}

/***********************************************************************
 * @brief SPI_send_packet
 * It checks if the transmit buffer is empty and sends the packet
 * It then checks if the transfer is complete i.e. receiver buffer is full
 ***********************************************************************/

uint8_t SPI_send_packet(uint8_t* p, uint8_t length) //To send the SPI packet
{
             uint8_t i=0;
             while((SPI_state() & 0x20) != 0x20); //Checks if the transfer buffer is empty
             for(i=0;i<length;i++)
          {
              SPI0->D = *(p+i); //Send the packet
          }
            return SPI0->D;
}
/***********************************************************************
 * @brief SPI_read_byte
 * It checks if the transfer is complete i.e. receiver buffer is full
 * SPI byte is read
 ***********************************************************************/

uint8_t SPI_read_byte(uint8_t byte)
{
			SPI0->D = 0x00;
			while ((SPI_state() & 0x80) != 0x80);
			byte = SPI0->D;
			return byte;
}
/***********************************************************************
 * @brief SPI_flush()
 * Function that flushes out the SPI transmit and the recieve buffers
 ***********************************************************************/
void SPI_flush() //To flush out the  spi transmit and recieve buffers
{
	SPI0_C1&=0xBF;
	SPI_init();
}

