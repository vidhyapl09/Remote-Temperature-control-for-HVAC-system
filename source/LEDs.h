/***************************************************************************************************************************
 File name: LEDs.h
 ​Description: Principles of Embedded Systems Final Project -
 Contains header file of LEDs.c
 File​ ​Author​ ​Name: Alexander G Dean
 Modified by :  Vidhya PL
 Credits : https://github.com/alexander-g-dean/ESF
 Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 *****************************************************************************************************************************
 */

#ifndef LEDS_H
#define LEDS_H

/*Library Files*/
#include <MKL25Z4.H>

/* function prototypes*/
void Init_RGB_LEDs(void);
void Control_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on);
void LED_testing(uint32_t red_val, uint32_t green_val, uint32_t blue_val);
#endif /*LEDS_H*/
