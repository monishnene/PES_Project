
/*
 * structure.h
 *
 *  Created on: oct 22, 2017
 *      Author: monish and sanika
 */

#ifndef	STRUCTURE_H_
#define STRUCTURE_H_
typedef struct
{
int32_t* buffptr;//base
uint32_t head=0;//in
uint32_t tail=0;//out
uint32_t size;//limit
uint32_t count=0;//used		
}CB_t;

extern CB_t cbvalues;

typedef enum
{
Buffer_Full;
Buffer_Empty;
Success;
Null_Error;
}CB_status;

extern CB_status cbstatus;

#endif /*structure.h*/

