
#include "MKL25Z4.h"
#include "NRF.h"
#include "SPI.h"

uint8_t nrf_read_register(uint8_t register)

{
        uint8_t l;
	l = SPI_write(0x00|register);
        return l;
}

void nrf_write_register(uint8_t register, uint8_t value)
{
 value = 255;
 SPI_write(value|register); 

void nrf_read_status() 
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
	PTC_BASE_PTR->PCOR = 1<<4; 
	config = nrf_write_register(NORDIC_CONFIG_REG); 
	SPI_write(0x03);
	PTC_BASE_PTR->PSOR =  1<<4; 
}

uint8_t nrf_read_config()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; 
	uint8_t j,k;
	PTC_BASE_PTR->PCOR = 1<<4; 
	k = nrf_read_register(NORDIC_CONFIG_REG); 
	j=SPI_write(0X7F);
	PTC_BASE_PTR->PSOR = 1<<4; 
        return k;
}

void nrf_read_rf_setup() 
{
	uint8_t c;
	PTC_BASE_PTR->PCOR = 1<<4;
	nrf_write_register(NORDIC_RF_SETUP_REG);
	c=SPI_write(0xff);
	PTC_BASE_PTR->PSOR = 1<<4;

}

void nrf_write_rf_setup(uint8_t config) 
{
	PTC_BASE_PTR->PCOR = 1<<4;
	config = nrf_write_register(NORDIC_RF_SETUP_REG);
	SPI_write(0x02);
	PTC_BASE_PTR->PSOR = 1<<4;
}

void nrf_read_TX_ADDR(uint8_t* address) 
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

void nrf_write_TX_ADDR(uint8_t *address) 
{
	uint32_t i;
	PTC_BASE_PTR->PCOR = 1<<4;
	*address = nrf_write_register(TX_ADDR);
	 for(i=0;i<5;i++)
	 {
		 SPI_write(0xBB);
	 }
	 PTC_BASE_PTR->PSOR = 1<<4;
}

uint8_t nrf_read_fifo_status() 

	uint8_t c;
	PTC_BASE_PTR->PCOR = 1<<4;
	nrf_read_register(FIFO_STATUS_REG );
	c=SPI_write(0xff);
	 PTC_BASE_PTR->PSOR = 1<<4;
}
void nrf_flush_tx_fifo() 
{																		
	PTC_BASE_PTR->PCOR = 1<<4;
	SPI_write(0xE1);
	PTC_BASE_PTR->PSOR = 1<<4;
}



void nrf_flush_rx_fifo() 
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




    

