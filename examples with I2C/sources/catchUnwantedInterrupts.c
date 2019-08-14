/*
 * catchUnwantedInterrupts.c
 *
 *  Created on: 20.05.2019
 *      Author: danielschubert
 */

#ifndef FUNCTIONS_CATCHUNWANTEDINTERRUPTS_C_
#define FUNCTIONS_CATCHUNWANTEDINTERRUPTS_C_


/*
 * catchUnwantedInterrupt.c
 *
 *  Created on: 09.05.2019
 *      Author: danielschubert
 */



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




#endif /* FUNCTIONS_CATCHUNWANTEDINTERRUPTS_C_ */
