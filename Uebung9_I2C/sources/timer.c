
/*
 * timer.c
 *
 *  Created on: 09.05.2019
 *      Author: danielschubert
 */

#ifndef TIMER_TIMER_C_
#define TIMER_TIMER_C_


/**********************************************
 * Includes
 **********************************************/
#include <stdint.h>

#include <msp430.h>
#include "headers/timer.h"



/**
 * Setup f�r Delay hier ACLK 32kHz
 */
void timer1_init(void)
{

    TA1CTL = 0x0100;                                            // TASSEL -> ACLK, MC_0 -> stoppt Counter, TACLR -> l�scht Inhalt von TAxR
    TA1EX0 = 0x0000;                                            // zus�tzlicher Vorteiler auf 1

    // Timer f�r 32kHz -> delay ~300ms
    TA1CCR0 = 65000;                                            // �berlauf-Frequenz .5sec (ACLK/1)/16384 = 2Hz (z�hle von 0 bis 16384 hoch)

    TA1CTL |= 0x0010;                                           // MC_1 -> UP-Modus
    TA1CCTL0 = 0x10;                                            // deaktiviere Capture-Compare-Funktion
}



/*
 * startet timer funktion
 */
void start_timer1(void)
{
    TA1CCTL0 |= 0x10;                                           // aktiviere Capture-Compare-Funktion
    TA1CTL &= ~0x01;                                            // Z�hler wieder von 0 aufw�rts
}



/*
 * stopt timer funktion
 */
void stop_timer1(void)
{
    TA1CCTL0 &= ~0x10;                                          // deaktiviere Capture-Compare-Funktion
    TA1CTL &= ~0x01;                                            // Z�hler wieder von 0 aufw�rts
}



/*
 * @delay variable, die die entsprechende Zeit als delay �bergibt
 */
void timer1_delay(uint16_t delay)
{
    countOverflows = delay;
    while(countOverflows);
    stop_timer1();
}


/*
 *
 *
void timer1_watch(uint16_t delay)
{
    counterOverflows = delay;
}
*/

/**
 * Isr f�r Delay
 */
#pragma vector=TIMER1_A0_VECTOR
__interrupt void isr_delay(void)
{

    if(countOverflows){
        countOverflows--;
    }

    command_temperatureState = 1;

    TA1CTL &= ~0x01;                                            // Z�hler wieder von 0 aufw�rts
} // isr_delay





#endif /* TIMER_TIMER_C_ */
