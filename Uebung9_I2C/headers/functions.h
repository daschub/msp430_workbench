/*
 * functions.h
 *
 *  Created on: 20.05.2019
 *      Author: danielschubert
 */
#ifndef FUNCTIONS_FUNCTIONS_H_
#define FUNCTIONS_FUNCTIONS_H_


/***********************************************
 * Variables
 ***********************************************/
/*
#define SET_RTC         "SET RTC\r\n"
#define GET_RTC         "GET RTC\r\n"
*/
#define HIGH                    1
#define LOW                     0
#define MAX_LENG                1

/*
 * tauscht Werte zweier Zahlen
 */
#define SWAP(a, b)  {                   \
                        a ^= b;         \
                        b ^= a;         \
                        a ^= b;         \
                    }

typedef struct
{
    uint16_t value;
    uint8_t unit[15];
    uint8_t ledState;
} temperature_t;


/***********************************************
 * Prototypes
 ***********************************************/
void compareReceivedParameter(void);
void compareTransmittedParameter(void);
uint16_t sizeof_t(uint8_t*);
uint8_t addLeds(uint8_t*);
uint8_t GPIO_setPinMode(uint8_t, uint8_t);
uint16_t LM75_temperature(uint8_t*);
void ledState(void);
uint8_t temperatureChange(uint16_t);
uint16_t getTemperature(void);
void temperatureState(void);

#endif /* FUNCTIONS_FUNCTIONS_H_ */
