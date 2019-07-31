/*
 * clock.c
 *
 *  Created on: 20.05.2019
 *      Author: danielschubert
 */

#ifndef CLK_CLOCK_C_
#define CLK_CLOCK_C_


#include <stdint.h>

#include <msp430.h>
#include "clock.h"

/**
 * Setup XT2  MCLK -> 4MHz   SMCLK -> 4MHz  ACLK -> 1MHZ
 */
void xt2_init(void){
    P5SEL = 0x0C;                                               // damit XT2 aktiviert werden kann (XT2 I/O -> P5.2/P5.3)
    UCSCTL3 = 0x0050;                                           // FLLref = XT2
    UCSCTL6 = 0x0000;                                           // aktiviert XT2
    UCSCTL4 = 0x0555;                                           // MCLK & SMCLk = XT2 ; ACLK = XT2;
    UCSCTL5 = 0x0200;                                           // ACLK Source Divider /4

    do{                                                         // warte bis sich XT2 stabilisiert
        UCSCTL7 &= ~(XT2OFFG);                                  // lösche XT2 fault flags
        SFRIFG1 &= ~OFIFG;                                      // lösche fault flags
    } while (UCSCTL7&XT2OFFG);                                  // Teste XT2 fault flag
}

#endif /* CLK_CLOCK_C_ */
