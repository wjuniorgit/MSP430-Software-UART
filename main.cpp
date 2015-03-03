#include "msp430g2553.h"
#include "softUart.h"
#include "globals.h"
#include "timer.h"

#define BUTTON BIT3


char btnpress;
unsigned char check;
char value;

/*
 * main.c
 */
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	if (CALDCO_16MHZ == 0xFF)				// If calibration constant erased
			{
		while (1)
			;                               // do not load, trap CPU!!
	}

	DCOCTL = 0;                          // Select lowest DCOx and MODx settings
	BCSCTL1 = CALBC1_16MHZ;                    // Set DCO
	DCOCTL = CALBC1_16MHZ;


	initClockTime();

	//endbtn
	btnpress = 0;

	softUart su;

	_BIS_SR(GIE);                            // Enable CPU interrupts

	su.xmit("\n\rSoftware UART\n\r");



}


