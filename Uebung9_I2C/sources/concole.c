/*
 * concole.c
 *
 *  Created on: 01.08.2019
 *      Author: danielschubert
 */

/********************************************
 * Includes
 ********************************************/
#include <stdint.h>

#include <msp430.h>
#include <string.h>
#include <strings.h>

#include "headers/console.h"
#include "headers/handler.h"
#include "headers/uart.h"




typedef struct
{
    uint8_t commands[MAX_COMMANDS][MAX_LENGTH_STRING];
    uint8_t arguments[MAX_ARGUMENTS][MAX_LENGTH_STRING];
    uint8_t options[MAX_OPTIONS][MAX_LENGTH_STRING];
} parameter_t;


parameter_t parameter =
        {
         commands: {"rtc", "led", "temperature", "adc"},
         arguments: {"change", "on", "off", "in", "out", "print", "help"},
         options: {"calender", "min", "sec", "hour","1", "2", "3", "4", "5", "6", "7", "8", "9",
                     "all", "celsius", "fahrenheit", "kelvin", "voltage"}
        };

eingabe_t eingabe;



/********************************************
 * Prototypes
 ********************************************/
uint8_t validateConsoleParameter(uint8_t);
uint8_t splitConsoleString(uint8_t*);



/********************************************
 * Variables
 ********************************************/
uint8_t countOfStrings = 0;


/********************************************
 * Functions
 ********************************************/

/*
 *
 */
uint8_t console_debug(void){
    countOfStrings = splitConsoleString(receivedString);
    return validateConsoleParameter(countOfStrings);
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
*   -> sind aufgeteilte strings in arrays vorhanden? j/n
*
*   return 1    -> error
*   return 0    -> no error
*/
uint8_t validateConsoleParameter(uint8_t countOfArrays)                             //
{
    uint8_t indexPtr = 0, indexArray = 0, indexEingabe = 0, err = 1;
    uint8_t* ptr[] = {parameter.commands, parameter.arguments, parameter.options};

    if (countOfArrays < 3){                                                         // wenn Teilstrings weniger 3 -> invalider String
        return err;
    }

    while(countOfArrays) {                                                          // solange Teilstrings übereinstimmen

        if(strcasecmp(ptr[indexPtr], eingabe.parameter[indexEingabe]) == 0){        // vergleicht Strings der erlaubten Commados mit Konsoleneingabe
            err = 0;                                                                // validee Command
            indexArray = 0;

            if(indexPtr<=1){                                                        // Array -> commands & arguments
                indexPtr++;                                                         // zeigt auf nächstes struct-element (array)
            } else {                                                                // Array -> parameter.options
                ptr[indexPtr] = parameter.options;                                  // zeigt auf Anfang des letzten Arrays
            }
            indexEingabe++;                                                         // aktuelle Stelle im Array
            countOfArrays--;                                                        // letztes struct-element erreicht?
        } else if(indexArray < MAX_LENGTH_STRING) {                                   // solange Arrayende nicht erreicht
            err = 1;
            indexArray++;
            ptr[indexPtr] += MAX_LENGTH_STRING;                                       // Pointer auf nächsten String
        } else if(indexArray == MAX_LENGTH_STRING && err){                            // wenn ende Array erreciht und kein parameter übereinstimmt,
            return err;                                                             //sofortiger abbruch und nicht auf weitere parameter überprüfen
        }
    } // while countOfArrays

    return err;
} // validateConsoleParameter







