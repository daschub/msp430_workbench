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
#define MAX_OPTIONS         20
#define MAX_ARGUMENTS       10
#define MAX_PARAMETERS      10
#define MAX_LENGTH_STRING   20

typedef struct
{
    uint8_t parameter[MAX_PARAMETERS][MAX_LENGTH_STRING];
} eingabe_t;




/********************************************
 * Prototypes
 ********************************************/
uint8_t console_debug(void);



#endif /* HEADERS_CONSOLE_H_ */
