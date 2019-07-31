/*
 * adc.c
 *
 *  Created on: 09.05.2019
 *      Author: danielschubert
 */
#ifndef ADC_ADC_C_
#define ADC_ADC_C_

#include <stdint.h>

#include <msp430.h>
#include <strings.h>
#include "adc.h"
#include "UART/uart.h"

uint16_t adcValues[50];
uint16_t voltageAverageTemp = 0;
uint16_t voltageAverageOld = 0;
uint32_t voltageAverageRaw = 0;
uint16_t voltageValues[50];
uint16_t indexVoltageValues = 0;
uint16_t voltageSumCounter = 0;
uint32_t voltageInputRaw = 0;                                   // variable für rohen Vin wert
uint32_t voltageSumValue = 0;                                   // summe durchschnittsspannung



/**
 * Setup ADC
 */
void adc_init(void)
{
    P6SEL |= 0x01;                                              // aktiviere A/D Kanal A0
    ADC12CTL0 = 0x0070;                                         // deaktiviere Conversion -> AD12ENC = 0; ADCREF -> 2,5V ; enable REF -> ADC12ON = 1 ; enable ADC
    ADC12CTL1 = 0x0218;                                         // sampling timer -> SHP = 1 ; ADC10CONSEQ -> single-channel ; clk source -> SMCLK

    REFCTL0 = 0x00;                                             // aktiviere Referenzspannung -> REFMSTR = 0;
    ADC12MCTL0 = 0x10;                                          // VREF+ , AVSS ; ADC12INCH -> A0
    ADC12IE = 0x01;                                             // aktiviere Interrupts (ansonsten polling ADC12BUSY Bit)
    ADC12CTL0 |= 0x02;                                          // aktiviere ADC -> AD12ENC = 1 ;
}



/*
 *
 */
void start_conversion(void)
{
    ADC12CTL0 |= 0x01;                                          // starte Umwandlung -> AD12SC = 1
}



/*
 *
 */
int voltage_input(void)
{
    return (voltageTransmit * VOLTAGE_REF) / ADC_VALUE;         // Vin = ( Nadc * 2500mV ) / 4095 [mV]

}



/*
 * prüfe wie gross die Spannungsänderung aktuell ist
 * gebe neuen spannungswert zurück, falls änderung größer 20,
 * ansonsten gebe alten wert zurück
 */
int voltage_change(uint16_t voltage1, uint16_t voltage2)
{
    int16_t voltageChange = voltage1 - voltage2;

    if (voltageChange > 40 | voltageChange < -40){
        voltage1 = voltage2;
        command_transmitString = 1;                        // Indexzahl für Ausgabe-String
        command_konsolenEingabe = 1;

        return voltage1;
    } else {
        return voltage2 ;
    } // if
} // voltageChange



/*
 *
 */
int voltage_result(void)
{
    voltageValues[indexVoltageValues] = voltageInputRaw;                                         // schreibe mittelwerte in array
    indexVoltageValues++;
    start_conversion();                                                                 // neue umwandlung
    if (indexVoltageValues == ADC_SUM_AVERAGE){                                              // 50 werte?
        while(indexVoltageValues){
            voltageAverageRaw += voltageValues[indexVoltageValues - 1];
            indexVoltageValues--;
        } // while
        voltageAverageRaw /= ADC_SUM_AVERAGE;                                           // durchnittswert array
        voltageAverageTemp = voltageAverageRaw;
        voltageAverageOld = voltage_change(voltageAverageOld, voltageAverageTemp);                    // gibt neues zurück falls änderung durch poti
    } // if array voll
    return voltageAverageOld;
}



/**
 * ADC isr
 *
 */
#pragma vector=ADC12_VECTOR
__interrupt void adc12bit(void)
{
    voltageSumValue += ADC12MEM0;                                       // summe der Spannungswerte
    voltageSumCounter++;
    ADC12IFG |= 0x01;

    if (voltageSumCounter == ADC_SUM_AVERAGE){
        voltageInputRaw = (voltageSumValue / ADC_SUM_AVERAGE);          // roher durchschnittswert Vin
        ADC12IFG &= ~0x01;                                              // solange umwandeln bis array voll
        voltageSumValue = 0;
        voltageSumCounter = 0;                                              // array voll
        command_average = 1;                                          // berechne Mittlewert
    } // if
} // adc12bit

#endif /* ADC_ADC_C_ */
