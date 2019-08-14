/*
 * i2c.h
 *
 *  Created on: 06.06.2019
 *      Author: danielschubert
 */

#ifndef I2C_I2C_H_
#define I2C_I2C_H_

#define SLAVE_PCF8574T      0x26            // PCF8574T Slave-Adresse 010 0110 ohne R/W bit;  Hardware shiftet die Adresse automatisch um 1bit nach links um das R/W-Bit anzuhängen
#define SLAVE_LM75          0x4E            // LM75     Slave-Adresse 100 1110 ohne R/W bit
#define MAX_LENGHT          0x05
#define HIGH                1
#define LOW                 0


/***********************************************
 * Variables
 ***********************************************/


uint8_t transmitData[MAX_LENGHT];
uint8_t receivedData[10];
uint16_t indexTransmitData;
uint16_t indexReceiveData;
uint8_t transmitChar;
uint8_t transmitChar2;
uint16_t command_slaveAddressSet;
uint16_t command_NACK;
uint16_t commandRepeatedStart;

uint16_t temperature;
uint16_t buffer;



/***********************************************
 * Prototypes
 ***********************************************/
void i2c_init(void);
//void stop_receive_i2c(void);
void i2c_master_send(uint16_t, uint8_t, uint16_t);
void i2c_master_receive(uint16_t, uint8_t*, uint16_t);


#endif /* I2C_I2C_H_ */
