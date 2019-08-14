/*
 * main.h
 *
 *  Created on: 17.06.2019
 *      Author: danielschubert
 */

#include <stdint.h>

#include <msp430.h> 
#include <stdio.h>
#include "headers/clock.h"
#include "headers/timer.h"
#include "headers/i2c.h"
#include "headers/uart.h"
#include "headers/functions.h"
#include "headers/console.h"
#include "headers/handler.h"
#include "headers/timer.h"
#include "headers/rtc.h"

/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	xt2_init();
	timer1_init();
	i2c_init();
	uart_init();
	rtc_init();
	calender_init();

	start_timer1();

    uint8_t validate = 1;

	__enable_interrupt();


	while(1){

	    if (command_receivedString){                                        // Kommandozeilenbefehl erhalten
            command_receivedString = 0;
            command_transmitString = 1;

            validate = console_debug();                                     // Kommandozeilenbefehl korrekt?
	    }


	    if (command_transmitString){                                        // Kommandozeilenbefehl validiert
	        command_transmitString = 0;
            if (validate == 0){                                             // kommandozeilenbefehl korrekt
                validate = 1;
                commandHandler();                                           //
            } else {
                uart_send("FALSCHE eINGABE\r\n");
            }
	    }


	    if (command_temperatureState && command_temperatureTrack){           // Balken-LED
	        command_temperatureState = 0;
	        temperatureState();
	    }
/*
	    if (commmand_changeCalender){       // TODO behandlung der kalenderbearbeitung


	    }
*/
	} // while

} // main




/*
 * Für alte funktionen
 *
if(command_receivedString){                                     // warte bis kompletter String ankommt
    command_receivedString = 0;
    command_transmitString = 1;

    compareReceivedParameter();
    start_receive();
} // if receivedString


if(command_transmitString){                                     // warte bis kompletter String gesendet
    command_transmitString = 0;

    compareTransmittedParameter();
    start_transmit();

/***************************************
 * Variables
 **************************************
uint16_t indexReceiveString = 0;                         // Indexzahl für Eingabe-String
uint16_t indexTransmitString = 0;                        // Indexzahl für Ausgabe-String



/*************************************
 * Prototypes
 ************************************
void stop_receive(void);


/**
 * Setup UART für 4MHz
 *
void uart_init(void)
{
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
    command_transmitString = 0;                                 // ist True sobald kompletter String gesendet wurde
}



/*
 * sendet @str über Schnittstelle UART
 *
void uart_send(uint8_t *str)
{

    for (indexTransmitString = 0; indexTransmitString <= strlen(str); indexTransmitString++){
        transmittedString[indexTransmitString] = str[indexTransmitString];
    }
    indexTransmitString = 1;
    start_transmit();
}



/*
 * erhalte @str über Schnittstelle UART
 *
void uart_receive(uint8_t *str)
{
    for (indexTransmitString = 0; str[indexReceiveString] != '\0'; indexReceiveString++){
        receivedString[indexReceiveString] = str[indexReceiveString];
    }
    indexReceiveString = 0;
}



/*
 *
 *
void start_transmit(void)
{
    UCA1IE |= 0x02;                                              // aktiviere RX interrupt
    UCA1TXBUF = transmittedString[0];                           // aktiviere Transmit Flag
}



/*
 *
 *
void start_receive(void)
{
    UCA1IE |= 0x01;                                             // aktiviere Receive interrupt
}


/*
 *
 *
void stop_transmit(void)
{

    UCA1IE &= ~0x02;                                            // deaktiviere Transmit interrupt
    //test

}

/*
 *
 *
void stop_receive(void)
{
    UCA1IE &= ~0x01;                                            // deaktiviere Receive interrupt
}



/**
 * Isr erhaltene Character
 * werden in receiveString gespeichert
 *
#pragma vector=USCI_A1_VECTOR
__interrupt void isr_uartA1(void)

{
    if (UCA1IFG & UCRXIFG){                                                 // Fall: receive
        receivedString[indexReceiveString] = UCA1RXBUF;                     // lese Character
        indexReceiveString++;

        if(UCA1RXBUF == '\n' || (indexReceiveString == MAX_LENGHT_RECEIVE)){      // ist Ende des Strings/Arrays erreicht?
            receivedString[indexReceiveString-2] = '\0';                    // um Stringende zu erkennen, und entfernt mit [index-2]  '\r\n'
            indexReceiveString = 0;
            command_receivedString = 1;                                     // damit Umwandlung gestartret wird       TODO ändern
        } // if
        UCA1IFG &= ~UCRXIFG;                                                // lösche Receive Flag
    } // if receive


     if (UCA1IE&UCTXIE){                                                  // Fall: transmit             TODO mit IFG
        UCA1TXBUF = transmittedString[indexTransmitString];
        indexTransmitString++;
        if(UCA1TXBUF == '\n' || (indexReceiveString == MAX_LENGHT_TRANSMIT)){      // ist Ende des Strings erreicht?
            while (indexTransmitString){
                transmittedString[--indexTransmitString] = '\0';                  // um Stringende zu erkennen, und entfernt mit [index-2]  '\r\n'
            }
            indexTransmitString = 0;
            stop_transmit();
        } // if ende string
     } // if transmit

} // isr_uartA1

} // if transmitString*/
