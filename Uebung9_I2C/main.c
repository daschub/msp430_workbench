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

/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	xt2_init();
	timer_init();
	i2c_init();
	uart_init();

    uint8_t validate = 1;
	__enable_interrupt();


	while(1){

	    if (command_receivedString){
            command_receivedString = 0;
            command_transmitString = 1;

            validate = console_debug();
            start_receive();
	    }

	    if (command_transmitString){
	        command_transmitString = 0;
            if (validate == 0){
                validate = 1;
                commandHandler();
            } else {
                uart_send("FALSCHE eINGABE\r\n");
            }
	    }

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
} // if transmitString*/
