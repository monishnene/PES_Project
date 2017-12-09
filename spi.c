/*
 * spi.c
 * Created on : Nov 22, 2017
 * Author : Sanika
 */

#include "MKL25Z4.h"
#include "SPI.h"
#include "gpio.h"

/************************************************************************
 * @brief SPI_init()
 * Function to initialize the SPI
 * SPI_configure() is being called to configure the required GPIO pins
 * The SPI is then enabled and set as the Master
 * The baud rate prescale and baud rate divisor is then being set
 ***********************************************************************/

void SPI_init() {
	SPI_configure();
	SPI0->C1 = 0x50;// Enables the SPI and is being set as  the Master device
	SPI0_BR = (SPI_BR_SPPR(0x03) | SPI_BR_SPR(0x08));    //Baud rate prescale divisor and baud rate divisor is being set
}
/************************************************************************
 * @brief SPI_state()
 * Function that shows the state of SPI
 ***********************************************************************/

uint8_t SPI_state(void) {  //Shows the status of SPI
	return SPI0->S;
}
/************************************************************************
 * @brief SPI_write_byte(uint8_t byte)
 * Function to write byte to the SPI
 * It writes the byte if the transmitter buffer is empty
 ***********************************************************************/
void SPI_write_byte(uint8_t byte)
{
        while ((SPI_state() & 0x20) != 0x20); //To check if the Transmitter buffer is empty
		SPI0->D = byte;                       //Sends the data

}

/************************************************************************
 * @brief SPI_send_packet(uint8_t* p, uint8_t length)
 * Function to send packet
 * To check if the transmit buffer is empty and then sends the data for given
 * length
 ***********************************************************************/
void SPI_send_packet(uint8_t* p, uint8_t length) {
	uint8_t i=0;
	for (i = 0; i < length; i++) {
		while ((SPI_state() & 0x20) != 0x20);
		SPI0->D = *(p+i);                        //Sends packet
	}
}
/************************************************************************
 * @brief SPI_read_byte()
 * Function to read the SPI
 * SPI_configure() is being called to configure the required GPIO pins
 * The SPI is then enabled and set as the Master
 * The baud rate prescale and baud rate divisor is then being set
 ***********************************************************************/

uint8_t SPI_read_byte()
{
	uint8_t byte;
	SPI0->D = 0x00;                             //Test value pushed to SPI
	while ((SPI_state() & 0x80) != 0x80);       //To check if the receive buffer is empty
	byte = SPI0->D;                             // Reads byte
	return byte;                                // Returns the byte
}
/************************************************************************
 * @brief SPI_flush()
 * Function to flush the transmit and receive buffers
 ***********************************************************************/

void spi_flush() //To flush out the transmit and recieve buffers
{
	SPI0_C1&=0xBF;
	SPI_init();
}
