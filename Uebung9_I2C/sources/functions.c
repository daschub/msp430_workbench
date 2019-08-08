/*
 * functions.c
 *
 *  Created on: 20.05.2019
 *      Author: danielschubert
 */

#ifndef FUNCTIONS_FUNCTIONS_C_
#define FUNCTIONS_FUNCTIONS_C_

/***********************************************
 * Includes
 ***********************************************/
#include <stdint.h>

#include <msp430.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include "headers/functions.h"
#include "headers/uart.h"


/***********************************************
 * Variables
 ***********************************************/


uint16_t command_setTempCelsius = 1;
uint16_t command_setTempFahrenheit = 0;

const uint8_t LED1 = BIT6;
const uint8_t LED2 = BIT5;
const uint8_t LED3 = BIT4;
const uint8_t LED4 = BIT0;
const uint8_t LED5 = BIT1;
const uint8_t LED6 = BIT7;
const uint8_t LED7 = BIT2;
const uint8_t LED8 = BIT3;
const uint8_t LED_ALL = (LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8);

/***********************************************
 * Prototypes
 ***********************************************/



/***********************************************
 * Functions
 ***********************************************/



/*
 * gibt länge des des übergebenden arrays @para zurück
 */
uint16_t sizeof_t(uint8_t* array)
{
    return sizeof(array)/sizeof(*array);
}



/*
 * setzt Ledzustand
 * @pins die zu setztenden LEDs
 * @mode gibt an ob HIGH oder LOW
 */
uint8_t GPIO_setPinMode(uint8_t pins, uint8_t mode)
{
    uint8_t temp_pins = 0xFF;
    if(mode == HIGH){
        temp_pins &= ~pins;
    } else if (mode == LOW) {
        temp_pins |= pins;
    }
    return temp_pins;
}



/*
 * addiere Leds, für funktion gpio_setpinmode
 */
uint8_t addLeds(uint8_t *ptr)
{
    uint8_t leds = 0;

    while(*ptr){                                           // addiere leds so oft bis keine zahl mehr kommt
        switch(*ptr){
            case '1':
                leds |= LED1;
                break;
            case '2':
                leds |= LED2;
                break;
            case '3':
                leds |= LED3;
                break;
            case '4':
                leds |= LED4;
                break;
            case '5':
                leds |= LED5;
                break;
            case '6':
                leds |= LED6;
                break;
            case '7':
                leds |= LED7;
                break;
            case '8':
                leds |= LED8;
                break;
            default:                                    // alle leds
                leds = 0xFF;
        }
        ptr += 20;                                      // TODO
    } // while;
    return leds;
}



/*
 *  liefert die Temperatur über den LM75 (1bit = 0,5°)
 *  die gelesen zwei bytes werden durch richtiges shiften (s. Datasheet) in den Temperaturwert gewandelt
 *  und mit 5 multipliziert um die dezimalStelle nach dem Komma in Integer auszugeben (@temperatureHandler)
 */
uint16_t LM75_temperature(uint8_t *readBytes)
{
    uint16_t temperature = 0;

    temperature = (uint16_t)readBytes[0] >> 7;                  // lese Buffer

    temperature |= (uint16_t)readBytes[1] << 1;                 // lese Buffer

    temperature &= 0x01FF;
    return temperature*5;                                       // Temperaturwert, letzte stelle ist dezimalstelle
}



#endif /* FUNCTIONS_FUNCTIONS_C_ */

/*
 * alte funktionen
 */

/*
 * vergleicht konsoleneingabe vom benutzer und übergibt den parameter der func compareTransmittedParameter
 *
void compareReceivedParameter(void)                                                                     //TODO
{
    command_konsolenEingabe = 1;

    if (strcasecmp(GET_RTC, receivedString) == 0){                  // ist Eingabe GET_RTC ?
        calender = getCalender();                                   //
    } else if (strcasecmp(SET_RTC, receivedString) == 0){           // ist Eingabe SET_RTC ?
        command_transmitConfig = 1;                               //
    } else if (command_checkString){                                // ist die Eingabe ein neues Datum?
        validateCalender();                                         // prüfe auf sinnvolle Datumseingabe
        command_transmitConfig = 1;
        command_readCalender = 1;
        if (command_checkString){                               // fall richtige datumseingabe
            command_checkString = 0;
        } else {
            command_konsolenEingabe = 0;
        } // if command_checkString

    } else {
        command_konsolenEingabe = 0;
        command_transmitString = 0;                             // TODO eingabe behandlung sobald arrayüberlauf oder genrell unerwarte eingabe

    } // if
} // compareReceivedParameter

*/


/*
 * entscheidet welche Hterm ausgabe -> korrekt eingabe vom benutzer oder unbekannt
 *
void compareTransmittedParameter(void)
{

    if(command_konsolenEingabe){                                // fall: korrekte Konsoleneingabe
       command_konsolenEingabe = 0;

        if(command_readCalender){                                       // soll Kalender gelesen werden ?
            command_readCalender = 0;

            snprintf(transmittedString, "%02d.%02d.%d, %02d:%02d:%02d Uhr \r\n", calender.day, calender.month,
            calender.year, calender.hour, calender.minute, calender.second);                                // Datum als String
        } // if command_ReadCalender

        else if (command_transmitConfig){                               // soll geändertes Datum gelesen werden
            command_transmitConfig = 0;

            uart_send("Gebe Datum im Format DD.MM.YYYY,hh:mm:ss ein\r\n");
            command_checkString = 1;

        } // else if command_transmitConfig


*/
