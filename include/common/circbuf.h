/*
 * circbuf.h
 *
 *  Created on: oct 22
, 2017
 *      Author: monish and sanika
 */

#ifndef	CIRCBUF_H_
#define CIRCBUF_H_
uint8_t CB_buffer_add_item((CB_t)* cbptr,int32_t data);
uint8_t CB_buffer_remove_item((CB_t)* cbptr,int32_t* store);
uint8_t CB_is_full((CB_t)* cbptr);
uint8_t CB_is_empty((CB_t)* cbptr);
uint8_t CB_peek((CB_t)* cbptr,uint8_t position, uint32_t* store);
uint8_t CB_init((CB_t)=* cbptr,uint32_t length);
uint8_t CB_destroy((CB_t)* cbptr);
#endif /*circbuf.h*/
