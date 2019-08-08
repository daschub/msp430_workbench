/*
 * i2c.c
 *
 *  Created on: 06.06.2019
 *      Author: danielschubert
 */



/**********************************************
 * Includes
 **********************************************/
#include <stdint.h>

#include <msp430.h>
#include <stdio.h>
#include "headers/i2c.h"
#include "headers/timer.h"
#include <strings.h>


/***********************************************
 * Variables
 ************************************************/


/***********************************************
 * Prototypes
 ***********************************************/
void start_transmit_i2c(void);
void start_receive_i2c(void);
void stop_transmit_i2c(void);


/***********************************************
 * Functions
 ***********************************************/

/**
 * I^2C setup
 *
 *
 * recommended init steps:
 * 1. set UCSWRST
 * 2. init all USCI reg with UCSWRST = 1
 * 3. config ports
 * 4. clear UCSWRST
 * 5. enable interrupts
 */
void i2c_init(void)
{
    UCB1CTL1 = 0x01;                                            // UCSWRST = 1
    UCB1CTL0 |= 0x0F;                                           // 7-bit adress (2^7 Slaves); UCMST = 1; UCMODE -> I^2C; UCSNYC -> synchronous
    UCB1CTL1 |= 0x80;                                           // Taktquelle -> SMCLK (1MHz)
    UCB1BR0 = 0x64;                                             // Rate: 10 kbit/s -> 1MHz / 10k = 100 (0x64)
    UCB1BR1 = 0x00;                                             //
    P4SEL |= 0x06;                                              // P4.1 = SCL, P4.2 = SDA;

    UCB1CTL1 &= ~0x01;                                          // USCI Modul ist aktiviert und Tranceiver ist bereit
    //UCB1IE |= 0x22;                                             // NACK, Start und Stopp IE = 1

}



/*
 * aktiviere Transmit
 */
void start_transmit_i2c(void)
{
    UCB1CTL1 |= 0x12;                                           // UCTR = 1; UCTXSTT = 1
} // start_transmit_i2c



/*
 * aktiviere Receive
 */
void start_receive_i2c(void)
{
    UCB1CTL1 &= ~0x10;                                          // UCTR = 0
    UCB1CTL1 |= 0x02;                                           // UCTXSTT = 1
} // start_transmit_i2c



/*
 * sende als Master
 * @slave übergibt Adresse des Slaves
 * @byte übergibt Zustand der Portpins
 */
void i2c_master_send(uint16_t slave, uint8_t writeByte, uint16_t length)
{

    UCB1I2CSA = slave;                                          // setzte Slaveadresse
    start_transmit_i2c();                                       // UCTR = 1, UCTSTT = 1

    while (length){

        while ((UCB1CTL1&UCTXSTT) && ((UCB1IFG&UCTXIFG) == 0));     // busy wait -> wartet bis ack nach slaveadresse kommt

        UCB1TXBUF = writeByte;                                           // schreibe in Buffer
        __delay_cycles(1000);

        writeByte++;
        length--;

    } // while

    UCB1CTL1 |= 0x04;                                           // UCTXSTP = 1
    UCB1IFG &= ~0x02;                                           // UCTXIFG = 0
    /*
    UCB1CTL1 &= ~0x12;                                          // UCTR = 0; UCTXSTT = 0
   */
} // i2c_master_send



/*
 * lese als Master
 * @slave übergibt Adresse des Slaves
 * @return gibt die ausgelesene Temperatur zurück
 *
 *
 */
void i2c_master_receive(uint16_t slave, uint8_t *readByte, uint16_t len)
{
    UCB1I2CSA = slave;                                          // setzte Slaveadresse
    start_receive_i2c();                                        // UCTR = 1, UCTSTT = 1

    while (len){
        while (UCB1CTL1&UCTXSTT);                               // busy wait -> wartet bis ack nach slaveadresse kommt

        *readByte = (uint8_t)UCB1RXBUF;                         // lese Buffer
        __delay_cycles(1000);

        readByte++;
        len--;
    } // while len

    UCB1CTL1 |= 0x04;                                           // UCTXSTP = 1

} // i2c_master_receive



/**
 * ISR für I^2C
 *
 *
 * 7Bit AdressModus
 *  ------------------------------------------------------------------
 * |S | SlaveAdress | R/W | ACK | Data | ACK | Data | ACK |  ...  | P |
 *  ------------------------------------------------------------------
 *  1Bit   7Bit       1Bit  1Bit  1Byte  1Bit  1Byte  1Bit 1Bit
 *                                                                      ___
 * Start-Bedingung, solange SCL = stabil  und high2low-Flanke auf SDA      \___
 *
 *                                                                          ___
 * Stopp-Bedingnugn, solange SCL = stabil und low2high-Flanke auf SDA   ___/
 *
 *
 * Repeated Start-Bedingung
 *  -----------------------------------------------------------------------------------------
 * |S | SlaveAdress | R/W | ACK | Data | ACK | S | SlaveAddress | R/W | ACK | Data | ACK | P |
 *  -----------------------------------------------------------------------------------------
 *
 *
 */
#pragma vector=USCI_B1_VECTOR
__interrupt void isr_i2c_B1(void)
{

    switch(__even_in_range(UCB1IV,0x0C)) {

            // no interrupt
        case 0: break;


            // arbitration; nur wichtig falls mehrere master ...
        case 2: break;


            // NACK                                                     // This flag is set when an acknowledge is expected but is not received.
        case 4:                                                         // UCNACKIFG is automatically cleared when a START condition is received.
            if (command_slaveAddressSet){                               // NACK received after slave address
                UCB1CTL1 &= ~0x04;                                      // UCTXSTP = 0
            } else if (!(UCB1IFG&UCTXIFG) && (UCB1TXBUF == 0)){         // NACK received after a data Byte
                UCB1CTL1 |= 0x12;                                       // UCTR = 1; UCTXSTT = 1
            }
            break;


            // Start
        case 6: break;

            // Stopp                                                    // UCSTPIFG is used in slave mode only and is automatically
        case 8:                                                         // cleared when a START condition is received.
            break;

            // Receive
        case 10:
            /*
            receivedData[indexReceiveData] = UCB1TXBUF;    // R/W = 1; Master <- Slave
            indexReceiveData++;
            if (UCB1RXBUF == 0){
                indexReceiveData = 0;
            } // if ende string
            //UCB1IFG &= ~0x01;                                      // löscht Receive IGF
            */
            __no_operation();
            //arbritation lost and continues as slave receiver
            break;


            // Transmit
        case 12:

            __delay_cycles(1000);

            UCB1TXBUF = transmitData[indexTransmitData];                // transmit R/W = 0;  Master -> Slave
            indexTransmitData++;
            /*if(indexTransmitData == 1){
                UCB1CTL1 |= 0x04;                                       // UCTXSTP = 1;
                UCB1IFG &= ~0x02;                                       // UCTXIFG = 0;
            } else if (commandRepeatedStart & lenghtData - 1){
                UCB1CTL1 |= 0x12;                                       // UCTR = 1; UCTXSTT = 1*/
            if(UCB1TXBUF == '\0') {
                indexTransmitData = 0;
            }
            break;


        default:
            break;
    } // switch even in range

} // isr_i2c_B1



