/*
 * conversion.c
 *
 *  Created on: Sep 29, 2017
 *      Author: monish and sanika
 */
#include<stdio.h>
#include <memory.h>
#include<stdlib.h>

int32_t numvalue(short flag,unsigned char* ptr, unsigned char digits, unsigned int base)
{
	short i;
        unsigned int number;
	for(i=0;i<digits;i++)
	{
		number = base*number + *(ptr+i);
	}
	if(flag==1)
	{
		number *= -1;
	}
}

short table(char a)
{
if(a=='0')
{return 0;}
else if(a=='1')
{return 1;}
}

char hexcon(int temp)
{
	switch(temp)
	{

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
}

unsigned char i2a(short i, unsigned int data, unsigned char* ptr, unsigned int base)
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

void compli(unsigned char* ptr,short i)
{	short j,c1=1,c2,temp;
	
	for(j=0;j<i;j++)
	{
	temp=*(ptr+j)^1;
	*(ptr+j)=temp;	
	}

	for(j=0;j<i;j++)
	{	
		c2=*(ptr+i-2-j)&c1;
		temp=*(ptr+i-2-j)^c1;
		*(ptr+i-2-j)=temp;
		c1=c2;
	}
	return;
}

unsigned int a2i(unsigned char* ptr, unsigned char digits, unsigned int base)
{
	short i=0,j=0;
	unsigned int number=0;
	while(*(ptr+i)!='\0')
	{
		number = number + (*(ptr+i)-48) * base;
		i++;
	}
	return i;
}


unsigned char my_itoa(int32_t data, unsigned char* ptr, unsigned int base)
{	
	short i=0,j,k,l=0,a,b,c,d;
	char temp;
	switch (base)
	{
		case 2:
			if (data < 0)
			{
			    	*ptr=1+'0';
			    	ptr++;
			    	data *= -1;
			    	i=i2a(i,data,ptr,base);
				my_reverse(ptr,i-1);
			    	compli(ptr,i);
				i++;	
				return i;
			}
			*(ptr)=0;
			ptr++;
			i= i2a(i,data,ptr,base);
			my_reverse(ptr,i-1);
			i++;
			return i;

		case 8:
			i=my_itoa(data,ptr,2);
			k=i-1;
			j=(k)%3;		
			temp=*(ptr);
			if(j>0)
			{
				for(k=k-1;k>=0;k--)
				{
					*(ptr+k+3-j)=*(ptr+k);
				}
				for(k=0;k<3-j;k++)
				{
					*(ptr+k)=temp;
				}
			}
			for(k=0;k<i+j-2;k+=3)
			{	
				a=table(*(ptr+k));
				b=table(*(ptr+k+1));
				c=table(*(ptr+k+2));			
				temp=a*4+b*2+c;
				*(ptr+l)=temp+'0';
				l++;
			}
			if(*(ptr)=='0')
			{
				for(i=0;i<l;i++)
				{	
					*(ptr)=*(ptr+1);
				}		
			l--;
			}
			*(ptr+l)='\0';
			l++;
			return l;

		case 10:
			if (data < 0)
			{
				*ptr='-';
				ptr++;
				data *= -1;
				i=i2a(i,data,ptr,base);
				my_reverse(ptr,i-1);
				i++;
				return i;
			}
			i= i2a(i,data,ptr,base);
			my_reverse(ptr,i-1);
			return i;

		case 16:
			i=my_itoa(data,ptr,2);
			k=i-1;
			j=(k)%4;		
			temp=*(ptr);
			if(j>0)
			{
				for(k=k-1;k>=0;k--)
				{
					*(ptr+k+4-j)=*(ptr+k);
				}
				for(k=0;k<4-j;k++)
				{
					*(ptr+k)=temp;
				}
			}
			for(k=0;k<i+j-1;k+=4)
			{	a=table(*(ptr+k));
				b=table(*(ptr+k+1));
				c=table(*(ptr+k+2));
				d=table(*(ptr+k+3));			
				temp=a*8+b*4+c*2+d;
				*(ptr+l)=hexcon(temp);
				l++;
			}
			if(*(ptr)=='0')
			{
				for(i=0;i<=l;i++)
				{
					*(ptr)=*(ptr+1);
				}	
			l--;
			}	
			*(ptr+l)='\0';
			l++;
			return l;

		default:
			printf("Not a valid base");
			return 0;
	}
}

int32_t my_atoi(unsigned char* ptr, unsigned char digits, unsigned int base)
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
			number=my_atoi(ptr,4*digits,2);
			return number;

		default:
			printf("Not a valid base");
			return 0;
	}
}

unsigned char  big_to_little32(unsigned int* data, unsigned int length)
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

unsigned char little_to_big32(unsigned int * data, unsigned int length)
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
