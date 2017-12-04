#include "MKL25Z4.h"
#include "nordic.h"
#include "spi.h"

/***********************************************************************
 * @brief nrf_read_register
 * It reads the SPI_write_byte register in a variable and returns the value

 ***********************************************************************/

uint8_t nrf_read_register(uint8_t register_function)

{
        uint8_t l;
	l = SPI_write_byte(0x00|register_function);//Reads the command
        return l;
}

/***********************************************************************
 * @brief nrf_write_register
 * It sets the SPI_write_byte register to a value

 ***********************************************************************/

void nrf_write_register(uint8_t register_function, uint8_t value)
{
  value = 254;
  SPI_write_byte(value|register_function); //Writes the command
}

/***********************************************************************
 * @brief nrf_read_status
 * It is a function to read the nordic status register
 * SPI_write_byte has been set to FF and a variable is used to store the result
 * for SPI_read

 ***********************************************************************/

uint8_t nrf_read_status() //function that reads the nrf status register
{
	uint8_t c,d,h;
	PTC_BASE_PTR->PCOR = 1<<4; //Chip select is made low
	d = nrf_read_register(NRF_STATUS_REG);
	h = SPI_write_byte(0xFF);
	c= SPI_read_byte(h);
	PTC_BASE_PTR->PSOR = 1<<4; //Chip select is set to high
	return c;
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
    nrf_write_register(NRF_CONFIG_REG, 3); //Write command to Config register
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
    k = nrf_read_register(NRF_CONFIG_REG); // Read command to Config register
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

uint8_t nrf_read_rf_setup() //Read the rf register
{
	uint8_t c;
	PTC_BASE_PTR->PCOR = 1<<4;
	nrf_write_register(NRF_RF_SETUP_REG, 6);
	c=SPI_write_byte(0xff);
	PTC_BASE_PTR->PSOR = 1<<4;
	return c;

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
    nrf_write_register(NRF_RF_SETUP_REG, 3);
	config = SPI_write_byte(0x08);
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

uint8_t nrf_read_rf_ch() //Read rf_ch register
{
 uint8_t i,k;
 PTC_BASE_PTR->PCOR = 1<<4;
 nrf_write_register(NRF_RF_CH_REG, 4);
 i = SPI_write_byte(0xff);
 PTC_BASE_PTR->PSOR = 1<<4;
 k= nrf_read_fifo_status(); //Read the fifo status
 return i;
}
/***********************************************************************
 * @brief nrf_write_rf_ch
 * Function to write to the ch register
 * Chip select is low
 * nrf-write-register is used for NORDIC_RF_CH_REG
 * values are written on the channel
 * The chip select is then set to high
 ***********************************************************************/

void nrf_write_rf_ch(uint8_t channel) //Write command to rf_ch register
{
uint32_t i;
PTC_BASE_PTR->PCOR = 1<<4;
nrf_write_register(NRF_RF_CH_REG, 5);
for(i=0; i<5; i++)
 {
   channel = SPI_write_byte(0x10);
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

void nrf_write_TX_ADDR(uint8_t *tx_addr) // Command to write to the tx address register
{
	uint32_t i;
	PTC_BASE_PTR->PCOR = 1<<4;
     nrf_write_register(TX_ADDR, 2);
	 for(i=0;i<5;i++)
	 {
		 *tx_addr = SPI_write_byte(0xBB);// Setting BB as the TX address
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

	uint8_t c,j;
	PTC_BASE_PTR->PCOR = 1<<4;
	 j = nrf_read_register(FIFO_STATUS_REG); //Command to read the fifo_status_register
	c=SPI_write_byte(0xff);
	 PTC_BASE_PTR->PSOR = 1<<4;
	 return c;
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










