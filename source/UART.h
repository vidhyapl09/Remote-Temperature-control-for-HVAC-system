/***************************************************************************************************************************
 File name: UART.h
 ​Description: Principles of Embedded Systems Final Project -
 header file of UART.c
 File​ ​Author​ ​Name: Vidhya PL, Alexander G. Dean
 Credits : Reused from my(Vidhya . PL) assignment 6 of PES coursework
 	 	   https://github.com/alexander-g-dean/ESF
 	 	   https://github.com/vidhyapalaniappan/PES_Assignment_6
 Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 *****************************************************************************************************************************
 */

#ifndef UART_H
#define UART_H

/*Library Files*/
#include <stdint.h>
#include <MKL25Z4.H>
#include <stdio.h>
#include "llfifo.h"


/* function prototypes*/
void Init_UART0(uint32_t baud_rate);
void UART0_Transmit_Poll(uint8_t data);
uint8_t UART0_Receive_Poll(void);
void Send_String_Poll(uint8_t *str);
void Send_String(uint8_t *str);
uint32_t Rx_Chars_Available(void);
uint8_t Get_Rx_Char(void);

#endif /*UART_H_*/

