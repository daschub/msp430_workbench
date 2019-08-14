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
#include "headers/i2c.h"
#include "headers/console.h"
#include "headers/handler.h"

/***********************************************
 * Variables
 ***********************************************/
const uint8_t LED1 = (BIT6);
const uint8_t LED2 = (BIT5);
const uint8_t LED3 = (BIT4);
const uint8_t LED4 = (BIT0);
const uint8_t LED5 = (BIT1);
const uint8_t LED6 = (BIT7);
const uint8_t LED7 = (BIT2);
const uint8_t LED8 = (BIT3);
const uint8_t LED_ALL = (LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8);

eingabe_t eingabe;

uint16_t lastTemp = 0;
uint8_t change = 0;
uint8_t temp_pins =0;
uint8_t readTemperature[2];
temperature_t temperature1 = { 270, "Celsius", 3 };

/***********************************************
 * Prototypes
 ***********************************************/
void temperatureScale(uint16_t);


/***********************************************
 * Functions
 ***********************************************/



/*
 * gibt l�nge des des �bergebenden arrays @para zur�ck
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
    if (command_temperatureTrack)
        temp_pins = 0xFF;

    if(mode == LOW){
        temp_pins |= pins;
    } else if (mode == HIGH) {
        temp_pins &= ~pins;
    }
    return temp_pins;
}



/*
 * addiere Leds, f�r funktion gpio_setpinmode
 */
uint8_t addLeds(uint8_t *ptr)   // TODO , uint8_t *readLeds zweiter parameter -> aktuelle leds
{

    uint8_t pinState = 0;

    while(*ptr){                                           // addiere leds so oft bis keine zahl mehr kommt
        switch(*ptr){
            case '1':
                pinState |= LED1;
                break;
            case '2':
                pinState |= LED2;
                break;
            case '3':
                pinState |= LED3;
                break;
            case '4':
                pinState |= LED4;
                break;
            case '5':
                pinState |= LED5;
                break;
            case '6':
                pinState |= LED6;
                break;
            case '7':
                pinState |= LED7;
                break;
            case '8':
                pinState |= LED8;
                break;
            case 'a':
            default:                                    // alle leds
                pinState = 0xFF;
        }
        ptr += 20;                                      // TODO
    } // while;
    return pinState;
}



/*
 *  liefert die Temperatur �ber den LM75 (1bit = 0,5�)
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



/*
 *
 */
uint8_t temperatureChange(uint16_t lastTemp){

    uint8_t change = 0;

    if (temperature1.value > lastTemp){
        if (temperature1.ledState <= 1)
            temperature1.ledState = 9;
        temperature1.ledState -= 1;                                  // Led(i+1) on
        change = 1;
    } else if (temperature1.value < lastTemp){
        if (temperature1.ledState >= 8)
            temperature1.ledState = 0;
        temperature1.ledState += 1;                                  // Led(i-1) on
        change = 1;
    } else {
        change = 0;
    }
    temperature1.value = lastTemp;

    return change;
}



/*
 * vergleiche temperatur wert in celsius (mit 10 multipliziert)  @LM75_temperature
 *
 */
void temperatureScale(uint16_t lastTemp){

    if (lastTemp <= 250)                                     // unter 25�
        temperature1.ledState = 1;
    else if (lastTemp == 255)                                   // 25,5�
        temperature1.ledState = 2;
    else if (lastTemp == 260)                                    // 26,0�
        temperature1.ledState = 3;
    else if (lastTemp == 265)                                   // 26,5�
        temperature1.ledState = 4;
    else if (lastTemp >= 270)                                // �ber 26,5�
        temperature1.ledState = 5;

}





/*
 *   liefert aktuelle temperatur ohne Kommastelle
 */
uint16_t getTemperature(void){

    uint16_t temp = 0;
    i2c_master_receive(SLAVE_LM75, readTemperature, 2);                     // lese LM75, schreibe 2Bytes in array
    temp = LM75_temperature(readTemperature);                               // wandle in rawTemperatur um

    return temp;
}



/*
 *
 */
void ledState(void)
{
    sprintf(receivedString, "led on %d", temperature1.ledState);
    command_receivedString = 1;
    command_temperature = 1;
    uart_receive("temperature print celsius");
}



/*
 *
 */
void temperatureState(void)
{
    lastTemp = getTemperature();                                //
    /*change = temperatureChange(lastTemp);                     // anstatt temperaturskala wechselnde led pro temperaturschwankung
    if (change){
        change = 0;
        ledState();
    }*/

    temperatureScale(lastTemp);                                // Temperaturskala -> welche led an
    ledState();
}


#endif /* FUNCTIONS_FUNCTIONS_C_ */

/*
 * alte funktionen
 */

/*
 * vergleicht konsoleneingabe vom benutzer und �bergibt den parameter der func compareTransmittedParameter
 *
void compareReceivedParameter(void)                                                                     //TODO
{
    command_konsolenEingabe = 1;

    if (strcasecmp(GET_RTC, receivedString) == 0){                  // ist Eingabe GET_RTC ?
        calender = getCalender();                                   //
    } else if (strcasecmp(SET_RTC, receivedString) == 0){           // ist Eingabe SET_RTC ?
        command_transmitConfig = 1;                               //
    } else if (command_checkString){                                // ist die Eingabe ein neues Datum?
        validateCalender();                                         // pr�fe auf sinnvolle Datumseingabe
        command_transmitConfig = 1;
        command_readCalender = 1;
        if (command_checkString){                               // fall richtige datumseingabe
            command_checkString = 0;
        } else {
            command_konsolenEingabe = 0;
        } // if command_checkString

    } else {
        command_konsolenEingabe = 0;
        command_transmitString = 0;                             // TODO eingabe behandlung sobald array�berlauf oder genrell unerwarte eingabe

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

        else if (command_transmitConfig){                               // soll ge�ndertes Datum gelesen werden
            command_transmitConfig = 0;

            uart_send("Gebe Datum im Format DD.MM.YYYY,hh:mm:ss ein\r\n");
            command_checkString = 1;

        } // else if command_transmitConfig


*/
