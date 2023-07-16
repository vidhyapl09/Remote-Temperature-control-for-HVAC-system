/***************************************************************************************************************************
 File name: adc.h
 ​Description: Principles of Embedded Systems Final Project -
 header file of adc.c
 File​ ​Author​ ​Name: Vidhya PL
 Date : 5/ 4/ 2023
 Credits : https://learningmicro.wordpress.com/using-in-built-temperature-sensor-of-kl25z-mcu/
 Credits :  Brainstormed with Isha Burange
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 *****************************************************************************************************************************
 */

#ifndef _ADC_H_
#define _ADC_H_

/*Library Files*/
#include <MKL25Z4.H>
#include <stdio.h>

/* Function Prototypes*/
void init_ADC(void);
uint16_t adc_read(uint8_t ch);

#endif /*_ADC_H_*/
