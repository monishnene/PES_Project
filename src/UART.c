#include <MKL25Z4.H>
#include "uart.h"

typedef struct_PORT_PIN_t{
   PORT_Type *PORT0;
   uint8_t Bit;
   uint32_t Alt;
}PORT_PIN_t;

PORT_PIN_t UART_Port_Pin[] = {
     { //configure PTA1 & PTA2 as alt2=uart0
	PORTA_PCR1 |= PORT_PCR_MUX(2);
	PORTA_PCR2 |= PORT_PCR_MUX(2);
	PTA_BASE_PTR->PDDR |= (uint32_t)(1<<2)};//Tx as an output, Rx is input by default

void UART_configure(void *UARTx, uint32_t Baud) {
 uint16_t clk;
 
if((UARTLP_Type *) UARTx == UART0) {
uint16_t ubd;//baud value holder
	//configure PTA1 & PTA2 as alt2=uart0
	PORTA_PCR1 |= PORT_PCR_MUX(2);
	PORTA_PCR2 |= PORT_PCR_MUX(2);
	PTA_BASE_PTR->PDDR |= (uint32_t)(1<<2);//Tx as an output, Rx is input by default
	//disable receiver and transmitter and load 8n1 settings
   ((UARTLP_Type *) UARTx)->C2 = 0000 1000;
   ((UARTLP_Type *) UARTx)->C1 = 0;
   ((UARTLP_Type *) UARTx)->C3 = 0;
	UART0_S1 |= 1100 0000;
	UART0_S2 = 0;
 SIM_SCGC5 |= 0000 0000 0000 0000 0000 0011 1000 0000;
 SIM_SCGC4 |= 0000 0000 0100 0100 0000 0000 0100 0000;
 SIM->SOPT2 &= ~(0000 0000 0000 0001 0000 0000 0000 0000);
 SIM->SOPT2|= SIM_SOPT2_UART0SRC(1);
 
 clk = SystemCoreClock / Baud;
 ((UARTLP_Type *) UARTx)-> BDH &= ~((0000 1111));
 ((UARTLP_Type *) UARTx)-> BDH |= UARTLP_BDH_SBR(clk);
 ((UARTLP_Type *) UARTx)-> BDL &=  ~(0000 0100);
 ((UARTLP_Type *) UARTx)-> BDL |= UARTLP_BDL_SBR(CLK);
//calculate baudrate value
	ubd = (uint16_t)((48000*1000)/(115200 * 16));
	//set oversampling ratio to 16 times
	UART0_C4 = UARTLP_C4_OSR(16 - 1);
        UART0_BDH = (ubd >> 8) & 00;
	UART0_BDL = ubd & 0000 0100;
	//Initialize transmit and receive circular buffers
	buf_reset(tx_buffer1,BUFLEN);
	buf_reset(rx_buffer,BUFLEN);
	UART0_C2 |= 0010 1100;
	/*//enable receiver interrupts
	NVIC_ICPR |= (uint32_t)(1<<(INT_UART0-16));//clear pending UART0 interrupts
	NVIC_ISER |= (uint32_t)(1<<(INT_UART0-16));//enable UART0 interrupts*/
}

 
void UART_send(void *UARTx, char c){
 if((UARTLP_Type *) UARTx == UART0){
 while (((UARTLP_Type *) UARTx)->S1 & S1-> UART0_C2 |= 1000 1000)
 ((UARTLP_Type *) UART0)->D = c;
 else{
qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq     while((UART_Type*) UARTx)-> S1 & UARTLP_S1_TDRE_MASK);
    ((UART_Type *) UART0)->D = c;
   }

}

void UART_send_n( void *UARTx, char *ptr) {
 while( *ptr!= '\0') {
 UART_senddata( UART0, *ptr);
 *ptr++;
 }
}

char UART_receive( void *UARTx) {

if((UARTLP_Type *) UARTx = UART0) {
 while (((UARTLP_Type *) UARTx)-> S1& UARTLP_S1_RDRF_MASK) ==0 )
c = ((UARTLP_Type *) UARTx)-> D;
}

else{
  while (((UARTLP_Type *) UARTx)-> S1& UARTLP_S1_RDRF_MASK)==0)
  c= ((UART_Type *) UARTx)->D;
 }

return c;
}

uint8_t UART_receive_n( void *UARTx, char *ptr) {
uint8_t num = 0;
do {
*ptr= UART_receive_n(UARTx);
*ptr ++;
num++;
} while (*(ptr-1)!= '\0');
  return num;
}



