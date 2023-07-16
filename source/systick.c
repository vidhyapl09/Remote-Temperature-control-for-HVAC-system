/***************************************************************************************************************************
 File name: Systick.c
 ​Description: Principles of Embedded Systems Final Project -
 	 	 	 Systick.c - Code that initializes the Systick timer and calls the Systick handler
 File​ ​Author​ ​Name: Vidhya PL
 Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso

  Credits: https://github.com/alexander-g-dean/ESF
 *****************************************************************************************************************************
 */

/*Including all the necessary header files*/
#include "systick.h"
#include "MKL25Z4.h"
//#include "log.h"

#define zero (0)
#define load (48000L)
#define sixteen (16)
#define three (0)

/*Declaring global variables*/
int num= zero;
int now_num = zero;

/*---------------------------------------------------------------------------------------
* Init_SysTick(void)
* Function to initialize the Systick Timer.
*
*Parameters : Takes no parameter as input
*
*Return : Returns nothing as it is a void function
*---------------------------------------------------------------------------------------*/
void Init_SysTick(void)
{
	SysTick-> LOAD = (load / sixteen);
	NVIC_SetPriority (SysTick_IRQn, three);
	SysTick -> VAL = three;
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk| SysTick_CTRL_ENABLE_Msk;
}

/*---------------------------------------------------------------------------------------
* SysTick_Handler()
* handler function when Systick timer overflowss.
*
*Parameters : Takes no parameter as input
*
*Return : Returns nothing as it is a void function
*---------------------------------------------------------------------------------------*/
void SysTick_Handler()
{
	num++;
	now_num++;
}

/*---------------------------------------------------------------------------------------
* now_time()
* Function used to find the time from start
*
*Parameters : Takes no parameter as input
*
*Return : int now_num
*---------------------------------------------------------------------------------------*/
int now_time()
{
	return now_num;
}


/*---------------------------------------------------------------------------------------
* reset_timer()
* Function to reset the timer back to zero
*
*Parameters : Takes no parameter as input
*
*Return : int num
*---------------------------------------------------------------------------------------*/
void reset_timer()
{
	num = zero ;
}

/*---------------------------------------------------------------------------------------
* delay_func()
* Function to create a delay for required number of milli seconds
*
*Parameters : Takes no parameter as input
*
*---------------------------------------------------------------------------------------*/
int delay_func(int i)
{
	reset_timer();
	while( num < i)
	{;}
	return 0;
}
