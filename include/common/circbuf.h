/*
 * circbuf.h
 *
 *  Created on: oct 22
, 2017
 *      Author: monish and sanika
 */
#include <stdint.h>
#ifndef	CIRCBUF_H_
#define CIRCBUF_H_

typedef struct
{
int32_t* buffptr;//base
uint32_t head;//in
uint32_t tail;//out
uint32_t size;//limit
uint32_t count;//used		
}CB_t;

extern CB_t cbvalues;

typedef enum
{
Buffer_Full,
Buffer_Empty,
Success,
Null_Error,
}CB_status;

extern CB_status cbstatus;
uint8_t CB_buffer_add_item(CB_t* cbptr,int8_t* data);
uint8_t CB_buffer_remove_item(CB_t* cbptr,int8_t* store);
uint8_t CB_is_full(CB_t* cbptr);
uint8_t CB_is_empty(CB_t* cbptr);
uint8_t CB_peek(CB_t* cbptr,uint8_t position, uint8_t* store);
uint8_t CB_init(CB_t* cbptr,uint8_t length);
uint8_t CB_destroy(CB_t* cbptr);
#endif /*circbuf.h*/
