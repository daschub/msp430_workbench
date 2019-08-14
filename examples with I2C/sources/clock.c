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
#include "headers/clock.h"


/**
 * Setup XT2  MCLK -> 4MHz   SMCLK -> 4MHz  ACLK -> 1MHZ
 */
void xt2_init(void)
{
    P5SEL = 0x3C;                                               // damit XT2 aktiviert werden kann (XT2 I/O -> P5.2/P5.3)
                                                               // damit XT1 aktiviert werden kann (XT1 I/O -> P5.4/P5.5)

    UCSCTL3 = 0x0000;                                           // FLLref = XT2
    UCSCTL6 = 0x00C1;                                           // XT2DRIVE_1, XT1DRIVE_3, BYPASS = 0,XCAP = 0, XTS = 0 -> LF Mode; TODO
    UCSCTL6 &= ~0x0001;                                         // XT1OFF = 0
                                                               //TODO
    UCSCTL4 = 0x0055;                                           // MCLK & SMCLk = XT2 ; ACLK = REFO;
    UCSCTL5 = 0x0000;                                           // Source Dividers /1


    do{                                                         // warte bis sich XT2 stabilisiert
       UCSCTL7 &= ~(XT2OFFG);                                  // lösche XT2 fault flags
       SFRIFG1 &= ~OFIFG;                                      // lösche fault flags
    } while (UCSCTL7&XT2OFFG);                                  // Teste XT2 fault flag

    do{                                                         // warte bis sich XT2 stabilisiert
    UCSCTL7 &= ~(XT1LFOFFG);                                    // lösche XT2 fault flags
       SFRIFG1 &= ~OFIFG;                                      // lösche fault flags
    } while (UCSCTL7&XT1LFOFFG);                                    // Teste XT2 fault flag
}

#endif /* CLK_CLOCK_C_ */
