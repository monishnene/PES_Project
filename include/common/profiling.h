/*
 * profiling.h
 *
 *  Created on: Dec 2, 2017
 *      Author: monis
 */

#ifndef INCLUDES_PROFILING_H_
#define INCLUDES_PROFILING_H_
static uint8_t loop_for_big_memory=1;
void SysTick_Init();
void time_start(uint8_t state);
void time_end(uint8_t state);
void log_result(uint32_t length, uint8_t k);
void profiling( uint32_t length);
void DMA0_IRQHandler();
#endif /* INCLUDES_PROFILING_H_ */
