/*
 * main.h
 *
 *  Created on: 09.05.2019
 *      Author: danielschubert
 */

#include <stdint.h>

#include <msp430.h>
#include <strings.h>
#include <stdio.h>
#include "CLK/clock.h"
#include "Timer/timer.h"
#include "UART/uart.h"
#include "ADC/adc.h"
#include "Functions/functions.h"

#define GET_ADC     "GET ADC\r\n"


/**
 * main.c
 * gibt gemessenen Spannungswert über die UART-Verbindung
 * durch den String "GET ADC" aus
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	                                // stop watchdog timer
	
	xt2_init();
    uart_init();
    adc_init();
    timer_init();

    start_conversion();

    start_timer();


    __enable_interrupt();


	while(1){

	    /*
	    if(command_convertAdc){
	        command_convertAdc = 0;
	        timer_delay(300);
	    }*/
	    if (command_average){
	        command_average = 0;
            voltageTransmit = voltage_result();
	        command_voltageAverage = 1;
	    } // if command average


	    if(command_receivedString){                             // warte bis kompletter String ankommt
            command_receivedString = 0;
            command_transmitString = 1;

            if (strcasecmp(GET_ADC, receivedString) == 0){      // ist eingabe richtig?
                command_konsolenEingabe = 1;
                start_conversion();
                //voltage_change();
            } else {
                command_konsolenEingabe = 0;
            }
        } // if receivedString


        if(command_transmitString && command_voltageAverage){   // warte bis kompletter String gesendet
            command_transmitString = 0;
            command_voltageAverage = 0;
            if(command_konsolenEingabe){                        // fall: korrekte Konsoleneingabe
                command_konsolenEingabe = 0;

                strcpy(transmittedString, convertIntToString(voltage_input()));                               // TODO
                sprintf("%d mV\r\n", transmittedString);      // Spannungswert als String

            } else{                                             // fall: falsche Konsoleneingabe
                strcpy(transmittedString, "Eingabe: Unbekannt\r\n");
            } // if konsoleneingabe

            start_transmit();
            start_timer();
        } // if transmitString

	} // while
} // main
