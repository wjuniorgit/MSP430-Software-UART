/*
 * timer.c
 *
 *  Created on: 27/05/2014
 *      Author: Wellington
 */

#include "msp430g2553.h"
#include "timer.h"
#include "pins.h"
#include "defines.h"

volatile int msCounter;
volatile int msCronometer;
volatile long secCounter;
volatile int startCronometer; //BOOL
volatile bool starttxcronometer;
volatile int txcronometer;
volatile int txtimeout;

void initClockTime() {

	msCounter = 0;
	secCounter = 0;
	msCronometer = 0;
	startCronometer = FALSE;
	starttxcronometer = false;

	WDTCTL = WDT_MDLY_0_5;              // WDT as interval timer (period 8 ms)
	IE1 |= WDTIE;

}

void startTxTimeout(int timeout) {
	txcronometer = 0;
	starttxcronometer = true;
	txtimeout = timeout *16;
}
int partialTxTimeout() {
	return txcronometer/16;
}

void secondsElapsed(int interval) {
	/*
	 int startTime = secCounter;
	 int presentTime = 0;

	 while (presentTime - startTime < interval) {

	 presentTime = secCounter;
	 }*/

	msCronometer = 0;
	int presentTime = 0;

	//activate cronometer
	startCronometer = TRUE;              //BOOL
	int intervalEnd = 32000 * interval;

	while (presentTime < intervalEnd) {

		presentTime = msCronometer;
	}

	//de-activate cronometer
	startCronometer = FALSE;              //BOOL
	msCronometer = 0;

}

void quaterMsElapsed(int interval) {

	msCronometer = 0;
	int presentTime = 0;

	//activate cronometer
	startCronometer = TRUE;              //BOOL
	int intervalEnd = 8 * interval;

	while (presentTime < intervalEnd) {
		presentTime = msCronometer;
	}

	//de-activate cronometer
	startCronometer = FALSE;              //BOOL
	msCronometer = 0;

}

int getMs() {

	int ms;
	ms = msCounter / 16;
	return ms;

}

int getSec() {

	return secCounter;
}

void initTest(){
	secCounter = 0;
	msCounter = 0;
}

#pragma vector=WDT_VECTOR
__interrupt void wdt_timer(void) {

	msCounter = msCounter + 1;

	if (msCounter == 32000) {
		GREEN_LED_TOGGLE();
		secCounter = secCounter + 1;
		msCounter = 0;
	}

	if (startCronometer == TRUE) {
		msCronometer = msCronometer + 1;
	}

	if (starttxcronometer) {
		txcronometer = txcronometer + 1;
		if (txcronometer > txtimeout) {
			starttxcronometer = false;
		}
	}

}
