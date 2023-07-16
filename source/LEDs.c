/***************************************************************************************************************************
 File name: LEDs.c
 ​Description: Principles of Embedded Systems Final Project -
 Contains functions to initialize LEDs and control the RGB LED
 File​ ​Author​ ​Name: Alexander G Dean
 Modified by :  Vidhya PL
 Credits : https://github.com/alexander-g-dean/ESF
 Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 *****************************************************************************************************************************
 */

/*Including all other necessary header files*/
#include "LEDs.h"

#define LED1_POS (1)	// on port A
#define LED2_POS (2)	// on port A
#define SW1_POS (5)		// on port A
// Freedom KL25Z LEDs
#define RED_LED_POS (18)		// on port B
#define GREEN_LED_POS (19)	// on port B
#define BLUE_LED_POS (1)		// on port D
#define MAX_DUTY_CYCLE		0xFF

#define MASK(x) (1UL << (x))

/*----------------------------------------------------------------------------
 void Init_RGB_LEDs(void)
 *@brief : this function is called to initialize LED
 *
 *Parameters : none
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void Init_RGB_LEDs(void)
{
	// Enable clock to ports B and D
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	;

	// Make 3 pins GPIO
	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(1);
	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(1);
	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(1);

	// Set ports to outputs
	PTB->PDDR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
	PTD->PDDR |= MASK(BLUE_LED_POS);
}

/*----------------------------------------------------------------------------
 void Control_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on)
 *@brief : this function is used to control RGB LED
 *
 *Parameters : unsigned int red_on, unsigned int green_on, unsigned int blue_on - Values
 *				of red, green, blue LED
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void Control_RGB_LEDs(unsigned int red_on, unsigned int green_on,
		unsigned int blue_on)
{
	if (red_on)
	{
		PTB->PCOR = MASK(RED_LED_POS);
	}
	else
	{
		PTB->PSOR = MASK(RED_LED_POS);
	}
	if (green_on)
	{
		PTB->PCOR = MASK(GREEN_LED_POS);
	}
	else
	{
		PTB->PSOR = MASK(GREEN_LED_POS);
	}
	if (blue_on)
	{
		PTD->PCOR = MASK(BLUE_LED_POS);
	}
	else
	{
		PTD->PSOR = MASK(BLUE_LED_POS);
	}
}

/*----------------------------------------------------------------------------
 void LED_testing(uint32_t red, uint32_t green, uint32_t blue)
 *@brief : this function is used to control RGB LED using PWM
 *
 *Parameters : uint32_t red, uint32_t green, uint32_t blue - Values
 *				of red, green, blue LED
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void LED_testing(uint32_t red_val, uint32_t green_val, uint32_t blue_val)
{
	SIM->SCGC6 |= SIM_SCGC6_TPM2(1);
	SIM->SCGC6 |= SIM_SCGC6_TPM0(1);
	TPM2->CONTROLS[0].CnV = red_val;
	TPM2->CONTROLS[1].CnV = green_val;
	TPM0->CONTROLS[1].CnV = blue_val;
}
