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
uint32_t time_calculation(/*parameter for function*/);
void profiling( uint32_t length);
#endif /* INCLUDES_PROFILING_H_ */
