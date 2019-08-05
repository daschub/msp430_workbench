#include <msp430.h> 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/clock.h"
#include "headers/console.h"


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	xt2_init();
	

	uint8_t validate = 0;
	uint8_t string[] = "led on 7 10 5";
	uint8_t countOfStrings = 0;

	while(1){




	    countOfStrings = splitConsoleString(string);

	    validate = validateConsoleParameter(countOfStrings);

	    if (validate == 0){
	        leds = commandHandler(string);
	    } /* else {
	        uart_send ("falsche konsoleneingabe. (--help)");
	    }*/

	    // uart_send(leds, lm75);
	}


}
