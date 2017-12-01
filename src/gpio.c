
GPIO_nrf_init(){
        SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;// Clock get to PORT C
	SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;//Clock get to SPI0
	PTC_BASE_PTR->PDDR |= 0x10; //Set pin 4 port C i.e PCS as output direction
	PTC_BASE_PTR->PDOR |= 0x10; //Set pin 4 port C i.e PCS as output
	PORTC->PCR[4] = PORT_PCR_MUX(1);  // PCS
	PORTC->PCR[5] = PORT_PCR_MUX(2);  // SCK
	PORTC->PCR[6] = PORT_PCR_MUX(2);  // MOSI
	PORTC->PCR[7] = PORT_PCR_MUX(2);  // MISO
        PTC_BASE_PTR->PSOR = 1<<4;//make gpio chip high
	SPI0->C1 = 0x50;// Enable SPI and set as Master
        SPI0_BR = (SPI_BR_SPPR(0x03) | SPI_BR_SPR(0x04)); 
        PTC_BASE_PTR->PCOR = 1<<4; //Chip select low
	nrf_write_register(NORDIC_CONFIG_REG); //write command to Config register
	SPI_write(0x03);//Write data to Config register
        PTC_BASE_PTR->PSOR = 1<<4; //Chip select high
        SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; //enable clock to port B
	uint8_t c;
	PTC_BASE_PTR->PCOR = 1<<4; //Chip select low
	nrf_read_register(NORDIC_CONFIG_REG); // read command to Config register
        c=SPI_write(0XFF);
        PTC_BASE_PTR->PSOR = 1<<4;
}
