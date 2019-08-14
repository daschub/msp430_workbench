/*
 * rtc.c
 *
 *  Created on: 27.05.2019
 *      Author: danielschubert
 */

#ifndef RTC_RTC_C_
#define RTC_RTC_C_


/**********************************************
 * Includes
 **********************************************/
#include <stdint.h>

#include <msp430.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "headers/rtc.h"
#include "headers/uart.h"
//#include "headers/functions.h"
#include "headers/timer.h"



/**********************************************
 * defines
 *********************************************/
#define SECONDS_PER_YEAR        31536000
#define SECONDS_PER_MONTH       2628000
#define SECONDS_PER_DAY         86400
#define SECONDS_PER_HOUR        3600
#define SECONDS_PER_MINUTE      60
#define LEAP_YEAR               1


/*********************************************
 * Typedefs
 ********************************************/
typedef enum
{
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OKTOBER,
    NOVEMBER,
    DECEMBER
} year_t;




typedef struct
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} time_t;


/*************************************
 * Prototypes
 ************************************/
void getTime(void);
void validateDate(void);
void validateTime(void);
int validateLeapYear(void);
void changeCalender(void);
void timePassed(void);
uint8_t *convertIntToString(uint32_t intValue, uint8_t *array);
//void structToString(calender_t calender);
void printString(uint8_t string);
void validateStringFormat(uint8_t *transmittedString);
void splitStringCalender(uint8_t *transmittedString);



/*****************************************
 * Functions
 *****************************************/


/*
 * Setup für RTC
 */
void rtc_init(void)
{
    RTCCTL0 = 0x50;                     // RTCTEVIE; RTCRDYIE Interrupt um RTC-Register auszulesen
    RTCCTL1 = 0x20;                     // BCD; RTCMODE = 1 KalenderModus, inkludiert schaltjahr-algth (ist genau -> 1901-2099), welcher durch 4 gerade-teilbar ist
                                        //
    //RTCCTL2 = 0x3F;                     // TODO
}



/*
 * setzt aktuelle Zeit auf den  Di 01.01.2019; 00:00:00 Uhr
 */
void calender_init(void)
{
    //
    RTCDAY = 0x02;                      // Dienstag
    RTCYEAR = 2019;                     // 2019  Bit 7-4 -> Dekade; Bit 3-0 -> Jahr
    RTCMON = 0x01;                      // 01
    RTCDAY = 0x01;                      // 01
    RTCHOUR = 0x06;                     // 0 Stunden
    RTCMIN = 0x04;                      // 0 Minuten
    RTCSEC = 0x03;                      // 0 Sekunden
}



/*
 * gibt aktuelles Datum zurück
 */
calender_t getCalender(void)
{
    calender_t calender = {RTCYEAR, RTCMON,RTCDAY, RTCHOUR, RTCMIN, RTCSEC};
    return calender;
} // get_calender



/*
 * @calender_t, Variable vom Typ Struktur, die das aktuelle Datum verändert
*/
void changeCalender(void)
{
    RTCYEAR = calender.year;                          // Jahr
    RTCMON = calender.month;                          // Monat
    RTCDAY = calender.day;                            // Tag
    RTCHOUR = calender.hour;                          // Stunden
    RTCMIN = calender.minute;                         // Minuten
    RTCSEC = calender.second;                         // Sekunden
}



/*
 * gibt aktuelle Zeit zurück
 */
void getTime(void)
{
    calender_t time = {RTCHOUR, RTCMIN, RTCSEC};
} // get_time



/*
 * prüft ob aktuell ein Schaltjahr vorliegt
 *
 * Jahr modulo 400  ->  Schaltjahr
 * Jahr modulo 100  ->  kein Schaltjahr
 * Jahr modulo   4  ->  Schaltjahr
 *
 */
int validateLeapYear(void)
{
    if (RTCYEAR % 400 == 0)
        return LEAP_YEAR;
    else if (RTCYEAR % 100 == 0)
        return 0;
    else if (RTCYEAR % 4 == 0)
        return LEAP_YEAR;
    else
        return 0;
}



/*
 * prüft ob eingegebenes Datum für Jahr, Monat und Tag sinnvoll ist.                        // TODO angeben ab welchem Jahr gestartet wird
 * und auf Schaltjahr
 */
void validateDate(void)
{

    uint16_t leapYear = validateLeapYear();

    if (calender.month < 13){                                                                       // Fall: kein Schaltjahr und Monatseingabe < 12

        switch(calender.month){
           case MARCH: case APRIL: case JUNE: case SEPTEMBER: case NOVEMBER:                        // gibt es angegebenen Tag im diesem Monat ?
               if (calender.day > 30){
                   command_checkString = 0;
               } break;
           case FEBRUARY:                                                                           // gibt es angegebenen Tag im diesem Monat ?
                if (!leapYear && calender.day > 28){
                    command_checkString = 0;
                } else if (leapYear && calender.day > 29){
                    command_checkString = 0;
                } break;
            default:                                                                                // gibt es angegebenen Tag im diesem Monat ?
                if (calender.day > 31){
                    command_checkString = 0;
                }break;
        } // switch
    } else {
        command_checkString = 0;
    } // if calender.month
} // validateDate



/*
 * prüft ob eingegebenes Zeit für Stunden, Minuten und Sekunden sinnvoll ist.
 */                                                                                         //TODO
void validateTime(void)
{
    if (calender.hour > 24)                                                                   //
        command_checkString = 0;
    else if (calender.minute > 60 )
        command_checkString = 0;
    else if (calender.second > 60)
        command_checkString =  0;
} // validateDate



/*
 * validiert das vom Benutzer übergebende Datum @calender_t
 */
void validateCalender(void)
{
    validateStringFormat(receivedString);                               // ist eingabe im richtigen datumsformat
    if (command_checkString){
        splitStringCalender(receivedString);                                    // funktion, die die jeweiligen datumsparamter in die struktur schreibt
        changeCalender();                                               // setzte neues datum

        validateDate();
    } // if

    if (command_checkString){
        validateTime();
    } // if

} // validateCalender


/**
 * @intValue übergebe gewünschten Int-Wert, der zu einen String gewandelt wird
 * @decimalValue gibt an, wie viele Nachkommastellen angegeben werden

 *
 * gegebene Zahl durch Modulo, dann durch entsprechenden Zählerfaktor teilen
 * dies ergibt die einzelne Ziffer.
 * dann mit z.b. switch case mit ASCII 31 addieren und in array speichern
 *
 * beispiel:  zahl 8436

        8436 % 10000  = 8436  / 1000  = 8
        8436 %  1000  =  436  /  100  = 4
        8436 %   100  =   36  /   10  = 3
        8436 %    10  =    6  /    1  = 6
 *
 */
uint8_t *convertIntToString(uint32_t intValue, uint8_t *array)
{
    uint16_t i;
    uint32_t count = 1,  temp = intValue , temp2 = intValue;

    while (temp > 10){                                                          // Anzahl der Dezimalstellen, (teile durch Zehn)
        temp /= 10;
        count++;
    } // while

    temp = pow(10,count);                                                       // temp ist Modulofaktor  ( 10^maxDezimalstelle)      // TODO ohne Quadratfunktion lösbar

    while (count){                                                              // iteriere über Zahl
        temp2 = intValue % temp;
        temp /= 10;
        array[i] = temp2 / temp;                                                // schreibe Ziffern in Array
        count--;
    } // for
    return array;
} // convert Int to String



/*
 * prüft ob erhaltenrer String richtiges Format hat (XX.XX.XXXX,XX:XX:XX)
 *
 * an 3. und 6. Stelle wird ein Punkt erwaqrtet
 * an 11. ein Komma
 * an 14. und 17. ein Doppelpunkt
 * ansonsten nur Ziffern
 */
void validateStringFormat(uint8_t *receivedString)
{
    uint8_t count = 1;
    //if (strlen(receivedString) == 22){
    while (*receivedString){

        switch (count)
        {
           case 3: case 6:                                              // steht '.' an der richtigen Stelle?
               if (*receivedString != '.'){
                   command_checkString = 0;
               } break;
           case 11:
              if (*receivedString != ','){                              // ist Leerstelle an der richtigen Stelle?
                  command_checkString = 0;
              } break;
           case 14: case 17:
               if (*receivedString != ':'){                             // steht ':' an der richtigen Stelle?
                   command_checkString = 0;
               } break;
           case 20: case 21:
                 break;
           default:
               if (*receivedString < '0' || *receivedString > '9'
                       || *receivedString == ' '){                      // ist gesendetes Zeichen eine Zahl oder Leerstelle ?
                   command_checkString = 0;
               }
        } // switch
        if (command_checkString){
            count++;
            *receivedString++;
        } else {
            *receivedString = '\0';
        } // if command_checkString
    } // while
} // validateStringFormat



/*
 * teilt String und schreibt sie in die Strukur @calender_t
 */
void splitStringCalender(uint8_t *receivedString)
{
    uint8_t delimiter[] = ".,:";
    uint8_t *ptr;
    // initialisieren und ersten Abschnitt erstellen
    ptr = strtok(receivedString, delimiter);

    while(ptr) {
        calender.day = atoi(ptr);                                   // schreibe Token in Tag
        ptr = strtok(NULL, delimiter);                              // naechsten Abschnitt erstellen
        calender.month = atoi(ptr);                                 // analog wie oben
        ptr = strtok(NULL, delimiter);
        calender.year = atoi(ptr);
        ptr = strtok(NULL, delimiter);
        calender.hour = atoi(ptr);
        ptr = strtok(NULL, delimiter);
        calender.minute = atoi(ptr);
        ptr = strtok(NULL, delimiter);
        calender.second = atoi(ptr);
        ptr = strtok(NULL, delimiter);
    } // while
} // splitString



// RTC ready Flag , einfacher Weg um EchtZeitUhr auszulesen
// keepout window -128/32768s vor und nach update, während keepout wird RTCRDY-Bit zurückgesetzt
#pragma vector=RTC_VECTOR
__interrupt void isr_rtc(void)
{
    /*
    RTCCTL1 &= ~RTCHOLD;

    switch (__even_in_range(RTCIV,16)){
        case 4:
            RTCCTL1 |= RTCHOLD;                                                                     // TODO
            start_timer();
            __enable_interrupt();
            timer_delay(4);                                             // 2 * ~315ms = 630ms
            break;        //RTCEVIFG Interrupts every minute
    }
    */

    RTCCTL0 &= ~0x07;                                               // lösche IFG's
} // isr_rtc



/*
 * Zeit, die vergangen ist, seit letzter Änderung
 *
void time_passed(void)          TODO
{
    calender.year = RTCYEAR * SECONDS_PER_YEAR;                   // sekunden im Jahr, 365 * 24 * 60 * 60
    calender.month = RTCMON * SECONDS_PER_MONTH;                  // einfachhaltshalber erstaml Jahr / 12
    calender.day = RTCDAY * SECONDS_PER_DAY;                      // sekunden pro Tag 24 * 60 * 60
    calender.hour = RTCHOUR * SECONDS_PER_HOUR;
    calender.minute = RTCMIN * SECONDS_PER_MINUTE;
    calender.second = RTCSEC;
} // time_passed
*/



#endif /* RTC_RTC_C_ */
