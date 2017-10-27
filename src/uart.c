/**
 * @file circbuf.c
 * @brief This file contains circular buffer operation functions.
 * @author monish and sanika
 * @date oct 25s, 2017
 *
 * circbuf.c
 * @Long description:-
 */
#include "system_MKL25Z4.h"
#include "MKL25Z4.h"
#include "uart.h"
#include "circbuf.h"
#define CLOCK_SETUP = 1 



/***********************************************************************
 * @brief UART_configure()  
 * This function configures the UART
 ***********************************************************************/
void UART_configure(void){
	uint8_t length = 8; 
	uint16_t baud_rate;//baud value holder
	//configure PTA1 & PTA2 as alt2=uart0
	PORTA_PCR1 |= PORT_PCR_MUX(2);
	PORTA_PCR2 |= PORT_PCR_MUX(2);
	PTA_BASE_PTR->PDDR |= (uint32_t)(1<<2);//Tx as an output, Rx is input by default
	//disable receiver and transmitter and load 8n1 settings
	UART0_C2 =0;
	UART0_C1 = 0;
	UART0_C3 = 0;
	UART0_S2 = 0;
	//calculate baudrate value
	baud_rate = (uint16_t)((48000*1000)/(115200 * 16));//change to 20k approx
	//set oversampling ratio to 16 times
	UART0_C4 = UARTLP_C4_OSR(16 - 1);
        UART0_BDH = (baud_rate >> 8) & UARTLP_BDH_SBR_MASK;
	UART0_BDL = (baud_rate & UARTLP_BDL_SBR_MASK);
	//Initialize transmit and receive circular buffers
	CB_t* tx_buffer;
	CB_t* rx_buffer;
	CB_init(CB_t* tx_circbuf,length);
 	CB_init(CB_t* rx_circbuf,length);
	UART0_C2 |= (uint32_t)(UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK | UARTLP_C2_RIE_MASK);
	//enable receiver interrupts
	NVIC_ICPR |= (uint32_t)(1<<(INT_UART0-16));//clear pending UART0 interrupts
	NVIC_ISER |= (uint32_t)(1<<(INT_UART0-16));//enable UART0 interrupts
}


/***********************************************************************
 * @brief UART_send()  
 * This function stores the value to be transmitted in transmit circular buffer
 * @tx_circbuf pointer to circular buffer
 ***********************************************************************/
void UART_send (CB_t* tx_circbuf)
{
uint8_t* temp;
CB_buffer_remove_item(tx_circbuf,temp);
while(!((UART0_S1 & 0x80)==0x80)); 
UART0_D = *temp;
}
 
/***********************************************************************
 * @brief UART_send_n()  
 * This function stores values from a certain memory location to be transmitted in transmit circular buffer
 * @tx_circbuf pointer to circular buffer
 * @length length of data
 ***********************************************************************/
void UART_send_n(CB_t* tx_circbuf,uint8_t length) 
{
uint8_t* temp;
uint8_t i;
for(i=0;i<length;i++)
{
	CB_buffer_remove_item(tx_circbuf,temp);
	while(!((UART0_S1 & 0x80)==0x80)); 
	UART0_D = *temp; 
}
}


/***********************************************************************
 * @brief UART_receive()  
 * This function stores a from receive circular buffer to  a certain memory location
 * @rx_circbuf pointer to circular buffer
 ***********************************************************************/
uint8_t UART_receive(CB_t* rx_circbuf) 
{
uint8_t* temp;
while(!((UART0_S1 & 0x20)==0x20)); 
*temp = UART0_D;
CB_buffer_add_item(rx_circbuf,temp);
return Success;
}
/***********************************************************************
 * @brief UART_receive_n()  
 * This function stores multiple values from receive circular buffer to  a certain memory location
 * @rx_circbufpointer to circular buffer
 * @length length of data
 ***********************************************************************/
uint8_t UART_receive_n(CB_t* rx_circbuf,uint8_t length)
{
uint8_t* temp;
uint8_t i;
for(i=0;i<length;i++)
{
	while(!((UART0_S1 & 0x20)==0x20)); 
	*temp = UART0_D;
	CB_buffer_add_item(rx_circbuf,temp);
}
return Success;
}

/***********************************************************************
 * @brief UART0_IRQHandler()
 * This function checks the register values after interrupt occurs and sends or receives data by UART
 ***********************************************************************/
void UART0_IRQHandler()
{
uint8_t* temp;
}

void ​ ​ UART0_IRQHandler();
1. This​ ​ function​ ​ is​ ​ the​ ​ IRQ​ ​ handler​ ​ for​ ​ the​ ​ UART.
2. You​ ​ will​ ​ need​ ​ to​ ​ handle​ ​ two​ ​ types​ ​ of​ ​ interrupts​ ​ in​ ​ this​ ​ function
a. Receive​ ​ Interrupts
b. Transmit​ ​ interrupt
3. Each​ ​ interrupt​ ​ should​ ​ clear​ ​ their​ ​ associated​ ​ flag​ ​ when​ ​ completed​ ​ but​ ​ only​ ​ if​ ​ they​ ​ were​ ​ set
4. This​ ​ routine​ ​ should​ ​ be​ ​ as​ ​ short​ ​ as​ ​ possible
