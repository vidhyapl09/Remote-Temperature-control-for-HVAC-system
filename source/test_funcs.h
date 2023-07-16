/***************************************************************************************************************************
 File name: test_funcs.h
 ​Description: Principles of Embedded Systems Final Project -
 - Header file for test_funcs.c
 File​ ​Author​ ​Name:  Vidhya PL & Alexander G Dean
 Credits : https://github.com/alexander-g-dean/ESF
 Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 *****************************************************************************************************************************
 */

#ifndef TEST_FUNCS_H_
#define TEST_FUNCS_H_

/*Library Files*/
#include <MKL25Z4.H>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "systick.h"
#include "UART.h"

#include "accelerometer.h"
#include "i2c.h"
#include "LEDs.h"
#include "adc.h"
#include "PWM.h"
#include "test_funcs.h"
#include "sysclock.h"
#include "command_processing.h"

/* Function Prototypes*/
void led_test_func();
void accelerometer_test_func();
void I2C_test_func();
void Temperature_test_func();

#endif /* TEST_FUNCS_H_ */
