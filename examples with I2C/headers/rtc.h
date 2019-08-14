/*
 * rtc.h
 *
 *  Created on: 27.05.2019
 *      Author: danielschubert
 */

#ifndef RTC_RTC_H_
#define RTC_RTC_H_


typedef struct
{
    uint16_t year;
    uint16_t month;
    uint16_t day;
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
} calender_t;

calender_t calender;


/***********************************************
 * Variables
 ***********************************************/
uint16_t command_checkString;
uint16_t command_konsolenEingabe;                   // ist True sobald korrekte Eingabe erhalten wurde
uint16_t command_readCalender;
uint8_t calenderString[30];
uint16_t command_transmitConfig;



/***********************************************
 * Prototypes
 ***********************************************/
void rtc_init(void);
void calender_init(void);
calender_t getCalender(void);
void validateCalender(void);


/*
#define X_FIELDS \
    X(field1) \
    X(field2) \
    X(field3) \
    X(field4)


typedef struct
{
#define X(field1) uint16_t year;
        X(field2) uint16_t month;
        X(field3) uint16_t day;
        X(field4) uint16_t hour;
        X(field5) uint16_t minute;
        X(field6) uint16_t second;
    X_FIELDS
#undef X
} calender_t;


char *structToString(calender_t *myCalender)
{
#define X(name) \
        strcat(calenderString, myCalender->name);           //TODO eigene printf
X_FIELDS
#undef X
return calenderString;
}
*/

#endif /* RTC_RTC_H_ */
