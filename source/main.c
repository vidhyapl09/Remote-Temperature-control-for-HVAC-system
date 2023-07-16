/***************************************************************************************************************************
 File name: main.c
 ​Description: Principles of Embedded Systems Final Project -
 main.c file which calls all the necessary initialization functions and the user input function
 File​ ​Author​ ​Name: Vidhya PL
 Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 *****************************************************************************************************************************
 */

/*Library Files*/
#include <MKL25Z4.H>
#include <stdio.h>

/*Including all other necessary header files*/
#include "UART.h"
#include "sysclock.h"
#include "command_processing.h"
#include "accelerometer.h"
#include "i2c.h"
#include "LEDs.h"
#include "adc.h"
#include "PWM.h"
#include "test_funcs.h"

/*Declaring the MACROs*/
#define BAUD_RATE_VALUE (115200)
#define ON (1)
#define OFF (0)

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(void)
{
	Init_SysTick();
	Init_RGB_LEDs();   					//Initializing the LEDs
	sysclock_init();					//Initializing the sysclock
	Init_UART0(BAUD_RATE_VALUE); 		//Initializing the UART
	i2c_init();  						//Initializing the I2C
	initPWM();  						//Initializing the PWM
	init_ADC(); 						//Initializing the ADC

	/*Calling all the Test Functions*/
	led_test_func();
	I2C_test_func();
	accelerometer_test_func();
	Temperature_test_func();

	if (!init_accelerometer())   		//Initializing the accelerometer
	{
		Control_RGB_LEDs(ON, OFF, OFF);  //Red LED on indicating Error
		while (1)
			;                		 //Unable to initial accelerometer
	}

	Control_RGB_LEDs(OFF, ON, OFF);	//Green LED on indicating successful initialization of accelerometer
	printf("\n\rPES Final Project!\n\r");
	printf("Type 'help' to know the menu options and proceed further\n\r");
	printf("$$ ");

	while (1)
	{
		user_input();    			//Getting input from user to process command
	}
	return 0;
}

