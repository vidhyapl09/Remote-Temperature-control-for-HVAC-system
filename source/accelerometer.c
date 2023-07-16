/***************************************************************************************************************************
 File name: accelerometer.c
 ​Description: Principles of Embedded Systems Final Project -
 - Contains function to initialize accelerometer, detect tilt and and get the current accelerometer readings
 File​ ​Author​ ​Name: Alexander G Dean
 Modified by :  Vidhya PL
 Credits : https://github.com/alexander-g-dean/ESF
 Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 *****************************************************************************************************************************
 */

/*Including all other necessary header files*/
#include "i2c.h"
#include "accelerometer.h"
#include "UART.h"

/*Declaring the MACROs*/
#define ERROR (-1)
#define LEFT_TILT (0)
#define RIGHT_TILT (1)
#define INITIAL_VAL (0)
#define DATA_SIZE (6)
#define TEMP_SIZE (3)
#define BYTE_SIZE (5)
#define LAST_BYTE (3)
#define ALIGN_BYTE (2)
#define TOTAL_BYTE (8)
#define ONE (1)

#define REG_XHI 				0x01
#define REG_XLO 				0x02
#define REG_YHI 				0x03
#define REG_YLO					0x04
#define REG_ZHI					0x05
#define REG_ZLO 				0x06
#define REG_CTRL4  				0x2D
#define CTRL_REG1_ACTIVE		0x01
#define COUNTS_PER_G 			(4096.0)
#define M_PI 					(3.14159265)
#define INIT_ACC (0x01)

/*Declaring Global Variables*/
int16_t acc_X = INITIAL_VAL;
int16_t acc_Y = INITIAL_VAL;
int16_t acc_Z = INITIAL_VAL;

/*Private function declarations*/

/*----------------------------------------------------------------------------
 int init_accelerometer()
 *@brief : this function is called to initialize accelerometer
 *
 *Parameters : none
 *
 *Return : Returns 1
 *
 *----------------------------------------------------------------------------*/
int init_accelerometer()
{
	//set active mode, 14 bit samples and 800 Hz ODR
	i2c_write_byte(MMA_ADDR, REG_CTRL1, INIT_ACC); //Initializing the MMA sensor
	return 1;
}

/*----------------------------------------------------------------------------
 void calculate_axes()
 *@brief : Calculates the x, y and z axes of the accelerometer
 *
 *Parameters : none
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void calculate_axes()
{
	int i;
	uint8_t data[DATA_SIZE];
	int16_t temp[TEMP_SIZE];

	i2c_start();
	i2c_read_setup(MMA_ADDR, REG_XHI);

	// Read five bytes in repeated mode
	for (i = INITIAL_VAL; i < BYTE_SIZE; i++) {
		data[i] = i2c_repeated_read(INITIAL_VAL);
	}
	// Read last byte ending repeated mode
	data[i] = i2c_repeated_read(1);

	for (i = INITIAL_VAL; i < LAST_BYTE; i++) {
		temp[i] = (int16_t) ((data[ALIGN_BYTE * i] << TOTAL_BYTE)
				| data[ALIGN_BYTE * i + ONE]);
	}

	// Align for 14 bits
	acc_X = temp[0] >> ALIGN_BYTE;
	acc_Y = temp[1] >> ALIGN_BYTE;
	acc_Z = temp[2] >> ALIGN_BYTE;
}

/*----------------------------------------------------------------------------
 int tilt_check()
 *@brief : this function checks if there is a right or left tilt
 *			of the KL255Z board's in-built accelerometer
 *
 *Parameters : none
 *
 *Return : Returns -1 in case of error, 0 in case of left titl,
 *			1 in case of right tilt
 *
 *----------------------------------------------------------------------------*/
int tilt_check()
{
	if ((acc_X < INITIAL_VAL) && (acc_Z < INITIAL_VAL) && (acc_Y > INITIAL_VAL)) //left tilt
			{
		return LEFT_TILT;
	} else if ((acc_Y < INITIAL_VAL) && (acc_Z < INITIAL_VAL)
			&& (acc_X < INITIAL_VAL))  //right tilt
			{
		return RIGHT_TILT;
	}
	return ERROR;
}

/*----------------------------------------------------------------------------
 void get_axes()
 *@brief : this function prints the current axes values
 *
 *Parameters : none
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void get_axes()
{
	printf("x axis value is %d\n\r", acc_X);
	printf("y axis value is %d\n\r", acc_Y);
	printf("z axis value is %d\n\r", acc_Z);
}

int16_t get_x_axis()
{
	return acc_X;
}

int16_t get_y_axis()
{
	return acc_Y;
}

int16_t get_z_axis()
{
	return acc_Z;
}

