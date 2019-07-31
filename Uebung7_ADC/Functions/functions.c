/*
 * functions.c
 *
 *  Created on: 20.05.2019
 *      Author: danielschubert
 */

#ifndef FUNCTIONS_FUNCTIONS_C_
#define FUNCTIONS_FUNCTIONS_C_

#include <stdint.h>

#include <msp430.h>
#include <strings.h>
#include <stdio.h>
#include <math.h>

uint16_t i;

/** TODO
 * @intValue übergebe gewünschten Int-Wert, der zu einen String gewandelt wird
 * @decimalValue gibt an, wie viele Nachkommastellen angegeben werden

 *
 * gegebene Zahl durch Modulo, dann durch entsprechenden Zählerfaktor teilen
 * dies ergibt die einzelne Ziffer.
 * dann mit z.b. switch case mit ASCII 31 addieren und in array speichern
 *
 */
char *convertIntToString(uint32_t intValue/*, int decimalValue*/)
{
    uint8_t array[10];
    uint32_t count = 1,  temp = intValue , temp2 = intValue;
    //* Anzahl der Ziffern
    while (temp > 10){
    temp /= 10;
    count++;
    } // while

    temp = pow(10,count);

    for(i = 0; i < count; i++){
        temp2 = intValue % temp;
        temp /= 10;
        array[i] = temp2 / temp;
    } // for
    return array;
} // convert Int to String


#endif /* FUNCTIONS_FUNCTIONS_C_ */
