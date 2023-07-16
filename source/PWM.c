/***************************************************************************************************************************
 File name: PWM.c
 ​Description: Principles of Embedded Systems Final Project -
 Contains functions to initialize PWM and to control the speed of motor
 File​ ​Author​ ​Name: Alexander G Dean
 Modified by :  Vidhya PL
 Credits : https://github.com/alexander-g-dean/ESF
 Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 *****************************************************************************************************************************
 */

/*Including all other necessary header files*/
#include "PWM.h"

/*Declaring MACROS here*/
#define PWM_PERIOD (12000)  // PWM period in clock cycles
#define MOTOR_PWM_PIN (2)   // PWM output pin B2
#define PWM_MODE (3)
#define ZERO (0)
#define ONE (1)
#define FULL (100.0f)

/*----------------------------------------------------------------------------
 void initPWM(void)
 *@brief : Initializes the PWM signal
 *
 *Parameters : none
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void initPWM(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;     // Enable clock for PORTB
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;      // Enable clock for TPM0
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(ONE);      // Select MCGFLLCLK as TPM source
	PORTB->PCR[MOTOR_PWM_PIN] |= PORT_PCR_MUX(PWM_MODE);  // Set pin to PWM mode
	TPM0->MOD = PWM_PERIOD - ONE;             // Set PWM period
	TPM0->SC = TPM_SC_PS(ZERO) | TPM_SC_CMOD(ONE); // Set TPM prescaler and clock mode
	TPM0->CONTROLS[2].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK; // Set PWM mode and pulse high on match
	TPM0->CONTROLS[2].CnV = ZERO;              // Set initial duty cycle to 0%
}

/*----------------------------------------------------------------------------
 void setMotorSpeed(float speed)
 *@brief : Function to control the speed of the motor by modifying the PWM duty cycle
 *
 *Parameters : float speed : required speed
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void setMotorSpeed(float speed)
{
	float dutyCycle = speed / FULL * (float) PWM_PERIOD;
	TPM0->CONTROLS[2].CnV = (uint16_t) dutyCycle;  // Set duty cycle
}
