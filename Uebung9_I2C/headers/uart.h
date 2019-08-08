/*
 * uart.h
 *
 *  Created on: 20.05.2019
 *      Author: danielschubert
 */

#ifndef UART_UART_H_
#define UART_UART_H_

#define MAX_LENGHT_RECEIVE      50
#define MAX_LENGHT_TRANSMIT     55

/*****************************************
 * Variables
 *****************************************/

uint8_t receivedString[MAX_LENGHT_RECEIVE];                 // Eingabe-String
uint8_t transmittedString[MAX_LENGHT_TRANSMIT];             // Ausgabe-String
uint16_t command_receivedString;                            // ist True sobald kompletter String erhalten wurde
uint16_t command_transmitString;                            // ist True sobald kompletter String gesendet wurde
uint16_t command_setLed;
uint16_t command_LedsOff;
uint16_t command_readTemperature;                           //



/*****************************************
 * Prototypes
 *****************************************/

void uart_init(void);
void uart_send(uint8_t*);
void start_transmit(void);
void start_receive(void);
void stop_transmit(void);

#endif /* UART_UART_H_ */
