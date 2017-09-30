/*
 * conversion.c
 *
 *  Created on: Sep 29, 2017
 *      Author: monish
 */
#include <memory.h>

int32_t numvalue(short flag,uint8_t* ptr, uint8_t digits, uint32_t base)
{
	short i;
	int32_t number;
	for(i=0;i<digits;i++)
	{
		number = base*number + *(ptr+i);
	}
	if(flag==1)
	{
		number *= -1;
	}
}

char hexcon(int temp)
{
	switch(temp)

			case 10:
			return 'A';

			case 11:
			return 'B';

			case 12:
			return 'C';

			case 13:
			return 'D';

			case 14:
			return 'E';

			case 15:
			return 'F';

			default:
			return temp +'0';
}

uint8_t i2a(short i,int32_t data, uint8_t * ptr, uint32_t base)
{
	short temp;
	while(data>=base)
	{
	temp=data%base;
	*(ptr+i)=temp +'0';
	data=data/base;
	i++;
	}
	*(ptr+i)=data +'0';
	i++;
	*(ptr+i)='\0';
	i++;
	return i;
}

void compli(uint8_t * ptr,short i)
{	short j,c1=0,c2;
	for(j=0;j<i;j++)
	{
		c2=*(ptr+i-2-j)&c1
		*(ptr+i-2-j)=*(ptr+i-2-j)^c1;
		c1=c2;
	}
	return;
}

int32_t a2i(uint8_t * ptr, uint8_t digits, uint32_t base)
{
	short i=0,j=0;
	int32_t number=0;
	while(*(ptr+i)!='\0')
	{
		number = number + (*(ptr+i)-48) * base;
		i++;
	}
	return i;
}


uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base)
{
	short i=0,j,k,l;
	var temp;
	switch base:
	{
		case 2:
			if (data < 0)
			{
		    *ptr=1+'0';
		    ptr++;
		    data *= -1;
		    i=i2a(i,data,*ptr,base);
		    compli(ptr,i);
		    i++;
			return i;
			}
			*(ptr)=0;
			ptr++;
			i++;
			i=i2a(i,data,*ptr,base);
			my_reverse(ptr,i-1);
			return i;

		case 8:
			l=0;
			i=uint8_t my_itoa(data,ptr,2);
			k=i;
			j=(i-1)%3;
			temp=*(ptr)
			for(k-1;k>=0;k--)
			{
			*(ptr+k+3-j)=*(ptr+k);
			}
			for(k=0;k<3-j;k++)
			{
			*(ptr+i)=temp;
			}
			for(k=0;k<i+j-1;k+=3)
			{
			temp=*(ptr+k)*4+*(ptr+k+1)*2+*(ptr+k+2);
			*(ptr+l)=temp + '0';
			l++;
			}
			*(ptr+l)='\0';
			l++;
			return l;

		case 10:
			if (data < 0)
			{
				*ptr='45';
				ptr++;
				data *= -;
				i=i2a(data,*ptr,base);
				my_reverse(ptr,i-1);
				i++;
				return i;
			}
			i=i2a(data,*ptr,base);
			my_reverse(ptr,i-1);
			return i;

		case 16:
			l=0;
			i=uint8_t my_itoa(data,ptr,2);
			k=i;
			j=(i-1)%4;
			temp=*(ptr)
			for(k-1;k>=0;k--)
			{
				*(ptr+k+4-j)=*(ptr+k);
			}
			for(k=0;k<4-j;k++)
			{
				*(ptr+i)=temp;
			}
			for(k=0;k<i+j-1;k+=4)
			{
			temp=*(ptr+k)*8+*(ptr+k+1)*4+*(ptr+k+2)*2+*(ptr+k+3);
			temp=hexcon(temp);
			*(ptr+l)=temp;
			l++;
			}
			*(ptr+l)='\0';
			l++;
			return l;

		default:
			printf("Not a valid base");
			return 0;
	}
}

int32_t my_atoi(uint8_t* ptr, uint8_t digits, uint32_t base)
{	short i,j,k,flag=0;
	int32_t number=0,temp;
	switch(base)
	{
		case 2:
			if (*(ptr)=='1')
			{
				compli(ptr,digits);
				flag=1;
			}
			number=numvalue(flag,ptr,digits,base);
			return number;

		case 8:
			for(i=digits-1;i>=0;i--)
			{
				temp = *(ptr+i);
				i2a(3*i,temp, ptr,2);
				my_reverse(ptr,3);
			}
			number=my_atoi(ptr,3*digits,2);
			return number;

		case 10:
			if (*(ptr)=='-')
			{
				ptr++;
				digits--;
				flag=1;
			}
			number=numvalue(flag,ptr,digits,base);
			return number;

		case 16:
			for(i=digits-1;i>=0;i--)
			{
				temp = *(ptr+i);
				i2a(4*i,temp, ptr,2);
				my_reverse(ptr,4);
			}
			number=int32_t my_atoi(ptr,4*digits,2);
			return number;

		default:
			printf("Not a valid base");
			return 0;
	}
}

int8_t big_to_little32(uint32_t* data, uint32_t length)
{
	short i,j;
	char* temp;
	for(i=0;i<length;i++)
	{
		data=data+4*i;
		for(j=0;j<2;j++)
		{
			 temp = *(data+i);
			 *(data+i) = *(data+3-i);
			 *(data+3-i) = temp;
		}
	}
	return 1;
}

int8_t little_to_big32(uint32_t * data, uint32_t length)
{	short i,j;
	char* temp;
	for(i=0;i<length;i++)
	{
		data=data+4*i;
		for(j=0;j<2;j++)
		{
			 temp = *(data+i);
			 *(data+i) = *(data+3-i);
			 *(data+3-i) = temp;
		}
	}
	return 1;
}
