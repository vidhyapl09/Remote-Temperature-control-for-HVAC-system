/***************************************************************************************************************************
 File name: PWM.h
 ​Description: Principles of Embedded Systems Final Project -
 Header file of PWM.c
 File​ ​Author​ ​Name: Alexander G Dean
 Modified by :  Vidhya PL
 Credits : https://github.com/alexander-g-dean/ESF
 Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 *****************************************************************************************************************************
 */

#ifndef _PWM_H_
#define _PWM_H_

/*Library Files*/
#include <MKL25Z4.H>

/* Function Prototypes*/
void initPWM(void);
void setMotorSpeed(float speed);

#endif /*_PWM_H_*/
