/*
 * timer.h
 *
 *  Created on: 27/05/2014
 *      Author: Wellington
 */

#ifndef TIMER_H_
#define TIMER_H_


void secondsElapsed(int);
void initClockTime(void);
void initTest(void);
void quaterMsElapsed(int);
void startTxTimeout(int);
int partialTxTimeout(void);
int getMs();
int getSec();


#endif /* TIMER_H_ */
