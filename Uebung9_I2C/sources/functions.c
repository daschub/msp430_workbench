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
#include <math.h>
#include "headers/functions.h"
#include "headers/i2c.h"
#include "headers/rtc.h"
#include "headers/uart.h"


/***********************************************
 * Variables
 ***********************************************/

const uint8_t lenArrayLM75 = 2;
const uint8_t lenArrayPCF8574T = 2;
const uint8_t lenArrayLeds = 10;
const uint8_t lenght = 1;

uint8_t PCF8574T_LEDS[lenArrayLeds];
uint8_t readBytes[lenArrayLM75];
uint8_t writeBytes[lenArrayPCF8574T];

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
const uint8_t LEDS = (LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8);




/***********************************************
 * Prototypes
 ***********************************************/



/***********************************************
 * Functions
 ***********************************************/


/*
 * setzt GPIO Pin als Input oder Output
 *
 *TODO
void GPIO_setPin(uint8_t mode, uint16_t port, uint16_t pin)
{
    if(strcasecmp(Input, mode) == 0){                           // ist Eingabe Input ?



    } else if(strcasecmp(Output, mode) == 0){                   // ist Eingabe Output ?

    }


}
*/


uint16_t sizeof_t(uint8_t* array)
{
    return sizeof(array)/sizeof(*array);
}


/*
 * vergleicht HTERM eingabe vom benutzer und behandelt dementsprechend den String
 */
void compareReceivedParameter(void)                                                                     //TODO
{
    command_konsolenEingabe = 1;

    if (strcasecmp(GET_RTC, receivedString) == 0){                  // ist Eingabe GET_RTC ?
        calender = getCalender();                                   //
    } else if (strcasecmp(SET_RTC, receivedString) == 0){           // ist Eingabe SET_RTC ?
        command_transmitConfig = 1;
    } else if (strcasecmp(SET_LED, receivedString) == 0){           // ist Eingabe SET_LED ?
        command_setLed = 1;
    } else if (strcasecmp(LEDS_OFF, receivedString) == 0){           // ist Eingabe SET_LED ?
        command_LedsOff = 1;
    } else if (strcasecmp(SET_LED, receivedString) == 0){           // ist Eingabe SET_LED ?
        command_setLed = 1;                                     //
    } else if (strcasecmp(SET_TEMP_C, receivedString) == 0){        // ist Eingabe SET_TEMP_C ?
        command_setTempCelsius = 1;                                 //
        command_setTempFahrenheit = 0;                              //
    } else if (strcasecmp(SET_TEMP_F, receivedString) == 0){        // ist Eingabe SET_TEMP_F ?
        command_setTempFahrenheit = 1;                              //
        command_setTempCelsius = 0;                                 //
    } else if (strcasecmp(GET_TEMPERATURE, receivedString) == 0){   // ist Eingabe GET_TEMPERATURE ?
        command_readTemperature = 1;                                //
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




/*
 * entscheidet welche Hterm ausgabe -> korrekt eingabe vom benutzer oder unbekannt
 */
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

        else if (command_setLed){                                       // soll geändertes Datum gelesen werden
            command_setLed = 0;

            //strcpy(transmittedString, "Welche LED's sollen angeschaltet werden? \r\n");
            PCF8574T_LEDS[0] = GPIO_setPinMode(LED3, HIGH);
            PCF8574T_LEDS[1] = GPIO_setPinMode(LED4, HIGH);

            i2c_master_send(SLAVE_PCF8574T, PCF8574T_LEDS, sizeof_t(PCF8574T_LEDS)-1);
            __delay_cycles(2000000);

        } // else if command_setLed

        else if (command_LedsOff){                                       // soll geändertes Datum gelesen werden
            command_LedsOff = 0;

            //strcpy(transmittedString, "Welche LED's sollen angeschaltet werden? \r\n");
            PCF8574T_LEDS[0] = GPIO_setPinMode(LEDS, LOW);
            i2c_master_send(SLAVE_PCF8574T, PCF8574T_LEDS, lenght);
            __delay_cycles(2000000);

        } // else if command_setLed

        else if(command_readTemperature){                                       // soll Kalender gelesen werden ?
            command_readTemperature = 0;

            i2c_master_receive(SLAVE_LM75, readBytes, lenArrayLM75);              // lese LM75, schreibe 2Bytes in array
            uint16_t temp = LM75_temperature(readBytes);            // wandle in rawTemperatur um

            if(command_setTempCelsius){
               sprintf(transmittedString, "%02d,%d °C \r\n",temp/10, temp%10);                              // Temperatur als String
            } else if (command_setTempFahrenheit){
               temp = (temp * 9/5) + 32;                                                                    // in Fahrenheit, z.B. (26 °C × 9/5) + 32 = 79,7 °F
               sprintf(transmittedString, "%02d,%d °F \r\n",temp/10, temp%10);                              // Temperatur als String
            }

        } // else if command_readTemperature

    } else {                                                                                                    // fall: falsche Konsoleneingabe
        uart_send("Eingabe: Unbekannt\r\n");
    } // if command_Konsoleneingabe

} // compareTransmittedParameter







#endif /* FUNCTIONS_FUNCTIONS_C_ */
