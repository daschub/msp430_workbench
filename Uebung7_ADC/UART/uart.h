/*
 * uart.h
 *
 *  Created on: 20.05.2019
 *      Author: danielschubert
 */

#ifndef UART_UART_H_
#define UART_UART_H_

uint8_t receivedString[12];                              // Eingabe-String
uint8_t transmittedString[21];                           // Ausgabe-String

uint16_t command_receivedString;                         // ist True sobald kompletter String erhalten wurde
uint16_t command_transmitString;                         // ist True sobald kompletter String gesendet wurde

void uart_init(void);
void start_transmit(void);
void stop_transmit(void);

#endif /* UART_UART_H_ */
