#ifndef SPI_H_
#define SPI_H_
#include <stdint.h>

void SPI_init();
uint8_t SPI_read_byte( uint8_t byte);
uint8_t SPI_write_byte( uint8_t byte);
void SPI_send_packet( uint8_t* p, uint8_t length);
void SPI_flush();
uint8_t SPI_state(void);

#endif
