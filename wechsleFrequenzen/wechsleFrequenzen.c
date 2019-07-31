#include <msp430.h>
#define BUTTON1 BIT1
#define BUTTON2 BIT1
#define LED1 BIT0

typedef enum
{
STATE_LED_OFF,
STATE_LED_BLINK_1HZ,
STATE_LED_BLINK_2HZ,
STATE_LED_BLINK_5HZ,
STATE_LED_BLINK_END
} state_led;

static state_led state;                                         // aktueller Zustand
static int delay;                                               // Variable zum Debouncing
static int counter;                                             // z�hlt Overflows f�r delay


/**
 * wechsleFrequenzen.c
 *
 * bei Tastendruck von Taster S1 erniedrigt sich die Frequenz der LED1
 * bei Tastendruck von Taster S2 erh�ht sich die Frequenz der LED1
 * LED1 aus <--> LED1 blinke 2Hz <--> LED1 5Hz <--> LED1 10Hz <--> LED1 50Hz <--> LED1 100Hz
 */
void main(void)
{
    /**
     * Setup Clocks
     * setzt REFO (~32768Hz) als Quelle f�r MCLK und SMCLK
     * und DCOCLKDIV (~1MHz) f�r ACLK
     */
    UCSCTL4 = SELM__REFOCLK + SELS__REFOCLK + SELA__DCOCLKDIV;

    WDTCTL = WDTPW + WDTHOLD;    state_led.STATE_LED
    P1OUT = 0x00;                                               // stellt sicher, dass Pins nicht schon gesetzt sind
    P2OUT = 0x00;                                               // stellt sicher, dass Pins nicht schon gesetzt sind

    /**
     * Setup Led
     */
    P2SEL &= ~LED1;                                             // GPIO-Funktion f�r LED1 gew�hlt
    P1DIR |= LED1;                                              // setzt LED1 als Ausgang
    state = STATE_LED_OFF;                                      // starte mit LED aus

    /**
     * Setup Button1
     */
    P2SEL &= ~BUTTON1;                                          // GPIO-Funktion f�r BUTTON1 gew�hlt
    P2DIR &= ~BUTTON1;                                          // setzte internen BUTTON1 als Eingang
    P2OUT |= BUTTON1;                                           // w�hlt Pull-up Modus f�r Button1
    P2REN |= BUTTON1;                                           // aktiviert Pull-up Widerstand f�r BUTTON1
    P2IES |= BUTTON1;                                           // high-to-low edge
    P2IFG = 0x00;                                               // l�sche BUTTON1 IFG
    P2IE |= BUTTON1;                                            // aktiviert BUTTON1 Interrupt

    /**
     * Setup Button2
     */
    P1SEL &= ~BUTTON2;                                          // GPIO-Funktion f�r BUTTON1 gew�hlt
    P1DIR &= ~BUTTON2;                                          // setzte internen BUTTON2 als Eingang
    P1OUT |= BUTTON2;                                           // w�hlt Pull-up Modus f�r Button2
    P1REN |= BUTTON2;                                           // aktiviert Pull-up Widerstand f�r BUTTON2
    P1IES |= BUTTON2;                                           // high-to-low edge
    P1IFG = 0x00;                                               // l�sche BUTTON2 IFG
    P1IE |= BUTTON2;                                            // aktiviert BUTTON2 Interrupt

    /**
     * Setup f�r LED blinken
     */
    TA0CTL = TASSEL_2 + ID_0 + MC_0 + TACLR;                    // TASSEL -> SMCLK, TAIE -> Timer Interrupt aktiviert, TACLR -> l�scht Inhalt von TAxR
    TA0EX0 = TAIDEX_0;                                          // zus�tzlicher Vorteiler auf 1
    TA0CCR0 = 16384;                                            // �berlauf-Frequenz 2Hz (SMCLK/1)/16384 = 2Hz (z�hle von 0 bis ~16384 hoch)
    TA0CTL |= MC_1;                                             // MC_1 -> UP-Modus, z�hle zum vorgebenen Wert hoch
    TA0CTL &= ~TAIFG;                                           // Z�hler wieder von 0 aufw�rts
    TA0CTL &= ~TAIE;                                            // Timer Interrupt deaktiviert
    TA0CCTL0 &= ~CCIE;                                          // deaktiviere Capture-Compare-Funktion f�r Timer_A
    TA0CCTL1 = 0x00;

    /**
     * Setup f�r Delay
     */
    TA1CTL = TASSEL_1 + ID_0 + MC_0 + TACLR;                    // TASSEL -> ACLK, MC_0 -> stoppt Counter, TACLR -> l�scht Inhalt von TAxR
    TA1EX0 = TAIDEX_0;                                          // zus�tzlicher Vorteiler auf 1
    TA1CCR0 = 1000;                                             // �berlauf-Frequenz 1msec (ACLK/1)/1000 = 1000Hz (z�hle von 0 bis 1000 hoch)
    TA1CTL |= MC_1;                                             // MC_1 -> UP-Modus, z�hle zum vorgebenen Wert hoch
    TA1CTL &= ~TAIFG;                                           // Z�hler wieder von 0 aufw�rts
    TA1CTL &= ~TAIE;                                            // Timer Interrupt deaktiviert
    TA1CCTL0 &= ~CCIE;                                          // deaktiviere Capture-Compare-Funktion f�r Timer_A
    delay = 60;                                                 // 0.06 sec (Zahl wird mit 1millisec multipliziert)
    counter = 0;                                                // z�hlt die �berl�ufe der isr_delay


    __enable_interrupt();                                       // aktiviert global alle Interrupts  (SR = 0x08;)

    while(1){
        /**
         *  Setup Watchdog
         *  schreibt Password -> 05Ah ins WDTPW-Register
         *  WDTCNTCL -> setzt den Watchdog-Zeitz�hler zur�ck auf Null
         *  WDTIS_4 -> gew�hlter Zeitz�hler auf 1s bei 32768Hz
        */
        //WDTCTL = WDTPW + WDTCNTCL + WDTIS_4;
    } // while
} // void main



/**
 * Timer Interrupt l�sst Led blinken
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void isr_LED_blink(void)
{
    P1OUT ^= LED1;                                              // l�sst LED1 blinken
    TA0CTL &= ~TAIFG;                                           // Z�hler wieder von 0 aufw�rts
} // isr_LED_blink



/**
 * erh�he Frequenzen beim Tastendr�cke
 */
#pragma vector=PORT2_VECTOR
__interrupt void isr_led_up(void)
{
    /**
     * aktiviert Timer1 f�r Debouncing (isr_delay())
     */

    if (P2IES & BUTTON1){                                       // fall taste gedr�ckt

        TA1CCTL0 |= CCIE;                                       // aktiviere Interruptfunktion f�r Timer_A
        P2IES &= ~BUTTON1;                                      // damit n�chtester interrupt das Loslassen des Tasters erf�llt

        switch(state){
            case STATE_LED_OFF:                                 // Fall: Taste 1. Mal gedr�ckt
                state = STATE_LED_BLINK_1HZ;                    // bei n�chsten Tastendruck LED blinkt mit
                TA0CCTL0 |= CCIE;                               // aktiviere Interruptfunktion f�r Timer_A
                break;
            case STATE_LED_BLINK_1HZ:                           // Fall: Taste 2. Mal gedr�ckt
                state = STATE_LED_BLINK_2HZ;                    // bei n�chsten Tastendruck LED blinkt mit
                TA0CCR0 = 8192;                                 // 2Hz (SMCLK/1)/8192 = 4Hz (z�hle von 0 bis ~8192 hoch)
                break;
            case STATE_LED_BLINK_2HZ:                           // Fall: Taste 3. Mal gedr�ckt
                state = STATE_LED_BLINK_END;                    // bei n�chsten Tastendruck LED blinkt mit
                TA0CCR0 = 3277;                                 // 5Hz (SMCLK/1)/3277 = 10Hz (z�hle von 0 bis ~3277 hoch)
               break;

            case STATE_LED_BLINK_END:                           // Fall: Taste 4. Mal gedr�ckt
                break;
        } // switch
    } else {
        TA1CCTL0 |= CCIE;                                       // aktiviere Interruptfunktion f�r Timer_A
        P2IES |= BUTTON1;                                       // n�chster interrupt erfolgt bei tastendruck
    } // if

    P2IFG = 0x00;                                               // damit wieder ein Interrupt ausgel�st werden kann
    P2IE &= ~BUTTON1;                                           // deaktiviert BUTTON1 Interrupt

} // isr_button1



/**
 * erniedrige Frequenzen beim Tastendr�cken
 */
#pragma vector=PORT1_VECTOR
__interrupt void isr_led_down(void)
{
    /**
     * aktiviert Timer1 f�r Debouncing (isr_delay())
     */
    if (P1IES & BUTTON2){                                       // fall taste gedr�ckt

        TA1CCTL0 |= CCIE;                                       // aktiviere Interruptfunktion f�r Timer_A
        P1IES &= ~BUTTON2;                                      // damit n�chtester interrupt das Loslassen des Tasters erf�llt

        switch(state){

            case STATE_LED_BLINK_END:                           // Fall: Taste 2. Mal gedr�ckt
                state = STATE_LED_BLINK_2HZ;                    // bei n�chsten Tastendruck LED blinkt mit
                TA0CCR0 = 8192;                                 // 2Hz (SMCLK/1)/8192 = 4Hz (z�hle von 0 bis ~8192 hoch)
                break;
            case STATE_LED_BLINK_2HZ:                           // Fall: Taste 3. Mal gedr�ckt
                state = STATE_LED_BLINK_1HZ;                    // bei n�chsten Tastendruck LED aus
                TA0CCR0 = 16384;                                // 1Hz (SMCLK/1)/16384 = 2Hz (z�hle von 0 bis ~16384 hoch)
                break;
            case STATE_LED_BLINK_1HZ:                           // Fall: Taste 4. Mal gedr�ckt
                state = STATE_LED_OFF;                          // LED aus
                TA0CCTL0 &= ~CCIE;                              // deaktiviere Capture-Compare-Funktion f�r Timer_A
                TA0CTL &= ~TAIFG;                               // Z�hler wieder von 0 aufw�rts
                P1OUT &= ~LED1;                                 // macht LED1 aus
            case STATE_LED_OFF:                                 // Fall: Taste 4. Mal gedr�ckt
                break;
        } // switch
    } else {
        TA1CCTL0 |= CCIE;                                       // aktiviere Interruptfunktion f�r Timer_A
        P1IES |= BUTTON2;                                       // damit n�chster Interrupt das Dr�cken des Tasters erf�llt
    } // if

    P1IFG &= ~BUTTON2;                                          // damit wieder ein Interrupt ausgel�st werden kann
    P1IE &= ~BUTTON2;                                           // deaktiviert BUTTON1 Interrupt

} // isr_button2



/**
 * Timer f�r Debouncing (delay)
 */
#pragma vector=TIMER1_A0_VECTOR
__interrupt void isr_delay(void)
{
    if (counter == delay){                                      // Fall: �berl�ufe sind gleich der gew�nschten Zeit
        P2IE |= BUTTON1;                                        // aktiviert BUTTON1 Interrupt
        P1IE |= BUTTON2;                                        // aktiviert BUTTON1 Interrupt
        TA1CCTL0 &= ~CCIE;                                      // deaktiviere Capture-Compare-Funktion f�r Timer_A
        TA1CTL &= ~TAIFG;                                       // Z�hler wieder von 0 aufw�rts
        counter = 0;                                            // damit �berl�ufe wieder von Null weg gez�hlt werden
    } else {
        counter++;
    } //if
    TA1CTL &= ~TAIFG;                                           // Z�hler wieder von 0 aufw�rts
} // isr_LED_blink



/**
 * dummy isr's
 * um nicht erwartete Interrupts abzufangen
 */
#pragma vector=TIMER0_A1_VECTOR
__interrupt void isr_timer0A1(void)
{
        __no_operation();
}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void isr_timer0B0(void)
{
        __no_operation();
}

#pragma vector=TIMER0_B1_VECTOR
__interrupt void isr_timer0B1(void)
{
        __no_operation();
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void isr_timer1A1(void)
{
        __no_operation();
}

#pragma vector=TIMER2_A0_VECTOR
__interrupt void isr_timer2A0(void)
{
        __no_operation();
}

#pragma vector=TIMER2_A1_VECTOR
__interrupt void isr_timer2A1(void)
{
        __no_operation();
}
