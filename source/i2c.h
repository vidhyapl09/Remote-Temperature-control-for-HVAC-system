/***************************************************************************************************************************
 File name: i2c.h
 ​Description: Principles of Embedded Systems Final Project -
 - header file of i2c.c
 File​ ​Author​ ​Name: Alexander G Dean
 Modified by :  Vidhya PL
 Credits : https://github.com/alexander-g-dean/ESF
 Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 *****************************************************************************************************************************
 */

#ifndef _I2C_H_
#define _I2C_H_

/*Library Files*/
#include <MKL25Z4.H>
#include <stdint.h>

/* Function Prototypes*/
void i2c_init(void);
void i2c_start(void);
void i2c_read_setup(uint8_t dev, uint8_t address);
uint8_t i2c_repeated_read(uint8_t);
uint8_t i2c_read_byte(uint8_t dev, uint8_t address);
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);

#endif /* _I2C_H_ */
