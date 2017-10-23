#include <stdint.h>..
#include "memory.h"
#include "structure.h"

uint8_t CB_buffer_add_item((CB_t)* cbptr,int32_t data)
{
if(cbptr == NULL)
	{return cbstatus->Null_staus;}
else
{-
	uint8_t i=CB_is_full(cbptr);
	if(i == cbstatus-> Buffer_Full)
		{return cbstatus->Buffer_Full;}
	else
	{
		if ((cbptr-> head)+1)==(cbptr-> size))		
			{cbptr-> head = 0;}
		else		
			{head++;}
		*((cbptr-> buffptr)+(cbptr-> head)) = data;
		if((cbptr-> head)>=(cbptr-> tail))
			{(cbptr-> count)= (cbptr-> head)-(cbptr-> tail);}
		else
			{(cbptr-> count)= ((cbptr-> head)-(cbptr-> tail)+(cbptr-> size);}
		return cbstatus->Success;
	}
}
}

uint8_t CB_buffer_remove_item((CB_t)* cbptr,int32_t* store)
{
if(cbptr == NULL)
{return cbstatus->Null_staus;}
else
{
	uint8_t i=CB_is_empty(cbptr);
	if(i == cbstatus-> Buffer_Empty)
		{return cbstatus->Buffer_Empty;}
	else
	{
		if ((cbptr-> tail)+1)==(cbptr-> size))		
			{cbptr-> tail = 0;}
		else		
			{tail++;}
		*store=*((cbptr-> buffptr)+(cbptr->tail));
		if((cbptr-> head)>=(cbptr-> tail))
			{(cbptr-> count)= (cbptr-> head)-(cbptr-> tail);}
		else
			{(cbptr-> count)= ((cbptr-> head)-(cbptr-> tail)+(cbptr-> size);}
		return cbstatus->Success;
	}	
}
}

uint8_t CB_is_full((CB_t)* cbptr)
{
if(cbptr == NULL)
	{return cbstatus->Null_staus;}
else
	{
	if((cbptr->tail+1)==(cbptr->head))
		return cbstatus->Buffer_Full;
	else
		return cbstatus->Success; 
	}
}

uint8_t CB_is_empty((CB_t)* cbptr)
{
if(cbptr == NULL)
	{return cbstatus->Null_staus;}
else
{
	if((cbptr->tail)==(cbptr->head))
		return cbstatus->Buffer_Empty;
	else
		return cbtatus->Success;
}
}

uint8_t CB_peek((CB_t)* cbptr,uint8_t position, uint32_t* store)
{
if(cbptr == NULL)
	{return cbstatus->Null_staus;}
else
{
	uint8_t i=CB_is_empty(cbptr);
	if(i == cbstatus->Buffer_Empty)
		{return cbstatus->Buffer_Empty;}
	else
	{
		*store=*((cbptr-> buffptr)+position);
		return cbstatus->Success;
	}
}
}

uint8_t CB_init((CB_t)=* cbptr,uint32_t length)
{
if(cbptr == NULL)
	{return cbstatus->Null_staus;}
else
{
	(cbptr-> buffptr) = malloc(length);
	(cbptr-> size) = length;
	if(cbptr == NULL)
		{return cbstatus->Null_status;}
	else
		{return cbstatus->Success;}
}
}

uint8_t CB_destroy((CB_t)* cbptr)
{
if(cbptr == NULL)
	{return cbstatus->Null_status;}
else
	{
	free_words(cbptr);
	return cbstatus->Success;
	}	
}
