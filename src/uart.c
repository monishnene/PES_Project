
#include "system_MKL25Z4.h"
#include "MKL25Z4.h"

#define CLOCK_SETUP = 1 

#include "uart.h"
//configure UART
void init_uart0(void){
	uint16_t ubd;//baud value holder
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
	ubd = (uint16_t)((48000*1000)/(57600 * 16));
	//set oversampling ratio to 16 times
	UART0_C4 = UARTLP_C4_OSR(16 - 1);
        UART0_BDH = (ubd >> 8) & UARTLP_BDH_SBR_MASK;
	UART0_BDL = (ubd & UARTLP_BDL_SBR_MASK);
	//Initialize transmit and receive circular buffers
	buf_reset(tx_buffer1,BUFLEN);
	buf_reset(rx_buffer,BUFLEN);
	UART0_C2 |= (uint32_t)(UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK | UARTLP_C2_RIE_MASK);
	//enable receiver interrupts
	NVIC_ICPR |= (uint32_t)(1<<(INT_UART0-16));//clear pending UART0 interrupts
	NVIC_ISER |= (uint32_t)(1<<(INT_UART0-16));//enable UART0 interrupts
}


void uart_putchar (uint8_t ch){
	/* Wait until space is available in the FIFO */
	while(!(UART0_S1 & (1<<8))==(1<<8));
	/* Send the character */
	UART0_D = (uint8_t)ch;
}

//UART0 brief interrupt handler
void UART0_IRQHandler(){
	if((UART0_S1 & UART_S1_RDRF_MASK)==UART_S1_RDRF_MASK){
		data = (uint8_t)UART0_D;
		data_available=1;
	}
}
<type> ​ ​ UART_configure ​ ​ ();
1. Configures​ ​ UART​ ​ to​ ​ the​ ​ given​ ​ settings.
62. No hardcoded configurations may be used. All settings need to use predefined Bit Masks and
macro​ ​ functions​ ​ to​ ​ help​ ​ determine​ ​ calculated​ ​ values
<type> ​ ​ UART_send ​ ​ ( ​ ​ <data-to-send> ​ ​ );
1. This​ ​ function​ ​ will​ ​ send​ ​ a ​ ​ single​ ​ byte​ ​ down​ ​ a ​ ​ specific​ ​ UART​ ​ device
2. The​ ​ function​ ​ will​ ​ take​ ​ 1 ​ ​ argument:
a. Pointer​ ​ to​ ​ the​ ​ data​ ​ item​ ​ to​ ​ send
3. This​ ​ function​ ​ should​ ​ block​ ​ on​ ​ transmitting​ ​ data
<type> ​ ​ UART_send_n ​ ​ ( ​ ​ <data-to-send>, ​ ​ <length-of-data> ​ ​ );
1. Function​ ​ takes​ ​ 2 ​ ​ arguments
a. Pointer​ ​ to​ ​ a ​ ​ contiguous​ ​ block​ ​ of​ ​ data​ ​ that​ ​ needs​ ​ to​ ​ be​ ​ transmitted
b. Number​ ​ of​ ​ items​ ​ to​ ​ transmit
2. This​ ​ function​ ​ should​ ​ block​ ​ on​ ​ transmitting​ ​ data
<type> ​ ​ UART_receive( ​ ​ <received-data> ​ ​ );
1. This​ ​ function​ ​ should​ ​ return​ ​ a ​ ​ received​ ​ byte​ ​ on​ ​ the​ ​ UART​ ​ using​ ​ an​ ​ input​ ​ parameter​ ​ pointer.
2. This​ ​ function​ ​ should​ ​ block​ ​ until​ ​ a ​ ​ character​ ​ has​ ​ been​ ​ received.
<type> ​ ​ UART_receive_n ​ ​ ( ​ ​ <received-data>, ​ ​ <length-of-data-to-receive> ​ ​ );
1. This​ ​ function​ ​ should​ ​ receive​ ​ a ​ ​ number​ ​ of​ ​ bytes​ ​ on​ ​ the​ ​ UART.
2. Function​ ​ takes​ ​ 2 ​ ​ arguments
a. Pointer​ ​ to​ ​ a ​ ​ memory​ ​ location​ ​ to​ ​ place​ ​ data​ ​ that​ ​ is​ ​ being​ ​ received
b. Number​ ​ of​ ​ items​ ​ to​ ​ receive
3. This​ ​ function​ ​ should​ ​ block​ ​ until​ ​ a ​ ​ number​ ​ of​ ​ characters​ ​ have​ ​ been​ ​ received.
void ​ ​ UART0_IRQHandler();
1. This​ ​ function​ ​ is​ ​ the​ ​ IRQ​ ​ handler​ ​ for​ ​ the​ ​ UART.
2. You​ ​ will​ ​ need​ ​ to​ ​ handle​ ​ two​ ​ types​ ​ of​ ​ interrupts​ ​ in​ ​ this​ ​ function
a. Receive​ ​ Interrupts
b. Transmit​ ​ interrupt
3. Each​ ​ interrupt​ ​ should​ ​ clear​ ​ their​ ​ associated​ ​ flag​ ​ when​ ​ completed​ ​ but​ ​ only​ ​ if​ ​ they​ ​ were​ ​ set
4. This​ ​ routine​ ​ should​ ​ be​ ​ as​ ​ short​ ​ as​ ​ possible
