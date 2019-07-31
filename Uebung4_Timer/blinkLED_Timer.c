#include <msp430.h> 

#define LED1 BIT0

/**
 * blinkLED_Timer.c
 * lässt LED mit der Frequenz von 1Hz blinken
 * durch eine Timer-Interruptfunktion
 */
void main(void)
{
    UCSCTL4 = SELM__REFOCLK + SELS__REFOCLK + SELA__REFOCLK;// setzt REFO (~32768Hz) als Quelle für MCLK

    P1OUT = 0x00;                                           // stellt sicher, dass Pins nicht schon gesetzt sind
    P1DIR |= LED1;                                          // setzt LED1 als Ausgang
    P2SEL |= LED1;                                          // GPIO-Funktion für LED1 gewählt

    TA0CCTL0 |= CCIE;                                       // aktiviere Interruptfunktion für Timer_A
    TA0CTL = TASSEL_2 + ID_0 + MC_0 + TAIE + TACLR;         // TASSEL -> SMCLK, TAIE -> Timer Interrupt aktiviert, TACLR -> löscht Inhalt von TAxR
    TA0EX0 = TAIDEX_0;                                      // zusätzlicher Vorteiler auf 1
    TA0CCR0 = 5461;                                         // Überlauf-Frequenz 2Hz (SMCLK/1)/16384 = 2Hz (zähle von 0 bis ~16384 hoch)
    TA0CTL |= MC_1;                                         // MC_1 -> UP-Modus, zähle zum vorgebenen Wert hoch

    __enable_interrupt();                                   // aktiviert global alle Interrupts  (SR = 0x08)

    while(1){
        /* Watchdog Konfiguration
         * schreibt Password -> 05Ah ins WDTPW-Register
         * WDTCNTCL -> setzt den Watchdog-Zeitzähler zurück auf Null
         * WDTIS_4 -> gewählter Zeitzähler auf 1s bei 32768Hz
        */
        WDTCTL = WDTPW + WDTCNTCL + WDTIS_4;
    } // while
} // void main

#pragma vector=TIMER0_A0_VECTOR
__interrupt void isr_LEDblink(void)
{
    P1OUT ^= LED1;                                          // lässt LED1 blinken
    TA0CTL &= ~TAIFG;                                       // Zähler wieder von 0 aufwärts
} // isr_LEDblink
