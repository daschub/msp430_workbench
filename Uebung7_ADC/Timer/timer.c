
/*
 * timer.c
 *
 *  Created on: 09.05.2019
 *      Author: danielschubert
 */

#ifndef TIMER_TIMER_C_
#define TIMER_TIMER_C_

#include <stdint.h>

#include <msp430.h>
#include "timer.h"



/**
 * Setup für Delay
 */
void timer_init(void){

    TA1CTL = 0x0100;                                            // TASSEL -> ACLK, MC_0 -> stoppt Counter, TACLR -> löscht Inhalt von TAxR
    TA1EX0 = 0x0000;                                            // zusätzlicher Vorteiler auf 1

    // Timer für 1MHz -> delay 1ms
    TA1CCR0 = 1000;                                             // Überlauf-Frequenz 1msec (ACLK/1)/1000 = 1000Hz (zähle von 0 bis 1000 hoch)

    TA1CTL |= 0x0010;                                           // MC_1 -> UP-Modus
    TA1CCTL0 = 0x10;                                            // deaktiviere Capture-Compare-Funktion
}

void start_timer(void){
    TA1CCTL0 |= 0x10;                                           // aktiviere Capture-Compare-Funktion
    TA1CTL &= ~0x01;                                            // Zähler wieder von 0 aufwärts
}

void stop_timer(void){
    TA1CCTL0 &= ~0x10;                                          // deaktiviere Capture-Compare-Funktion
    TA1CTL &= ~0x01;                                            // Zähler wieder von 0 aufwärts
}


void timer_delay(uint16_t delay){
    countOverflows = delay;
    while(countOverflows);
    stop_timer();
}

/**
 * Isr für Delay
 */
#pragma vector=TIMER1_A0_VECTOR
__interrupt void isr_delay(void)
{
    if(countOverflows){
        countOverflows--;
    }
    TA1CTL &= ~0x01;                                            // Zähler wieder von 0 aufwärts
} // isr_delay


#endif /* TIMER_TIMER_C_ */
