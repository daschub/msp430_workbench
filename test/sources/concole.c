/*
 * concole.c
 *
 *  Created on: 01.08.2019
 *      Author: danielschubert
 */

/********************************************
 * Includes
 ********************************************/
#include <msp430.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "headers/console.h"

#define HIGH                1
#define LOW                 0


/********************************************
 * Variables
 ********************************************/
const uint8_t LED1 = BIT6;
const uint8_t LED2 = BIT5;
const uint8_t LED3 = BIT4;
const uint8_t LED4 = BIT0;
const uint8_t LED5 = BIT1;
const uint8_t LED6 = BIT7;
const uint8_t LED7 = BIT2;
const uint8_t LED8 = BIT3;
const uint8_t LEDS = (LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8);


parameter_t parameter =
        {
         commands: {"rtc", "led", "temperatur", "adc"},
         arguments: {"change", "on", "off", "in", "out", "print", "help" },
         options: {"calender", "min", "sec", "hour","1", "2", "3", "4", "5", "6", "7", "celsius", "fahrenheit", "kelvin" }   // TODO zahlen anders behandeln
        };

eingabe_t eingabe;
uint8_t temp_pins = 0xFF;

uint8_t GPIO_setPinMode(uint8_t, uint8_t);

/********************************************
 * Functions
 ********************************************/

/*
 * gibt länge des des übergebenden arrays @para zurück
 */
uint16_t sizeof_t(uint8_t* array)
{
    return sizeof(array)/sizeof(*array);
}



/*
 * teilt den String @para in Teilstrings, schreibt sie in eine Strukur  @eingabe_t und gibt die Anzahl an teilstrings zurück
 */
uint8_t splitConsoleString(uint8_t *splitString)
{
    uint8_t delimiter[] = " ";
    uint8_t *ptr;
    uint8_t i = 0;                                                              // laufvariable

    ptr = strtok(splitString, delimiter);                                       // initialisieren und ersten Abschnitt erstellen

    while(ptr) {
        strcpy(eingabe.parameter[i], ptr);                                      // schreibe Token in Tag
        ptr = strtok(NULL, delimiter);                                          // naechsten Abschnitt erstellen
        i++;
    } // while
    return i;                                                                   // anzahl an tEILSTRINGS
} // splitConsoleString



/*prüfe auf valide eingabe
*-> sind aufgeteilte strings in arrays vorhanden? j/n
* iteriere über struct von arrays
* -> pointer auf nächstes element = + sizeof erstes element (size_t arrayCommands)
* -> pointer drittes elemnt wieder + size_t arrayOptions
*
*/
uint8_t validateConsoleParameter(uint8_t countOfStrings)
{
    uint8_t i = 0, j = 0, k = 0, err = 1;
    uint8_t* ptr[] = {parameter.commands, parameter.arguments, parameter.options};
    uint8_t arrayLength = MAXLENGTH_ARRAY;

    while(countOfStrings) {                                                     // solange teilstrings übereinstimmen
        if(strcasecmp(ptr[i], eingabe.parameter[k]) == 0){                          // vergleiche string mit pointer auf array
            err = 0;                                                                // wenn übereinstimmt erhöhe pointer um arraygröße des letzten also

            if(i<=1)                                                            // nächstes struct element und iteriere wieder über elmente ,
                i++;                                                            // falls wieder treffer in array , erhöhe wiederrum pointer auf nächstes struct elemtne
            else
                ptr[i] = parameter.options;                                     //  ptr wieder an anfang des arrays

            k++;
            countOfStrings--;                                                   //


        } else if(j == arrayLength && err){                                     // wenn kein parameter übereinstimmt, sofortiger abbruch und nicht weitere parameter überprüfen
            break;
        } else if(err == 0){                                                    // err = 1 , prüfe nächsten parameter auf korrektheit
            err = 1;
        } else {
            ptr[i] += arrayLength;                                              // pointer auf nächstes arrayelement
            j++;
        }
    }
    return err;
} // validateConsoleParameter



/*
 * falls valider consolencommand , übergebe an module @handler_
 * wenn erster Teilstring(command) == led , dann mehrere options in Folge kommen-> led 1 3 4 on,
 *
*/
uint8_t commandHandler(uint8_t* str)
{
    uint8_t leds = 0;

    if (strcasecmp("temperature", str) == 0){
        temperaturHandler(*str);
    } else if (strcasecmp("adc", str) == 0){
        adcHandler(*str);
    } else if (strcasecmp("rtc", str) == 0){
        rtcHandler(*str);
    } else if (strcasecmp("led", str) == 0){
        leds = ledHandler();
    } /*else {
        uart_ send("für diesen Paramter ist noch kein handler vorhanden");
    }*/
} // commandHandler



void temperaturHandler(uint8_t* str)
{
    __no_operation();
}

void adcHandler(uint8_t* str)
{
    __no_operation();
}


void rtcHandler(uint8_t* str)
{
    __no_operation();
}



/*
 * bestimmt welche leds  an/aus und übergibt sie an i2c_master_send()
 */
uint8_t ledHandler(void)
{
    uint8_t *ptr = eingabe.parameter[1];
    uint8_t mode = 0;
    uint8_t leds = 0;

    if (strcasecmp("on", ptr) == 0){
            mode = HIGH;
    } else if (strcasecmp("off", ptr) == 0){
        mode = LOW;
    }

    *ptr = eingabe.parameter[2];
    leds = addLeds(leds, *ptr);                             // welche leds ein/ausgeschaltet werden sollen

    return GPIO_setPinMode(leds, mode);                     // setzt Bits
} // ledHandler



/*
 * addiere Leds, für funktion gpio_setpinmode
 */
uint8_t addLeds(uint8_t leds, uint8_t *ptr)
{
    while(isdigit(*ptr)){                           // prüfe ob nächster teilstring argument ist, ansonsten addiere leds so oft bis keine zahl mehr kommt
                                                    // zb. LED 1 3 4 5 3  on   <-- setzte 5 leds und danach argumentHandler();
        switch(*ptr){
            case 1:
                leds |= LED1;
            case 2:
                leds |= LED2;
            case 3:
                leds |= LED3;
            case 4:
                leds |= LED4;
            case 5:
                leds |= LED5;
            case 6:
                leds |= LED6;
            case 7:
                leds |= LED7;
            case 8:
                leds |= LED8;
        }
        ptr += 20;                                  // TODO
    } // while
    return leds;
}



/*
 * setzt Ledzustand
 * @pins die zu setztenden LEDs
 * @mode gibt an ob HIGH oder LOW
 */
uint8_t GPIO_setPinMode(uint8_t pins, uint8_t mode)
{

    if(mode == HIGH){
        temp_pins &= ~pins;
    } else if (mode == LOW) {
        temp_pins |= pins;
    }
    return temp_pins;
}


















