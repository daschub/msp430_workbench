/*
 * handler.c
 *
 *  Created on: 08.08.2019
 *      Author: danielschubert
 */
/********************************************
 * Includes
 ********************************************/
#include <stdint.h>

#include <msp430.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "headers/handler.h"

#include "headers/uart.h"
#include "headers/rtc.h"
#include "headers/i2c.h"
#include "headers/console.h"
#include "headers/functions.h"


/********************************************
 * defines/typedefs
 ********************************************/
#define LM75_LENGHT             2
#define PCF8574T_LENGHT         1
#define LED_ARRAY              10


/********************************************
 * Variables
 ********************************************/
uint8_t PCF8574T_LEDS[LED_ARRAY];
uint8_t readBytes[LM75_LENGHT];
uint8_t readLeds[PCF8574T_LENGHT];
uint8_t writeBytes[PCF8574T_LENGHT];
uint8_t pinState = 0;
eingabe_t eingabe;

uint8_t *parameter1 = eingabe.parameter[0];
uint8_t *parameter2 = eingabe.parameter[1];
uint8_t *parameter3 = eingabe.parameter[2];


/********************************************
 * Functions
 ********************************************/


/*
 * TODO um @commandHandler zu verschlanken
 */
void command_debug(void)
{

}



/*
 * behandelt  validierte Konsoleneingabe
 * und übergibt sie je nach ersten Parameter an Handlerfunktionen
 *
*/
void commandHandler(void)
{
    uint8_t* commandArray = 0;
    uint8_t leds = 0;

    if (strcasecmp("temperature", parameter1) == 0){
        commandArray = temperatureHandler();                // gibt temperatur + einheit zurück

        uart_send(commandArray);
    } else if (strcasecmp("adc", parameter1) == 0){
        adcHandler(parameter2);
    } else if (strcasecmp("rtc", parameter1) == 0){
        rtcHandler(*parameter2);
    } else if (strcasecmp("led", parameter1) == 0){
        leds = ledHandler();                                // welche leds schalten?
        i2c_master_send(SLAVE_PCF8574T, leds, MAX_LENG);
        if (command_temperature){
            command_temperature = 0;
        } else {
            uart_send("LEDs geschaltet\r\n");               // sende welche leds geschaltet  TODO welche leds geschaltet
        }
    } else {
        uart_send("für diesen Paramter ist noch kein handler vorhanden\r\n");
    }


} // commandHandler



/*
 * liefert die Temperatur mit entsprechender Einheit zurück
 */
uint8_t* temperatureHandler(void)
{
    uint8_t stringTemperature[10];
    uint16_t temp = 0;

    if (strcasecmp("print", parameter2) == 0){
        i2c_master_receive(SLAVE_LM75, readBytes, LM75_LENGHT);                     // lese LM75, schreibe 2Bytes in array
        temp = LM75_temperature(readBytes);                                         // wandle in rawTemperatur um

        if (strcasecmp("celsius", parameter3) == 0){
            sprintf(stringTemperature, "%02d,%d °C \r\n", temp/10, temp%10);            // Temperatur als String
        } else if (strcasecmp("fahrenheit", parameter3) == 0){
            temp = (temp * 9/5) + 320;                                                  // in Fahrenheit, z.B. (26 °C × 9/5) + 32 = 79,7 °F
            sprintf(stringTemperature, "%02d,%d °F \r\n", temp/10, temp%10);            // Temperatur als String
        } else if (strcasecmp("kelvin", parameter3) == 0){
            temp *= 10;
            temp += 27315;                                                              // in Kelvin +273,15
            sprintf(stringTemperature, "%02d,%d K \r\n", temp/100, temp%100);           // Temperatur als String
        } // if "einheiten"
    } // if "print"
    else if (strcasecmp("track", parameter2) == 0){
        if (strcasecmp("on", parameter3) == 0){
            command_temperatureTrack = 1;
            uart_send("Balken-Leds an\r\n");
        } else if (strcasecmp("off", parameter3) == 0){
            command_temperatureTrack = 0;
            uart_send("Balken-Leds aus\r\n");
        }
    } // temperatureTrack
    else {
    uart_send("dieses commando ist für temperatur nicht zulässig\r\n");
    }

    return stringTemperature;
}



/*
 * TODO
 */
void adcHandler(uint8_t* str)
{
    __no_operation();
}



/*
 * TODO
 */
void rtcHandler(uint8_t* str)
{
    snprintf(transmittedString, "%02d.%02d.%d, %02d:%02d:%02d Uhr \r\n", calender.day, calender.month,
                calender.year, calender.hour, calender.minute, calender.second);

    uart_send("Gebe Datum im Format DD.MM.YYYY,hh:mm:ss ein\r\n");
    validateCalender();
}



/*
 * bestimmt welche leds  an/aus und übergibt sie an i2c_master_send()
 */
uint8_t ledHandler(void)
{
    uint8_t mode = 0;                                                   // welcher pegel soll anstehen?
    uint8_t i = 0;                                                      // laufvariable array
    uint8_t leds = 0;

    if (strcasecmp("on", parameter2) == 0){
        mode = HIGH;
    } else if (strcasecmp("off", parameter2) == 0){
        mode = LOW;
    }
                                        // TODO i2c_master_read PCA7485 -> datasheet p.9 input mode
    //i2c_master_receive(SLAVE_PCF8574T, readLeds, PCF8574T_LENGHT);

    leds = addLeds(parameter3);       // 2. parameter  readleds              // welche leds ein/ausgeschaltet werden sollen
    leds = GPIO_setPinMode(leds, mode);

    for (i = 10; i >= 2; i--){                                          // lösche gesetzte leds, falls nächstete eingabe kürzer
        *parameter3 = '\0';
        parameter3 += MAX_LENGTH_STRING;
    }
    parameter3 = eingabe.parameter[2];

    return leds;
} // ledHandler







