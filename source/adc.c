/***************************************************************************************************************************
 File name: adc.c
 ​Description: Principles of Embedded Systems Final Project -
 Function to initialize ADC and to read temperature values
 File​ ​Author​ ​Name: Vidhya PL
 Date : 5/ 4/ 2023
 Credits : https://learningmicro.wordpress.com/using-in-built-temperature-sensor-of-kl25z-mcu/
 Credits :  Brainstormed with Isha Burange
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 *****************************************************************************************************************************
 */

/*Including all other necessary header files*/
#include "adc.h"

/*Declaring the MACROs*/
#define INITIAL_VAL (0)
#define DIV (3)
#define MODE (2)
#define TEMP_OFFSET (34)  //Calculated based on my testing with temp sensor
#define ROOM_TEMP (25)
#define VOLT ( 0.0029296875)
#define COLD (0.001646)
#define HOT (0.001749)
#define SLOPE (0.7012)

/*Private function declarations*/

/*----------------------------------------------------------------------------
 void init_ADC(void)
 *@brief : this function is called to initialize the ADC
 *
 *Parameters : none
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void init_ADC(void)
{
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
	ADC0->CFG1 = INITIAL_VAL; // Reset register
	ADC0->CFG1 = ADC_CFG1_ADICLK(INITIAL_VAL) | ADC_CFG1_ADLPC_MASK |
	ADC_CFG1_ADIV(DIV) | ADC_CFG1_MODE(MODE) | ADC_CFG1_ADLSMP_MASK;
}

/*----------------------------------------------------------------------------
 uint16_t adc_read(uint8_t ch)
 *@brief : this function used to read the temperature sensor values
 *
 *Parameters : input channel
 *
 *Return : current temp value
 *
 *----------------------------------------------------------------------------*/
uint16_t adc_read(uint8_t ch)
{
	// Write to SC1A to start conversion
	ADC0->SC1[INITIAL_VAL] =
			((ch & ADC_SC1_ADCH_MASK)
					| (ADC0->SC1[INITIAL_VAL]
							& (ADC_SC1_AIEN_MASK | ADC_SC1_DIFF_MASK)));

	while (!(ADC0->SC1[INITIAL_VAL] & ADC_SC1_COCO_MASK))
		; // Run until the conversion is complete

	float Vtemp = (float) ADC0->R[INITIAL_VAL];
	float Temp1;
	Vtemp = Vtemp * VOLT;  //Converting to voltage
	if (Vtemp >= SLOPE)  //Checking if it is hot or cold slope
	{
		Temp1 = ROOM_TEMP - ((Vtemp - SLOPE) / COLD);  //Value for Cold slope
	}
	else
	{
		Temp1 = ROOM_TEMP - ((Vtemp - SLOPE) / HOT);  //Value for Hot slope
	}
	return Temp1 - TEMP_OFFSET;
}

