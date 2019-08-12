/*
 * timer.h
 *
 *  Created on: 20.05.2019
 *      Author: danielschubert
 */

#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

uint8_t command_temperatureState;

uint16_t delay;                                    // in msec (Zahl wird mit 1millisec multipliziert)
uint16_t countOverflows;

void timer1_init(void);
void start_timer1(void);
void stop_timer1(void);
void timer1_delay(uint16_t delay);

#endif /* TIMER_TIMER_H_ */
