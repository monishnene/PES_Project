
#include "MKL25Z4.h"
#include "NRF.h"
#include "SPI.h"

uint8_t nrf_read_register(uint8_t register)

{
        uint8_t l;
	l = SPI_write(0x00|register);//read command
        return l;
}

void nrf_write_register(uint8_t register, uint8_t value)
{
 value = 255;
 SPI_write(value|register); //write command
}

void nrf_read_status() //function to read the nrf status register
{
	uint8_t c;
	PTC_BASE_PTR->PCOR = 1<<4;
	nrf_read_register(NORDIC_STATUS_REG);
	SPI_write(0xFF);
	c=SPI_read();
	PTC_BASE_PTR->PSOR = 1<<4;
}

void nrf_write_config(uint8_t config)
{
	PTC_BASE_PTR->PCOR = 1<<4; //Chip select low
	config = nrf_write_register(NORDIC_CONFIG_REG); //write command to Config register
	SPI_write(0x03);//Write data to Config register
	PTC_BASE_PTR->PSOR =  1<<4; //Chip select high
}

uint8_t nrf_read_config()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; //enable clock to port B
	uint8_t j,k;
	PTC_BASE_PTR->PCOR = 1<<4; //Chip select low
	k = nrf_read_register(NORDIC_CONFIG_REG); // read command to Config register
	j=SPI_write(0X7F);//Send dummy value to recieve data
	PTC_BASE_PTR->PSOR = 1<<4; //Chip select high
        return k;
}

void nrf_read_rf_setup() //read the rf register
{
	uint8_t c;
	PTC_BASE_PTR->PCOR = 1<<4;
	nrf_write_register(NORDIC_RF_SETUP_REG);
	c=SPI_write(0xff);
	PTC_BASE_PTR->PSOR = 1<<4;

}

void nrf_write_rf_setup(uint8_t config) //setup the rf register
{
	PTC_BASE_PTR->PCOR = 1<<4;
	config = nrf_write_register(NORDIC_RF_SETUP_REG);
	SPI_write(0x02);
	PTC_BASE_PTR->PSOR = 1<<4;
}

uint8_t nrf_read_rf_ch();
{
 uint8_t i,k;
 PTC_BASE_PTR->PCOR = 1<<4;
 k = nrf_write_register(NORDIC_RF_CH);
 i = SPI_write(0xff);
 PTC_BASE_PTR->PSOR = 1<<4;
 return k;
}

void nrf_write_rf_ch(uint8_t channel);
{
uint32_t i;
PTC_BASE_PTR->PCOR = 1<<4;
channel = nrf_write_register(NORDIC_RF_CH);
for(i=0; i<5; i++)
{
  SPI_write(0xCA);
}
PTC_BASE_PTR->PSOR = 1<<4;
}


void nrf_read_TX_ADDR(uint8_t* address) //read the tx address register
{
	uint32_t i;
	uint8_t k;
	PTC_BASE_PTR->PCOR = 1<<4;
	*address = nrf_read_register(TX_ADDR);
	 for(i=0;i<5;i++)
	 {

		 k=SPI_write(0xff);
	 }
	PTC_BASE_PTR->PSOR = 1<<4;
}

void nrf_write_TX_ADDR(uint8_t *address) //write the tx address register
{
	uint32_t i;
	PTC_BASE_PTR->PCOR = 1<<4;
	*address = nrf_write_register(TX_ADDR);
	 for(i=0;i<5;i++)
	 {
		 SPI_write(0xBB);// setting BB as the TX address
	 }
	 PTC_BASE_PTR->PSOR = 1<<4;
}

uint8_t nrf_read_fifo_status() //function to read the nrf fifostatus register
{

	uint8_t c;
	PTC_BASE_PTR->PCOR = 1<<4;
	nrf_read_register(FIFO_STATUS_REG );
	c=SPI_write(0xff);
	 PTC_BASE_PTR->PSOR = 1<<4;
}


void nrf_flush_tx_fifo() //function to flush the tx fifo
{																		
	PTC_BASE_PTR->PCOR = 1<<4;
	SPI_write(0xE1);
	PTC_BASE_PTR->PSOR = 1<<4;
}

void nrf_flush_rx_fifo() //function to flush the rx fifo
{
	PTC_BASE_PTR->PCOR = 1<<4;
	SPI_write(0xE2);
	PTC_BASE_PTR->PSOR = 1<<4;
}

/*void nrf_transmit_data() //send data to nrf buffer
{
	PTC_BASE_PTR->PCOR = 1<<4;
	SPI_write(W_TXPAYLOAD);
	SPI_write(0x10);
        PTC_BASE_PTR->PSOR = 1<<4; 																																							

}
 
void nrf_read_data() //receive data from nrf buffer
{
	uint8_t c;
	PTC_BASE_PTR->PCOR = 1<<4;
	SPI_write(R_RXPAYLOAD);
	c=SPI_write(0xff);
	PTC_BASE_PTR->PSOR = 1<<4;

	nrf_fifostatus_read();

}*/









    

