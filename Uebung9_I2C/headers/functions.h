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

#define SET_RTC         "SET RTC\r\n"
#define GET_RTC         "GET RTC\r\n"
#define SET_LED         "SET LED\r\n"
#define LEDS_OFF        "LEDS OFF\r\n"
#define SET_TEMP_C      "SET TEMP_C\r\n"
#define SET_TEMP_F      "SET TEMP_F\r\n"
#define GET_TEMPERATURE "GET TEMP\r\n"




/*
 * tauscht Werte zweier Zahlen
 */
#define SWAP(a, b)  {                   \
                        a ^= b;         \
                        b ^= a;         \
                        a ^= b;         \
                    }


/***********************************************
 * Prototypes
 ***********************************************/
void compareReceivedParameter(void);
void compareTransmittedParameter(void);
uint16_t sizeof_t(uint8_t*);


#endif /* FUNCTIONS_FUNCTIONS_H_ */
