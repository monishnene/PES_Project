/*
* nordic.h
*
*
* Created on: Nov 19, 2017
*
* Author: Sanika
*/

#ifndef NORDIC_H_
#define NORDIC_H_
#include <stdint.h>

uint8_t nrf_read_register(uint8_t register);
void nrf_write_register(uint8_t register, uint8_t value);
uint8_t nrf_read_status();
void nrf_write_config(uint8_t config);
uint8_t nrf_read_config();
uint8_t nrf_read_rf_setup(uint8_t config);
uint8_t nrf_read_rf_ch();
void nrf_write_rf_ch(uint8_t channel);
void nrf_read_TX_ADDR(uint8_t* address);
void nrf_write_TX_ADDR(uint8_t* tx_addr);
uint8_t nrf_read_fifo_status();
void nrf_flush_tx_fifo();
void nrf_flush_rx_fifo();

#endif
