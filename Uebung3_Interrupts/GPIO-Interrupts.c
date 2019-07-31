#include <msp430.h>

#define BUTTON1 BIT1
#define BUTTON2 BIT1
#define LED1 BIT0
#define LED2 BIT7

/**
 * GPIO-Interrupts.c
 */
void main(void)
{
    UCSCTL4 = SELM__REFOCLK;            // setzt REFO (~32768Hz) als Quelle f�r MCLK

    P1OUT = 0x00;                       // stellt sicher, dass Pins nicht schon gesetzt sind
    P4OUT = 0x00;                       // stellt sicher, dass Pins nicht schon gesetzt sind

    P2SEL &= ~BUTTON1;                  // GPIO-Funktion f�r BUTTON1 gew�hlt
    P1SEL &= ~BUTTON2;                  // GPIO-Funktion f�r BUTTON2 gew�hlt
    P2SEL |= LED1;                      // GPIO-Funktion f�r LED1 gew�hlt
    P1SEL |= LED2;                      // GPIO-Funktion f�r LED2 gew�hlt

    P2DIR &= ~BUTTON1;                  // setzte internen BUTTON1 als Eingang
    P1DIR &= ~BUTTON2;                  // setzte internen BUTTON2 als Eingang
    P1DIR |= LED1;                      // setzte LED1 als Ausgang
    P4DIR |= LED2;                      // setzte LED2 als Ausgang
    P2OUT |= BUTTON1;                   // w�hlt Pull-up Modus f�r Button1
    P1OUT |= BUTTON2;                   // w�hlt Pull-up Modus f�r Button2
    P2REN |= BUTTON1;                   // aktiviert Pull-up Widerstand f�r BUTTON1
    P1REN |= BUTTON2;                   // aktiviert Pull-up Widerstand f�r BUTTON2

    P2IES |= BUTTON1;                   // high-to-low edge
    P1IES |= BUTTON2;                   // high-to-low edge
    P2IFG &= ~BUTTON1;                  // l�sche BUTTON1 IFG
    P1IFG &= ~BUTTON2;                  // l�sche BUTTON2 IFG
    P2IE |= BUTTON1;                    // aktiviert BUTTON1 Interrupt
    P1IE |= BUTTON2;                    // aktiviert BUTTON2 Interrupt

    __enable_interrupt();               // aktiviert global alle Interrupts  (SR = 0x08;)

    while(1){
        /* Watchdog Konfiguration
         * schreibt Password -> 05Ah ins WDTPW-Register
         * WDTCNTCL -> setzt den Watchdog-Zeitz�hler zur�ck auf Null
         * WDTIS_4 -> gew�hlter Zeitz�hler auf 1s bei 32.768kHz
        */
        WDTCTL = WDTPW + WDTCNTCL + WDTIS_4;
    } // while
} // void main

#pragma vector=PORT2_VECTOR
__interrupt void isr_button1(void)
{
    if (P2IES & BUTTON1){               // fall taste gedr�ckt
        P1OUT |= LED1;                  // macht LED1 ein
        P2IES &= ~BUTTON1;              // damit n�chtester interrupt das Loslassen des Tasters erf�llt
    } else {                            // fall taste losgelassen
        P1OUT &= ~LED1;                 // macht LED1 aus
        P2IES |= BUTTON1;               // n�chster interrupt erfolgt bei tastendruck
    } // if
    P2IFG &= ~BUTTON1;                  // damit wideer ein interrupt ausgel�st werden kann
} // isr_button1

#pragma vector=PORT1_VECTOR
__interrupt void isr_button2(void)
{
    if (P1IES & BUTTON2){               // fall taste gedr�ckt
        P4OUT |= LED2;                  // schaltet LED2 ein
        P1IES &= ~BUTTON2;              // n�chster Interrupt erfolgt beim Loslassen des Tasters
    } else {                            // Fall Taste losgelassen
        P4OUT &= ~LED2;                 // schaltet LED aus
        P1IES |= BUTTON2;               // damit n�chster Interrupt das Dr�cken des Tasters erf�llt
    } // if
    P1IFG &= ~BUTTON2;                  // damit wieder ein Interrupt ausgel�st werden kann
} // isr_button2
