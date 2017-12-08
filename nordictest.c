#include "MKL25Z4.h"
#include "nordic.h"
#include "spi.h"
#include "gpio.h"

void main()
{
	uint8_t byte = 8;
	uint8_t register_function = 6;
	uint8_t i=0;
	uint8_t j=0;
	GPIO_nrf_configure();
	nrf_write_config();
	nrf_read_config();
	nrf_write_register(register_function);
	nrf_read_register(register_function);
}
