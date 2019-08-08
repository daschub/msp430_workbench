/*
 * handler.h
 *
 *  Created on: 08.08.2019
 *      Author: danielschubert
 */

#ifndef SOURCES_HANDLER_H_
#define SOURCES_HANDLER_H_


#define LM75_LENGHT             2
#define PCF8574T_LENGHT         1
#define LED_ARRAY              10


/********************************************
 * Prototypes
 ********************************************/
void command_debug(void);

void commandHandler(void);

uint8_t* temperatureHandler(void);
void adcHandler(uint8_t*);
void rtcHandler(uint8_t*);
uint8_t ledHandler(void);




#endif /* SOURCES_HANDLER_H_ */
