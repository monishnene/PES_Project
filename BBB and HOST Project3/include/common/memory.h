* memory.h
 *
 *  Created on: Sep 29, 2017
 *      Author: monish and sanika
 */

#ifndef MEMORY_H_
#define MEMORY_H_
#include <stdint.h>
uint8_t* my_memmove(uint8_t* src, uint8_t* dst, uint32_t length);
uint8_t* my_memcpy(uint8_t* src, uint8_t* dst, uint32_t length);
uint8_t* my_memset(uint8_t* src, uint32_t length, uint8_t value);
uint8_t* my_memzero(uint8_t* src, uint32_t length);
uint8_t* my_reverse(uint8_t* src, uint32_t length);
int32_t* reserve_words(uint32_t length);
void free_words(uint32_t* src);
void memmove_dma(uint8_t *src, uint8_t *dst, uint32_t length, uint8_t byte);
void memset_dma(uint8_t *dst, uint32_t length, uint32_t value, uint8_t byte);
void DMA_overlap_handler(void);
static uint8_t overlap_flag = 0,original_byte=0,original_length=0;
static uint8_t* original_dst,temp_location;

#endif /* MEMORY_H_ */
