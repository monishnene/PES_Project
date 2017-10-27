/**
 * @file circbuf.c
 * @brief This file contains circular buffer operation functions.
 * @author monish and sanika
 * @date oct 22, 2017
 *
 * circbuf.c
 *@Long description:-
 */
#include <stdlib.h>
#include <stdint.h>
#include "memory.h"
#include "circbuf.h"

/***********************************************************************
 * @brief CB_buffer_add_item()  
 * This function adds an item to circular buffer
 * @(CB_t)* cbptr pointer to circular buffer struct
 * @data value to be stored in circular buffer
 * @return error in form of enum defined in structure.h
 ***********************************************************************/
uint8_t CB_buffer_add_item(CB_t* cbptr,int8_t* data)
{
if(cbptr == NULL)
	{return Null_Error;}
else
{
	uint8_t i=CB_is_full(cbptr);
	if(i == Buffer_Full)
		{return Buffer_Full;}
	else
	{
		if (((cbptr-> head)+1)==(cbptr-> size))		
			{cbptr-> head = 0;}
		else		
			{cbptr-> head++;}
		*((cbptr-> buffptr)+(cbptr-> head)) = *data;
		if((cbptr-> head)>=(cbptr-> tail))
			{(cbptr-> count)= (cbptr-> head)-(cbptr-> tail);}
		else
			{(cbptr-> count)= ((cbptr-> head)-(cbptr-> tail)+(cbptr-> size));}
		return Success;
	}
}
}

/***********************************************************************
 * @brief CB_buffer_remove_item()  
 * This function removes an item from circular buffer and stores it
 * @(CB_t)* cbptr pointer to circular buffer struct
 * @store pointer to the location where the data is supposed to be stored
 * @return error in form of enum defined in structure.h
 ***********************************************************************/
uint8_t CB_buffer_remove_item(CB_t* cbptr,int8_t* store)
{
if(cbptr == NULL)
{return Null_Error;}
else
{
	uint8_t i=CB_is_empty(cbptr);
	if(i == Buffer_Empty)
		{return Buffer_Empty;}
	else
	{
		if (((cbptr-> tail)+1)==(cbptr-> size))		
			{cbptr-> tail = 0;}
		else		
			{cbptr-> tail++;}
		*store=*((cbptr-> buffptr)+(cbptr->tail));
		if((cbptr-> head)>=(cbptr-> tail))
			{(cbptr-> count)= (cbptr-> head)-(cbptr-> tail);}
		else
			{(cbptr-> count)= ((cbptr-> head)-(cbptr-> tail)+(cbptr-> size));}
		return Success;
	}	
}
}

/***********************************************************************
 * @briefCB_is_full()  
 * This function checks if buffer is full
 * @(CB_t)* cbptr pointer to circular buffer struct
 * @return error in form of enum defined in structure.h
 ***********************************************************************/
uint8_t CB_is_full(CB_t* cbptr)
{
if(cbptr == NULL)
	{return Null_Error;}
else
	{
	if((cbptr->tail+1)==(cbptr->head))
		return Buffer_Full;
	else
		return Success; 
	}
}


/***********************************************************************
 * @brief CB_is_empty()  
 * This function checks if buffer is empty
 * @(CB_t)* cbptr pointer to circular buffer struct
 * @return error in form of enum defined in structure.h
 ***********************************************************************/
uint8_t CB_is_empty(CB_t* cbptr)
{
if(cbptr == NULL)
	{return Null_Error;}
else
{
	if((cbptr->tail)==(cbptr->head))
		return Buffer_Empty;
	else
		return Success;
}
}


/***********************************************************************
 * @brief CB_peek()  
 * This function copies the item from circular buffer at a given position and stores it
 * @(CB_t)* cbptr pointer to circular buffer struct
 * @store pointer to the location where the data is supposed to be stored
 * @return error in form of enum defined in structure.h
 ***********************************************************************/
uint8_t CB_peek(CB_t* cbptr,uint8_t position, uint8_t* store)
{
if(cbptr == NULL)
	{return Null_Error;}
else
{
	uint8_t i=CB_is_empty(cbptr);
	if(i == Buffer_Empty)
		{return Buffer_Empty;}
	else
	{	while(position > cbptr-> size)
		 {position = position - cbptr-> size;}
		*store=*((cbptr-> buffptr)+position);
		return Success;
	}
}
}

/***********************************************************************
 * @brief CB_init()  
 * This function allocates memory using malloc for circular buffer
 * @(CB_t)* cbptr pointer to circular buffer struct
 * @length length of the circular buffer
 * @return error in form of enum defined in structure.h
 ***********************************************************************/
uint8_t CB_init(CB_t* cbptr,uint8_t length)
{
if(cbptr == NULL)
	{return Null_Error;}
else
{
	(cbptr-> buffptr) = malloc(length);
	(cbptr-> size) = length;
	(cbptr-> head) = 0;
	(cbptr-> tail) = 0;
	(cbptr-> count) = 0;
	if(cbptr == NULL)
		{return Null_Error;}
	else
		{return Success;}
}
}

/***********************************************************************
 * @brief CB_destroy()  
 * This function deallocates memory used by the circular buffer pointed by cbptr
 * @(CB_t)* cbptr pointer to circular buffer struct
 * @return error in form of enum defined in structure.h
 ***********************************************************************/
uint8_t CB_destroy(CB_t* cbptr)
{
if(cbptr == NULL)
	{return Null_Error;}
else
	{
	free(cbptr);
	return Success;
	}	
}
