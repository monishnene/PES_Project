#include "MKL25Z4.h"
#include "nordic.h"
#include "spi.h"
#include "gpio.h"

void main()
{
	uint8_t byte = 8;
	uint8_t i=0;
	uint8_t j=0;
	SPI_init();
	i= SPI_write_byte(byte);
	j=SPI_read_byte();
}
