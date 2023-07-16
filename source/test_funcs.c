/***************************************************************************************************************************
 File name: test_funcs.c
 ​Description: Principles of Embedded Systems Final Project -
 	 	 	- Contains test functions for accelerometer, temeperature, LED and I2C
 File​ ​Author​ ​Name:  Vidhya PL & Alexander G Dean
 Credits : https://github.com/alexander-g-dean/ESF
 Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 *****************************************************************************************************************************
 */

/*Including all other necessary header files*/
#include "test_funcs.h"

/*Declaring the MACROs*/
#define DUTY_CYCLE (0xFF)
#define HIGH (1)
#define LOW (0)
#define X_REF (100)	   //X axis reference value when did self test with the on board accelerometer sensor
#define Y_REF (200)	   //Y axis reference value when did self test with the on board accelerometer sensor
#define Z_REF (1700)   //Z axis reference value when did self test with the on board accelerometer sensor
#define CHANNEL (26)
#define MIN_TEMP (0)
#define MAX_TEMP (70)  //From data sheet of KL25Z
#define MIN_DELAY (2)
#define MAX_DELAY (3)
#define DELAY_100 (10)
#define LOOP_VAR (10)
#define INITIAL (0)

/*Declaring Global Variables*/
int16_t local_x;
int16_t local_y;
int16_t local_z;
int total_in_x = INITIAL;
int total_in_y = INITIAL;
int total_in_z = INITIAL;

/*Private function declarations*/
static void accelerometer_mode(int mode);

/*----------------------------------------------------------------------------
void led_test_func()
 *@brief : Test suite for testing LED Function
 *
 *Parameters : none
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void led_test_func()
{
	printf("Running Test Function for LED \n\r");
	// Loop to test the LED with varying duty cycle for red color
	for (int i = INITIAL; i<DUTY_CYCLE; i+=0x10)
	{
		LED_testing(i,INITIAL,INITIAL); // Set LED with duty cycle for red color
		delay_func(MAX_DELAY); // Wait for some time
	}
	delay_func(DELAY_100); // Wait for some time before next loop

// Loop to test the LED with varying duty cycle for green color
	for (int i = INITIAL; i<DUTY_CYCLE; i+=0x10)
	{
		LED_testing(INITIAL,i,INITIAL); // Set LED with duty cycle for green color
		delay_func(MAX_DELAY);
	}
	delay_func(DELAY_100);

// Loop to test the LED with varying duty cycle for blue color
	for (int i = INITIAL; i<DUTY_CYCLE; i+=0x10)
	{
		LED_testing(INITIAL,INITIAL,i); // Set LED with duty cycle for blue color
		delay_func(MAX_DELAY);
	}
	delay_func(DELAY_100);

	// Loop to test the LED with varying duty cycle for red and green color
	for (int i = INITIAL; i<DUTY_CYCLE; i+=0x10)
	{
		LED_testing(i,i,0); // Set LED with duty cycle for red and green color
		delay_func(MAX_DELAY);
	}
	delay_func(DELAY_100);

// Loop to test the LED with varying duty cycle for green and blue color
	for (int i = INITIAL; i<DUTY_CYCLE; i+=0x10)
	{
		LED_testing(INITIAL,i,i);  // Set LED with duty cycle for green and blue color
		delay_func(MAX_DELAY);
	}
	delay_func(DELAY_100);

// Loop to test the LED with varying duty cycle for red and blue color
	for (int i = INITIAL; i<DUTY_CYCLE; i+=0x10)
	{
		LED_testing(i,INITIAL,i); // Set LED with duty cycle for red and blue color
		delay_func(MAX_DELAY);
	}
	delay_func(DELAY_100);

// Loop to test the LED with varying duty cycle for all three colors
	for (int i = INITIAL; i<DUTY_CYCLE; i+=0x10)
	{
		LED_testing(i,i,i); // Set LED with duty cycle for all three colors
		delay_func(MAX_DELAY);
	}
	delay_func(DELAY_100);

printf("The RGB LED was tested SUCCESSFULLY by changing the PWM signal\n\r");
printf("\r\n");
}

/*----------------------------------------------------------------------------
void accelerometer_test_func()
 *@brief : Test suite for testing accelerometer Function
 *
 *Parameters : none
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void accelerometer_test_func()
{
	printf("Running Test Function for accelerometer \n\r");
	int x_axis[15];
	int y_axis[15];
	int z_axis[15];

// Get initial accelerometer readings
	calculate_axes();
	local_x = get_x_axis();
	local_y = get_y_axis();
	local_z = get_z_axis();

// Collect accelerometer data
	for(int i=0;i<LOOP_VAR;i++)
	{
	// Set accelerometer mode to high
		accelerometer_mode(HIGH);
		// Read accelerometer axes
		calculate_axes();
		local_x = get_x_axis();
		local_y = get_y_axis();
		local_z = get_z_axis();
		x_axis[i]=local_x;
		y_axis[i]=local_y;
		z_axis[i]=local_z;

// Set accelerometer mode to low
		accelerometer_mode(LOW);
		// Read accelerometer axes
		calculate_axes();
		local_x = get_x_axis();
		local_y = get_y_axis();
		local_z = get_z_axis();
		x_axis[i]-=local_x;
		y_axis[i]-=local_y;
		z_axis[i]-=local_z;

// Add up the accelerometer data
		total_in_x += x_axis[i];
		total_in_y += y_axis[i];
		total_in_z += z_axis[i];
	}
	// Check if the accelerometer is working correctly
	if((total_in_x/LOOP_VAR > X_REF) && (total_in_y/LOOP_VAR > Y_REF) && (total_in_z/LOOP_VAR > Z_REF))
	{
		printf("Successfully tested Accelerometer!\n\r");
		printf("\r\n");
	}
	else
	{
		printf("FAILED to verify Accelerometer \n\r");
	}
}


/*----------------------------------------------------------------------------
static void accelerometer_mode(int input)
 *@brief : Function to set the accelerometer mode
 *
 *Parameters : input : mode
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
static void accelerometer_mode(int input)
{
// If input is HIGH, set the accelerometer to high power mode
	if(input == HIGH)
	{
	// Write 0x00 to REG_CTRL1
		i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x00);
		delay_func(MIN_DELAY);
		// Write 0x80 to REG_CTRL2
		i2c_write_byte(MMA_ADDR, REG_CTRL2, 0x80);
		delay_func(MIN_DELAY);
		// Write 0x01 to REG_CTRL1
		i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
		delay_func(MIN_DELAY);
	}
	// If input is LOW, set the accelerometer to low power mode
	else if(input == LOW)
	{
	// Write 0x00 to REG_CTRL1
		i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x00);
		delay_func(MIN_DELAY);
		// Write 0x00 to REG_CTRL2
		i2c_write_byte(MMA_ADDR, REG_CTRL2, 0x00);
		delay_func(MIN_DELAY);
		// Write 0x01 to REG_CTRL1
		i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
		delay_func(MIN_DELAY);
	}

}

/*----------------------------------------------------------------------------
void I2C_test_func()
 *@brief : Test suite for testing I2C Function
 *
 *Parameters : none
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void I2C_test_func()
{
	printf("Running Test for I2C\n\r");
	if(i2c_read_byte(MMA_ADDR, REG_WHOAMI) == WHOAMI)  //Checking if the WHO AM I register is read properly
	{
		printf("Successfully tested I2C!\n\r");
		printf("Successfully Initialized I2C!\n\r");
		printf("\r\n");
	}
	else
	{
	printf("Failed to Initialize I2C");
	}
}

/*----------------------------------------------------------------------------
void Temperature_test_func()
 *@brief : Test suite for testing Temperature Function
 *
 *Parameters : none
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void Temperature_test_func()
{
	printf("Running Test Function for Temperature sensor \n\r");
	//Checking if the temeperature is within the valid range
	if ((adc_read(CHANNEL) < MAX_TEMP) && (adc_read(CHANNEL) > MIN_TEMP))
	{
	printf("Successfully tested Temperature Sensor!\n\r");
	}
	else
	{
	printf("Failed to test Temperature sensor");
	}
}
