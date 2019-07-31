/*
 * adc.h
 *
 *  Created on: 20.05.2019
 *      Author: danielschubert
 */

#ifndef ADC_ADC_H_
#define ADC_ADC_H_

#define     ADC_VALUE       4095                    // auflösung 12 bit adc
#define     VOLTAGE_REF     2500                    // Referenzspannung VRef
#define     ADC_SUM_AVERAGE   50                    // zählervariable für durchschnittsberechnung

uint16_t command_konsolenEingabe;                   // ist True sobald korrekte Eingabe erhalten wurde
uint16_t command_convertAdc;
uint16_t command_voltageAverage;                    // gibt an ob durchschnittswert berechnet wurde
uint16_t command_average;
uint32_t voltageTransmit;

int voltage_result(void);
void adc_init(void);
int voltage_change(uint16_t voltage1, uint16_t voltage2);
void start_conversion(void);
//void stop_conversion(void);
void voltage_average(void);
int voltage_input(void);


#endif /* ADC_ADC_H_ */
