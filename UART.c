/* Includes -------------------------------------------------------------------*/
#include "sam.h"

/* Variables ------------------------------------------------------------------*/

#define LED_PIN 0x08000000u		// external Ram				0000 1000 0000 0000 0000 0000 0000
#define NLED_PIN 0xf7ffffffu	// Vendor-Specific-Device	1111 0111 1111 1111 1111 1111 1111

// #define NLED_PIN 0xf7ffffffu	// Vendor-Specific-Device	1111 0111 1111 1111 1111 1111 1111

/* Prototypes -----------------------------------------------------------------*/
static void intialize_UART (void) ;
uint32_t uart_tx_ready(void);
void uart_write_char(char chr);


// static void delay_ms(uint32_t time_ms);

int main(void) {


	/* Initialize the SAM system */
	// It is Used to initialize the Microcontroller to full (84 MHz)
	SystemInit();							// A device-specific system configuration function
	
	// Disable watchdog timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
		PIOB->PIO_PER |=0x0A000000;		// Port I/O Enable Register 	 (write only)   WPEN is cleared
		
		PIOB->PIO_OER |=LED_PIN;		// OUTPUT  Enable Register		 (Write Only)   to set the direction as OUTPUT
		
		//
		PIOB->PIO_PUDR |=LED_PIN;		// pull_up Disable resistor  { pPio->PIO_PUDR = dwMask ; }  1== Diable
		
	//	PIOB->PIO_OWER |=LED_PIN;		// Output Write Enable register to enable writing to ODSR directly
		
//	PIOB->PIO_ODSR|=LED_PIN;			// OUTPUT DATA STATUS REGISTER (used to drive data on the line )
	
	//PIOB->PIO_ODSR&=NLED_PIN;
				
		
		
	intialize_UART();

	
	while (1) {
		
		uart_write_char('a');
		while (!uart_tx_ready());
		
		
		//if(UART->UART_SR & UART_SR_TXRDY) 	PIOB->PIO_ODSR|=LED_PIN ;   
		
		// if(PIOA->PIO_PSR & PIO_PSR_P9) 	PIOB->PIO_ODSR|=LED_PIN ;  PERIOHERAL IS ACTIVE 
		// if(PIOA->PIO_OSR & PIO_OSR_P9) 	PIOB->PIO_ODSR|=LED_PIN ;  PERIOHERAL
		 
		// if(PIOA->PIO_ABSR & PIO_ABSR_P9) 	PIOB->PIO_ODSR|=LED_PIN ;   // A Function 
		
		
		
	}

}



void intialize_UART (void)
{

	
	//      (2) -->> TWO
	
	//  Disable PIO Control on PA8 & PA9   and set up for Peripheral A
	//  UART PA9 (UTXD)
	PIOA->PIO_PDR  |= PIO_PA9 ;    // Checked
	PIOA->PIO_OER  |= PIO_PA9 ;	// Checked	     // OUTPUT  Enable Register		 (Write Only)   to set the direction  as OUTPUT
	//PIOA->PIO_ABSR &= ~PIO_PA9 ;  	// Checked 	// Set PWM pin peripheral type A or B, in this case B ( Timer 0 )
	PIOA->PIO_PUDR |= PIO_PA9;		// Checked // pull_up Disable resistor  { pPio->PIO_PUDR = dwMask ; }  1== Diable

	
	//  3 ( THREE)
	
	
	// PAGE 634 PDR register
	// PDR is 0 (no effect) & PDR is 1 (enable the peripheral and disable the PIO controller)
	//NVIC_DisableIRQ(TC0_IRQn);
	//NVIC_ClearPendingIRQ(TC0_IRQn);
	//NVIC_SetPriority(TC0_IRQn, 1);
	//NVIC_EnableIRQ(UART_IRQn); // enable UART interrupts
	
	
		// 1  ONE
		
		// Enable the PMC for UART
		// PMC->PMC_PCER0 |= ID_UART ;
		REG_PMC_PCER0 |= PMC_PCER0_PID8;
		
		//		//pmc_enable_periph_clk(ID_TC0);
		
		// Reset and disable receiver and transmitter
	UART->UART_PTCR = UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RXDIS | UART_CR_TXDIS;	
		
	//Reset TX
	UART->UART_CR|= UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RXDIS | UART_CR_TXDIS;

	//configure baud rate
	uint32_t dwBaudRate = 9600;
	UART->UART_BRGR = (SystemCoreClock / dwBaudRate) >> 4;
	
	//UART->UART_BRGR|=0x4D; 	
	UART->UART_IDR = 0xFFFFFFFF;
	
	// Config. Mode register  && Channel Mode
	// NO Parity
	UART->UART_MR|=UART_MR_PAR_NO|UART_MR_CHMODE_NORMAL;;
	
	// enable receiver and transmitter
	UART->UART_CR = UART_CR_RXEN | UART_CR_TXEN;

}

/**
 * Checks if a character can be sent by the UART.
 * @return 1 is returned when a character is ready to be sent,
 * otherwise 0 is returned.
 */

uint32_t uart_tx_ready(void) {
	return (UART->UART_SR & UART_SR_TXRDY);
}

/**
 * Sends a character to the UART.
 * @param chr Character (ASCII code) to send.
 * @pre Call uart_tx_ready() to check if a character can be sent.
 */


void uart_write_char(char chr) {
	UART->UART_THR = (uint32_t) chr;
}

