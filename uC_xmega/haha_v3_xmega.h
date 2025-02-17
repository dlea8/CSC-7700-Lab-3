/*
 * haha_v3_xmega.h
 *
 * HaHa v3.0 Board
 *  Author: Reiner Dizon-Paradis
 */ 


#ifndef HAHA_V3_XMEGA_H_
#define HAHA_V3_XMEGA_H_

#include "avr_compiler.h"
// #include "spi_driver.h" // Uncomment if using SPI
#include <avr/io.h>

/* Pin Definitions for Chip Interconnection - Refer to the HaHa Manual */
#define HAHA_V3_CM_PORT				PORTA
#define HAHA_V3_CLK_INTER_PORT		PORTC
#define HAHA_V3_CLK_INTER_PIN		PIN0_bm
#define HAHA_V3_CLK_INTER_DELAY		25

/* Function Prototypes */
void haha_v3_interBegin(void);
void haha_v3_clkInterPos(void);
void haha_v3_clkInterNeg(void);
void haha_v3_sendDataToFPGA(uint8_t data);





/* SPI Declarations */
#ifdef SPI_DRIVER_H

/* Global variables */
SPI_Master_t spiMasterC;

/* Pin Definitions for SS for W25N Flash */
#define W25N_SS_PORT        PORTC
#define W25N_SS_PIN         PIN4_bm
#define W25N_ss_en()        SPI_MasterSSLow(&W25N_SS_PORT, W25N_SS_PIN)
#define W25N_ss_di()        SPI_MasterSSHigh(&W25N_SS_PORT, W25N_SS_PIN)

/* Pin Definitions for Flash HOLD_N pin/port */
#define W25N_HOLD_N_PORT    PORTE
#define W25N_HOLD_N_PIN     PIN1_bm

/* Pin Definitions for Flash WP_N pin/port */
#define W25N_WP_N_PORT      PORTE
#define W25N_WP_N_PIN       PIN2_bm


/* Pin Definitions for SS for MC3635 Accelerometer */
#define MC3635_SS_PORT      PORTE
#define MC3635_SS_PIN       PIN3_bm
#define MC3635_ss_en()      SPI_MasterSSLow(&MC3635_SS_PORT, MC3635_SS_PIN)
#define MC3635_ss_di()      SPI_MasterSSHigh(&MC3635_SS_PORT, MC3635_SS_PIN)


/* Function Prototypes */
void haha_v3_SPIBegin(void);

#endif




#endif
