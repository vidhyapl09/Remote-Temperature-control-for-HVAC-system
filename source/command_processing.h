/***************************************************************************************************************************
 File name: command_processing.h
 ​Description: Principles of Embedded Systems Final Project -
 header file of command_processing.h
 File​ ​Author​ ​Name: Vidhya PL
 Date : 4/ 9/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 Credits:
 Reused from my(Vidhya . PL) assignment 6 of PES coursework
 https://github.com/vidhyapalaniappan/PES_Assignment_6
 *****************************************************************************************************************************
 */

#ifndef _COMMAND_PROCESSING_H_
#define _COMMAND_PROCESSING_H_

/* 	LIBRARY FILES	*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "adc.h"
#include "accelerometer.h"
#include "LEDs.h"
#include "PWM.h"

/*----------------------------------------------------------------------------
 * @brief:	process command for the provided user input
 *
 * @parameters:
 *   	char *input	:  Input string provided by user
 *
 * @returns: none
 ----------------------------------------------------------------------------*/
void command_process(char *input);
void user_input();

#endif /*_COMMAND_PROCESSING_H_*/
