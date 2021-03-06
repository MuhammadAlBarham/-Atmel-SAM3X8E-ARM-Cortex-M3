/*
 * Test.c
 *
 * Created: 5/12/2019 12:19:41 PM
 * Author : Phantom
 */ 
#include "sam.h"

int main(void)
{
    /* Initialize the SAM system */
	// It is Used to initialize the Microcontroller to full (84 MHz)
    SystemInit();							// A device-specific system configuration function
	
	/* 
	extern void WDT_Disable( Wdt* pWDT )
	{
		pWDT->WDT_MR = WDT_MR_WDDIS;
	}
	
	*/
	// PIO PARALLER INPUT/OUTPUT 
	 
		WDT->WDT_MR = WDT_MR_WDDIS;				// Disable the Watchdog Timer	
	
		// PMC->PMC_PCER0 =(1<<12);			//Enable Peripheral Clock PMC_PCER1
	
		// Output 50Hz PWM at a resolution of 14 bits on pin DAC1 (pin: PB16, peripheral: PWML0)
		// PWM Set-up on pin: DAC1`
		//PMC->PMC_PCER1|= PMC_PCER1_PID36						  // Enable CLOCK PWM FROM THE PMC

		
		  REG_PMC_PCER1 |= PMC_PCER1_PID36;
		// Page 563 through the PMC_PCER
		

			                   
		PIOB->PIO_ABSR|=(1u<<16); 							   // Set PWM pin peripheral type A or B, in this case B
		// PB16 is the PWML0 through based on page 40 
		
		PIOB->PIO_PDR|=(1u << 16);								// Set the corresponding pin to be the peripheral 
		// PAGE 634 PDR register 
		
		// PDR is 0 (no effect) & PDR is 1 (enable the peripheral and disable the PIO controller)
		
		
		// Select the clock of the register 
		REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42);     // Set the PWM clock rate to 2MHz (84MHz/42)
		// clock register page 1006  
		// READ A bout it facously 

		REG_PWM_CMR0 = PWM_CMR_CALG | PWM_CMR_CPRE_CLKA;      // Set the clock source as CLKA
		
		// CMR_CALG is the channel Alignment 
		// CMR_CPRE_CLKA is the Channel Pre-Scaler with CLock A  
		 
		
		REG_PWM_CPRD0 = 2000;                                 // Set the PWM periode {(2*2000*42)/84MHz}
		// Set the period of the waveform 
		
		//  The value must be define between the 0 and CPRD (period)
		
		REG_PWM_CDTY0 = 1000;                                 // Set the PWM duty cycle to 1500 - center the servo
		
	
		//page 1007 
		REG_PWM_ENA = PWM_ENA_CHID0;                          // Enable the PWM channel
	    // Enable the PWM output for Channel x
	/*
		REG_PMC_PCER1 |= PMC_PCER1_PID36;                     // Enable PWM
		REG_PIOB_ABSR |= PIO_ABSR_P16;                        // Set PWM pin perhipheral type A or B, in this case B
		REG_PIOB_PDR |= PIO_PDR_P16;                          // Set PWM pin to an output
		REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42);     // Set the PWM clock rate to 2MHz (84MHz/42)
		REG_PWM_CMR0 = PWM_CMR_CALG | PWM_CMR_CPRE_CLKA;      // Enable dual slope PWM and set the clock source as CLKA
		REG_PWM_CPRD0 = 20000;                                // Set the PWM frequency 2MHz/(2 * 20000) = 50Hz
		REG_PWM_CDTY0 = 1500;                                 // Set the PWM duty cycle to 1500 - centre the servo
		REG_PWM_ENA = PWM_ENA_CHID0;                          // Enable the PWM channel
	
	*/
	
	
    while (1) 
    {
		
		   // PIOB->PIO_OSR ==0x02000000 check is 0 ( YES it is Input) 
		   // PIOB->PIO_PUSR == 0x08000000 CHECK IS CORRECT 
		   // It is at zero level ( PIOB->PIO_PDSR  & (1<<25) ) false 
		  
		if ( 0 ) 
		{
					PIOB->PIO_ODSR|=0x08000000u;				// OUTPUT DATA STATUS REGISTER (used to drive data on the line )
		}
		else 
		{
					PIOB->PIO_ODSR&=0xf7ffffffu	;
		}

		
    }
	return 0 ; 
}

