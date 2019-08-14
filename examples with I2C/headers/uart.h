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
uint8_t command_receivedString;                            // ist True sobald kompletter String erhalten wurde
uint8_t command_transmitString;                            // ist True sobald kompletter String gesendet wurde
uint8_t command_temperatureChange;
uint8_t command_temperature;

/*****************************************
 * Prototypes
 *****************************************/

void uart_init(void);
void uart_send(uint8_t*);
void uart_receive(uint8_t *str);

void start_transmit(void);
void start_receive(void);
void stop_transmit(void);

#endif /* UART_UART_H_ */
