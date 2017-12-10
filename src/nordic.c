/*
 * nordic.c
 * Created on : Nov 23, 2017
 *
 */
#include "MKL25Z4.h"
#include "SPI.h"
#include "nordic.h"
#include <stdlib.h>
#include <stdint.h>
#include "gpio.h"

/**********************************************************
@brief nrf_read_register
 * It reads the SPI_write_byte register in a variable and returns the value
************************************************************/

void nrf_read_register(uint8_t function)

 {
		SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
		uint8_t k;
		k =SPI_write_byte(0x00|function);//Reads the command

 }
/***************************************************************
 * @brief nrf_write_register
 * It sets the SPI_write_byte register to a value
 *
 **************************************************************/
void nrf_write_register(uint8_t function)

 {
		SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
		uint8_t i;
		i = SPI_write_byte(0x20|function); //Writes the command
 }

 /***********************************************************************
  @brief nrf_read_status
 * It is a function to read the nordic status register
 * SPI_write_byte has been set to FF and a variable is used to store the result
 * for SPI_read


  ***********************************************************************/

void nrf_read_status() //function that reads the nrf status register
 {
		SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
		uint8_t c,d,h;
		nrf_chip_enable();

		nrf_read_register(NRF_STATUS_REG);
		d = SPI_write_byte(0x36);
		c= SPI_read_byte();
		nrf_chip_disable();

 }

 /***********************************************************************
@brief nrf_write_config
 * GPIO is low
 * It is a function to write command to the Config register
 * Data is written to config register and that data is being stored in
  *  * config variable. The GPIO is then set to high
  ***********************************************************************/

 void nrf_write_config() //function that is used for writing config register
 {
	    SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	    uint8_t h;
	    nrf_chip_enable();
		//Write command to Config register
		//Write data to Config register
		 nrf_write_register(NRF_CONFIG_REG); //Write command to Config register
		 h = SPI_write_byte(0x03);//Write data to Config register
		 nrf_chip_disable();

 }

 /***********************************************************************
@brief nrf_read_config
 * The Clock to Port B is being enabled.
 * GPIO is low
 * It is a function to read command to the Config register
 * A dummy value is sent to receive data
 * The GPIO is then set to high and the dummy value is being returned

  *********************************************************************/

void nrf_read_config()
 {
		uint8_t j,k;
		SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; //enable clock to port C
		nrf_chip_enable();
		nrf_read_register(NRF_CONFIG_REG); // Read command to Config register
		k = SPI_write_byte(0X82);//Sends a test value to recieve data
		nrf_chip_disable();

 }
 /***********************************************************************
  * @brief nrf_read_rf_setup
 * Function to read the rf setup register
 * GPIO is low
 * nrf-write-register is used for NORDIC_RF_SETUP_REG
 * A dummy value is sent to receive data
 * The GPIO is then set to high
  *
  ***********************************************************************/

 //Read the rf register
void nrf_read_rf_setup() //Read the rf register
 {
	 SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
 	 uint8_t c;
 	 nrf_chip_enable();
     nrf_write_register(NRF_RF_SETUP_REG);
 	 c = SPI_write_byte(0xFF);
 	 nrf_chip_disable();

 }
 /***********************************************************************
@brief nrf_write_rf_setup
 * Function to write the rf setup register
 * GPIO is low
 * nrf-write-register is used for NORDIC_RF_SETUP_REG
 * A value is written
 * The GPIO is then set to high

  ***********************************************************************/

//Setup the rf register
void nrf_write_rf_setup() //Setup the rf register
 {
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	uint8_t l;
	nrf_chip_enable();
    nrf_write_register(NRF_RF_SETUP_REG);
    l=  SPI_write_byte(0x02);
    nrf_chip_disable();
 }
 /***********************************************************************
@brief nrf_read_rf_ch
 * Function to read the ch register
 * GPIO is low
 * nrf-write-register is used for NORDIC_RF_CH_REG
 * A value is written
 * The GPIO is then set to high
 * The fifo status is then read and returned

  ***********************************************************************/


void nrf_read_rf_ch() //Read rf_ch register
 {
	 SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
     uint8_t i;
     nrf_chip_enable();
     nrf_write_register(NRF_RF_CH_REG);
     i =  SPI_write_byte(0x42);
     nrf_chip_disable();
  //Read the fifo status
     nrf_read_fifo_status(); //Read the fifo status
 }
 /***********************************************************************
  *@brief nrf_write_rf_ch
 * Function to write to the ch register
 * GPIO is low
 * nrf-write-register is used for NORDIC_RF_CH_REG
 * values are written on the channel
 * The GPIO is then set to high

  *
  ***********************************************************************/
  //Write command to rf_ch register
void nrf_write_rf_ch() //Write command to rf_ch register
 {
	 SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
     uint32_t i;
     uint8_t channel;
     nrf_chip_enable();
     nrf_write_register(NRF_RF_CH_REG);
     for(i=0; i<5; i++)
     {
       channel = SPI_write_byte(0x10);
      }
     nrf_chip_disable();
 }
  // The chip select is then set to high
    /*************************************************
     * @brief nrf_read_TX_addr
 * Function to read the TX_ADDR
 * GPIO is low
 * nrf-read-register is used for reading the TX_ADDR register
 * values are written using SPI_write_byte
 * The GPIO is then set to high
     *
     **************************************************/

void nrf_read_TX_ADDR() //Read the tx address register
 {
	  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
 	  uint32_t i;
 	  uint8_t k;
 	  nrf_chip_enable();
 //Command to read the TX_ADDR register
 	  for(i=0;i<5;i++)
 		{
 			k =  SPI_write_byte(0xB3);// setting BB as the TX address
 		 }
 	  nrf_chip_disable();
 }

//Read the tx address register
// Command to write to the tx address register
/*********************************************************************
 * @brief nrf_write_TX_ADDR
 * Function to write to the tx address register
 * GPIO is low
 * nrf_write_register is used for TX_ADDR register
 * values are written using SPI_write_byte
 * The GPIO is then set to high

 *
 *********************************************************************/
void nrf_write_TX_ADDR() // Command to write to the tx address register
 {
	 SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
 	 uint32_t i;
 	 uint8_t j;
 	 nrf_chip_enable();
 	 nrf_write_register(TX_ADDR);

 	 for(i=0;i<5;i++)
 	  {
 		  j  = SPI_write_byte(0x06);// Setting BB as the TX address
 	  }

      nrf_chip_disable();
 }
// Command to write to the tx address register

 //Function to read the nrf fifostatus register
 /*************************************************************
  * @brief nrf_read_fifo_status
 * Function to read the nrf_fifo_status
 * GPIO is low
 * nrf_read_register is used for FIFO_STATUS_REG
 * values are written
 * The GPIO is then set to high

  *
  ***********************************************************/
void nrf_read_fifo_status() //Function to read the nrf fifostatus register
 {
	 SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
     uint8_t h;
     nrf_chip_enable();
 //Command to read the fifo_status_register
     nrf_read_register(FIFO_STATUS_REG); //Command to read the fifo_status_register
 	 h = SPI_write_byte(0xFF);
 	 nrf_chip_disable();
 }
/**********************************************************
 * @brief nrf_flush_tx_fifo
 * Function to flush_tx_fifo
 * GPIO is low
 * SPI_write_byte sending 0xE1
 * The GPIO is then set to high

 *
 ***********************************************************/
void nrf_flush_tx_fifo() //function to flush the tx fifo
{
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	uint8_t g;
	nrf_chip_enable();
	g = SPI_write_byte(0xE1);
	nrf_chip_disable() ;
}
/*************************************************************
 * @brief nrf_flush_rx_fifo
 * Function to flush_rx_fifo
 * GPIO is low
 * SPI_write_byte sending 0xE2
 * The GPIO is then set to high
 *
 *************************************************************/
void nrf_flush_rx_fifo() //function to flush the rx fifo
{
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	uint8_t c;
	nrf_chip_enable();
	c = SPI_write_byte(0xE2);
	nrf_chip_disable();
}

