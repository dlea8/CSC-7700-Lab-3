/*
 * haha_v3_xmega.c
 *
 * HaHa v3.0 Board
 *  Author: Reiner Dizon-Paradis
 */ 

#include "haha_v3_xmega.h"                                               

/* Set up chip interconnection as outputs */
void haha_v3_interBegin(void)
{
	HAHA_V3_CM_PORT.DIRSET = 0xFF;	// set all PORTA as output
	HAHA_V3_CM_PORT.OUT = 0x00;		// set PORTA to all 0's
	HAHA_V3_CLK_INTER_PORT.DIRSET = HAHA_V3_CLK_INTER_PIN; // set PC0 as output
	haha_v3_clkInterNeg();	// set to falling edge of clock
}

/* Send a rising edge for the Chip interconnection clock */
void haha_v3_clkInterPos(void)
{
	HAHA_V3_CLK_INTER_PORT.OUTSET = HAHA_V3_CLK_INTER_PIN; 
	_delay_ms(HAHA_V3_CLK_INTER_DELAY);
}

/* Send a falling edge for the Chip interconnection clock */
void haha_v3_clkInterNeg(void)
{
	HAHA_V3_CLK_INTER_PORT.OUTCLR = HAHA_V3_CLK_INTER_PIN;
	_delay_ms(HAHA_V3_CLK_INTER_DELAY);
}

/* Send a byte data to the FPGA */
void haha_v3_sendDataToFPGA(uint8_t data)
{
	HAHA_V3_CM_PORT.OUT = data;
	haha_v3_clkInterPos(); // rising edge
	haha_v3_clkInterNeg(); // falling edge
}




/* SPI Functions */
#ifdef SPI_DRIVER_H
void haha_v3_SPIBegin(void)
{
	/* Initialize SPI master on port C */
	SPI_MasterInit(&spiMasterC,
					&SPIC,
					&PORTC,
					false,
					SPI_MODE_0_gc,
					SPI_INTLVL_OFF_gc,
					false,
					SPI_PRESCALER_DIV4_gc);
}



/* Add your own function that initializes SS (HOLD_N, WP_N) ports as needed for selected SPI device. It should called before SPI operations - Example below: */

void init_SS()
{

	// SS setup
	W25N_SS_PORT.DIRSET = W25N_SS_PIN;
	W25N_SS_PORT.PIN4CTRL = PORT_OPC_WIREDANDPULL_gc;

	W25N_SS_PORT.OUTSET = W25N_SS_PIN;

	haha_v3_SPIBegin();	
	
	uint8_t keyByte = 0x00;

	// writing to flash
	W25N_ss_en();
	SPI_MasterTransceiveByte(&spiMasterC, keyByte);
	W25N_ss_di();

	W25N_ss_en();
	unsigned char read_data = SPI_MasterTransceiveByte(&spiMasterC, keyByte);
	W25N_ss_di();

	// need the .v file to send to the FPGA

}

/* Init SS pin as output with wired AND and pull-up. */
// MC3635_SS_PORT.DIRSET = MC3635_SS_PIN;
// MC3635_SS_PORT.PIN4CTRL = PORT_OPC_WIREDANDPULL_gc;

/* Set SS output to high. (No slave addressed). */
// MC3635_SS_PORT.OUTSET = MC3635_SS_PIN;


#endif

