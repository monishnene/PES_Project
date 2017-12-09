/*
 * gpio.h
 *
 *  Created on: Dec 8, 2017
 *      Author: Monish and Sanika
 */

#ifndef INCLUDES_GPIO_H_
#define INCLUDES_GPIO_H_
#include "MKL25Z4.h"
#include "SPI.h"
#include "nordic.h"

void SPI_configure();
void GPIO_nrf_configure();
void nrf_chip_enable();
void nrf_chip_disable();
void nrf_transmit_enable();
void nrf_transmit_disable();

#endif /* INCLUDES_GPIO_H_ */
