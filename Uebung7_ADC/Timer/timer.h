/*
 * timer.h
 *
 *  Created on: 20.05.2019
 *      Author: danielschubert
 */

#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

uint16_t delay;                                    // in msec (Zahl wird mit 1millisec multipliziert)
uint16_t countOverflows;

void timer_init(void);
void start_timer(void);
void stop_timer(void);
void timer_delay(uint16_t delay);

#endif /* TIMER_TIMER_H_ */
