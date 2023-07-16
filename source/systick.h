/***************************************************************************************************************************
 File name: Systick.h
 ​Description: Principles of Embedded Systems Final Project -
 	 	 	 Header file for systick.c
 File​ ​Author​ ​Name: Vidhya PL
 Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso

  Credits: https://github.com/alexander-g-dean/ESF
 *****************************************************************************************************************************
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

/*Declaring the functions from systick.c file*/
void Init_SysTick(void);
void SysTick_Handler(void);
void reset_timer();
int now_time();
int delay_func(int i);

#endif /* SYSTICK_H_ */
