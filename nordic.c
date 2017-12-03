
#include "MKL25Z4.h"
#include "NRF.h"
#include "SPI.h"

/***********************************************************************
 * @brief nrf_read_register
 * It reads the SPI_write_byte register in a variable and returns the value
 

 ***********************************************************************/

uint8_t nrf_read_register(uint8_t register)

{
        uint8_t l;
	l = SPI_write_byte(0x00|register);//Reads the command
        return l;
}

/***********************************************************************
 * @brief nrf_write_register
 * It sets the SPI_write_byte register to a value
 

 ***********************************************************************/

void nrf_write_register(uint8_t register, uint8_t value)
{
 value = 255;
 SPI_write_byte(value|register); //Writes the command
}

/***********************************************************************
 * @brief nrf_read_status
 * It is a function to read the nordic status register
 * SPI_write_byte has been set to FF and a variable is used to store the result
 * for SPI_read
 

 ***********************************************************************/

void nrf_read_status() //function that reads the nrf status register
{
	uint8_t c;
	PTC_BASE_PTR->PCOR = 1<<4; //Chip select is made low
	nrf_read_register(NORDIC_STATUS_REG);
	SPI_write_byte(0xFF);
	c=SPI_read_byte();
	PTC_BASE_PTR->PSOR = 1<<4; //Chip select is set to high
}

/***********************************************************************
 * @brief nrf_write_config
 * Chip select is low
 * It is a function to write command to the Config register
 * Data is written to config register and that data is being stored in 
 * config variable. The chip select is then set to high
 ***********************************************************************/

void nrf_write_config(uint8_t config) //function that is used for writing config register
{
	PTC_BASE_PTR->PCOR = 1<<4; 
        nrf_write_register(NORDIC_CONFIG_REG); //Write command to Config register
	config = SPI_write_byte(0x03);//Write data to Config register
	PTC_BASE_PTR->PSOR =  1<<4; 
}

/***********************************************************************
 * @brief nrf_read_config
 * The Clock to Port B is being enabled.
 * Chip select is low
 * It is a function to read command to the Config register
 * A dummy value is sent to receive data  
 * The chip select is then set to high and the dummy value is being returned
 ***********************************************************************/
uint8_t nrf_read_config()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; //enable clock to port B
	uint8_t j,k;
	PTC_BASE_PTR->PCOR = 1<<4; //Chip select  is made low
        nrf_read_register(NORDIC_CONFIG_REG); // Read command to Config register
	j=SPI_write_byte(0X7F);//Sends a test value to recieve data
	PTC_BASE_PTR->PSOR = 1<<4; //Chip select is set to high
        return j;
}
/***********************************************************************
 * @brief nrf_read_rf_setup
 * Function to read the rf setup register
 * Chip select is low
 * nrf-write-register is used for NORDIC_RF_SETUP_REG
 * A dummy value is sent to receive data  
 * The chip select is then set to high 
 ***********************************************************************/

void nrf_read_rf_setup() //Read the rf register
{
	uint8_t c;
	PTC_BASE_PTR->PCOR = 1<<4;
	nrf_write_register(NORDIC_RF_SETUP_REG);
	c=SPI_write_byte(0xff);
	PTC_BASE_PTR->PSOR = 1<<4;

}
/***********************************************************************
 * @brief nrf_write_rf_setup
 * Function to write the rf setup register
 * Chip select is low
 * nrf-write-register is used for NORDIC_RF_SETUP_REG
 * A value is written 
 * The chip select is then set to high 
 ***********************************************************************/

void nrf_write_rf_setup(uint8_t config) //Setup the rf register
{
	PTC_BASE_PTR->PCOR = 1<<4;
	config = nrf_write_register(NORDIC_RF_SETUP_REG);
	SPI_write_byte(0x02);
	PTC_BASE_PTR->PSOR = 1<<4;
}
/***********************************************************************
 * @brief nrf_read_rf_ch
 * Function to read the ch register
 * Chip select is low
 * nrf-write-register is used for NORDIC_RF_CH_REG
 * A value is written 
 * The chip select is then set to high
 * The fifo status is then read and returned 
 ***********************************************************************/

uint8_t nrf_read_rf_ch(); //Read rf_ch register
{
 uint8_t i,k;
 PTC_BASE_PTR->PCOR = 1<<4;
 nrf_write_register(NORDIC_RF_CH_REG);
 i = SPI_write_byte(0xff);
 PTC_BASE_PTR->PSOR = 1<<4;
 k=nrf_read_fifo_status(); //Read the fifo status
 return k;
}
/***********************************************************************
 * @brief nrf_write_rf_ch
 * Function to write to the ch register
 * Chip select is low
 * nrf-write-register is used for NORDIC_RF_CH_REG
 * values are written on the channel
 * The chip select is then set to high
 ***********************************************************************/

void nrf_write_rf_ch(uint8_t channel); //Write command to rf_ch register
{
uint32_t i;
PTC_BASE_PTR->PCOR = 1<<4;
channel = nrf_write_register(NORDIC_RF_CH_REG);
for(i=0; i<5; i++)
{
  SPI_write_byte(0x10);
}
PTC_BASE_PTR->PSOR = 1<<4;
}
/***********************************************************************
 * @brief nrf_read_TX_addr
 * Function to read the TX_ADDR 
 * Chip select is low
 * nrf-read-register is used for reading the TX_ADDR register
 * values are written using SPI_write_byte
 * The chip select is then set to high
 ***********************************************************************/

void nrf_read_TX_ADDR(uint8_t* address) //Read the tx address register
{
	uint32_t i;
	uint8_t k;
	PTC_BASE_PTR->PCOR = 1<<4;
	*address = nrf_read_register(TX_ADDR); //Command to read the TX_ADDR register
	 for(i=0;i<5;i++)
	 {

		 k=SPI_write_byte(0xff);
	 }
	PTC_BASE_PTR->PSOR = 1<<4;
}
/***********************************************************************
 * @brief nrf_write_TX_ADDR
 * Function to write to the tx address register
 * Chip select is low
 * nrf_write_register is used for TX_ADDR register
 * values are written using SPI_write_byte
 * The chip select is then set to high
 ***********************************************************************/

void nrf_write_TX_ADDR(uint8_t *address) // Command to write to the tx address register
{
	uint32_t i;
	PTC_BASE_PTR->PCOR = 1<<4;
	*address = nrf_write_register(TX_ADDR);
	 for(i=0;i<5;i++)
	 {
		 SPI_write_byte(0xBB);// Setting BB as the TX address
	 }
	 PTC_BASE_PTR->PSOR = 1<<4;
}
/***********************************************************************
 * @brief nrf_read_fifo_status
 * Function to read the nrf_fifo_status
 * Chip select is low
 * nrf_read_register is used for FIFO_STATUS_REG
 * values are written
 * The chip select is then set to high
 ***********************************************************************/

uint8_t nrf_read_fifo_status() //Function to read the nrf fifostatus register
{

	uint8_t c;
	PTC_BASE_PTR->PCOR = 1<<4;
	nrf_read_register(FIFO_STATUS_REG); //Command to read the fifo_status_register
	c=SPI_write_byte(0xff);
	 PTC_BASE_PTR->PSOR = 1<<4;
}
/***********************************************************************
 * @brief nrf_flush_tx_fifo
 * Function to flush_tx_fifo
 * Chip select is low
 * SPI_write_byte sending 0xE1
 * The chip select is then set to high
 ***********************************************************************/

void nrf_flush_tx_fifo() //Function that flushes the tx fifo
{																		
	PTC_BASE_PTR->PCOR = 1<<4;
	SPI_write_byte(0xE1);   
	PTC_BASE_PTR->PSOR = 1<<4;
}
/***********************************************************************
 * @brief nrf_flush_rx_fifo
 * Function to flush_rx_fifo
 * Chip select is low
 * SPI_write_byte sending 0xE2
 * The chip select is then set to high
 ***********************************************************************/

void nrf_flush_rx_fifo() //Function that flushes the rx fifo
{
	PTC_BASE_PTR->PCOR = 1<<4;
	SPI_write_byte(0xE2);
	PTC_BASE_PTR->PSOR = 1<<4;
}










    
