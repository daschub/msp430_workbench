/*
 * uart.c
 *
 *  Created on: 09.05.2019
 *      Author: danielschubert
 */

#ifndef UART_UART_C_
#define UART_UART_C_

#include <stdint.h>

#include <msp430.h>
#include <strings.h>
#include "uart.h"


uint16_t indexReceiveString = 0;                         // Indexzahl für Eingabe-String
uint16_t indexTransmitString = 1;                        // Indexzahl für Ausgabe-String


/**
 * Setup UART für 4MHz
 */
void uart_init(void){
    UCA1CTL0 = 0x00;                                            // Parität deaktiviert
    UCA1CTL1 = 0x01 ;                                           // um UART-Register zu konfigurieren, UCSWRST = 1
    P4SEL |= BIT4 + BIT5;                                       // P4.4 UART TX (<-- MCU), P4.5 UART RX (--> MCU)

    UCA1CTL1 |= 0x80;                                           // source -> SMCLK
    UCA1BR0 = 26;                                               // 4MHz 9600 Baudrate
    UCA1BR1 = 0;                                                // UCOS16 UCBR Dez 26
    UCA1MCTL = 0x11;                                            // UCOS16 = 1; UCBRF -> modulation stage

    UCA1CTL1 &= ~0x01;                                          // USCI Modul ist aktiviert und Transmitter+Receiver sind bereit; UCSWRST = 0
    UCA1IE = 0x01;                                              // aktiviere RX interrupt
    UCA1IFG = 0x00;                                             // wird gesetzt sobald kompletter Character erhalten/gesendet
    command_receivedString = 0;                                 // ist True sobald kompletter String erhalten wurde
    command_transmitString = 0;                                // ist True sobald kompletter String gesendet wurde
}


void start_transmit(void){
    UCA1IE |= 0x02;                                             // aktiviere Transmit interrupt
    UCA1TXBUF = transmittedString[0];                           // aktiviere Transmit Flag
}

void stop_transmit(void){
    UCA1IE &= ~0x02;                                            // deaktiviere Transmit interrupt
}
/**
 * Isr erhaltene Character
 * werden in receiveString gespeichert
 */
#pragma vector=USCI_A1_VECTOR
__interrupt void isr_uartA1(void)
{
    if (UCA1IFG & UCRXIFG){                                     // Fall: receive
        receivedString[indexReceiveString] = UCA1RXBUF;         // lese Character
        indexReceiveString++;
        if(UCA1RXBUF == '\n'){                                  // ist Ende des Strings erreicht?
            receivedString[indexReceiveString] = '\0';          // um Stringende zu erkennen
            indexReceiveString = 0;
            command_receivedString = 1;                         // damit Umwandlung gestartret wird
        } // if
        UCA1IFG &= ~UCRXIFG;                                    // lösche Receive Flag
    } // if receive


     if (UCA1IE & UCTXIE){                                      // Fall: transmit
        UCA1TXBUF = transmittedString[indexTransmitString];
        indexTransmitString++;
        if(UCA1TXBUF == '\n'){                                  // ist Ende des Strings erreicht?
            transmittedString[indexTransmitString] = '\0';      // um Stringende zu erkennen
            indexTransmitString = 1;
            stop_transmit();
        } // if ende string
     } // if transmit

} // isr_uartA1


#endif /* UART_UART_C_ */
