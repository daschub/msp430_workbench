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
    UCSCTL4 = SELM__REFOCLK;            // setzt REFO (~32768Hz) als Quelle für MCLK

    P1OUT = 0x00;                       // stellt sicher, dass Pins nicht schon gesetzt sind
    P4OUT = 0x00;                       // stellt sicher, dass Pins nicht schon gesetzt sind

    P2SEL &= ~BUTTON1;                  // GPIO-Funktion für BUTTON1 gewählt
    P1SEL &= ~BUTTON2;                  // GPIO-Funktion für BUTTON2 gewählt
    P2SEL |= LED1;                      // GPIO-Funktion für LED1 gewählt
    P1SEL |= LED2;                      // GPIO-Funktion für LED2 gewählt

    P2DIR &= ~BUTTON1;                  // setzte internen BUTTON1 als Eingang
    P1DIR &= ~BUTTON2;                  // setzte internen BUTTON2 als Eingang
    P1DIR |= LED1;                      // setzte LED1 als Ausgang
    P4DIR |= LED2;                      // setzte LED2 als Ausgang
    P2OUT |= BUTTON1;                   // wählt Pull-up Modus für Button1
    P1OUT |= BUTTON2;                   // wählt Pull-up Modus für Button2
    P2REN |= BUTTON1;                   // aktiviert Pull-up Widerstand fÜr BUTTON1
    P1REN |= BUTTON2;                   // aktiviert Pull-up Widerstand fÜr BUTTON2

    P2IES |= BUTTON1;                   // high-to-low edge
    P1IES |= BUTTON2;                   // high-to-low edge
    P2IFG &= ~BUTTON1;                  // lösche BUTTON1 IFG
    P1IFG &= ~BUTTON2;                  // lösche BUTTON2 IFG
    P2IE |= BUTTON1;                    // aktiviert BUTTON1 Interrupt
    P1IE |= BUTTON2;                    // aktiviert BUTTON2 Interrupt

    __enable_interrupt();               // aktiviert global alle Interrupts  (SR = 0x08;)

    while(1){
        /* Watchdog Konfiguration
         * schreibt Password -> 05Ah ins WDTPW-Register
         * WDTCNTCL -> setzt den Watchdog-Zeitzähler zurück auf Null
         * WDTIS_4 -> gewählter Zeitzähler auf 1s bei 32.768kHz
        */
        WDTCTL = WDTPW + WDTCNTCL + WDTIS_4;
    } // while
} // void main

#pragma vector=PORT2_VECTOR
__interrupt void isr_button1(void)
{
    if (P2IES & BUTTON1){               // fall taste gedrückt
        P1OUT |= LED1;                  // macht LED1 ein
        P2IES &= ~BUTTON1;              // damit nächtester interrupt das Loslassen des Tasters erfüllt
    } else {                            // fall taste losgelassen
        P1OUT &= ~LED1;                 // macht LED1 aus
        P2IES |= BUTTON1;               // nächster interrupt erfolgt bei tastendruck
    } // if
    P2IFG &= ~BUTTON1;                  // damit wideer ein interrupt ausgelöst werden kann
} // isr_button1

#pragma vector=PORT1_VECTOR
__interrupt void isr_button2(void)
{
    if (P1IES & BUTTON2){               // fall taste gedrückt
        P4OUT |= LED2;                  // schaltet LED2 ein
        P1IES &= ~BUTTON2;              // nächster Interrupt erfolgt beim Loslassen des Tasters
    } else {                            // Fall Taste losgelassen
        P4OUT &= ~LED2;                 // schaltet LED aus
        P1IES |= BUTTON2;               // damit nächster Interrupt das Drücken des Tasters erfüllt
    } // if
    P1IFG &= ~BUTTON2;                  // damit wieder ein Interrupt ausgelöst werden kann
} // isr_button2
