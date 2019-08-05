/*
 * console.h
 *
 *  Created on: 01.08.2019
 *      Author: danielschubert
 */

#ifndef HEADERS_CONSOLE_H_
#define HEADERS_CONSOLE_H_



/********************************************
 * defines/typedefs
 ********************************************/
#define MAX_COMMANDS        10
#define MAX_OPTIONS         17
#define MAX_ARGUMENTS       10
#define MAXLENGTH_ARRAY     20
#define MAX_PARAMETERS      10

typedef struct
{
    uint8_t commands[MAX_COMMANDS][MAXLENGTH_ARRAY];
    uint8_t options[MAX_OPTIONS][MAXLENGTH_ARRAY];
    uint8_t arguments[MAX_ARGUMENTS][MAXLENGTH_ARRAY];
} parameter_t;


typedef struct
{
    uint8_t parameter[MAX_PARAMETERS][MAXLENGTH_ARRAY];
} eingabe_t;




/********************************************
 * Prototypes
 ********************************************/

uint8_t validateConsoleParameter(uint8_t);
uint8_t splitConsoleString(uint8_t*);
uint8_t commandHandler(uint8_t*);
void temperaturHandler(uint8_t*);
void adcHandler(uint8_t*);
void rtcHandler(uint8_t*);
uint8_t ledHandler(void);
uint8_t addLeds(uint8_t, uint8_t*);



#endif /* HEADERS_CONSOLE_H_ */
