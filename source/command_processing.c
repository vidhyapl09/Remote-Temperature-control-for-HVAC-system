/***************************************************************************************************************************
 File name: command_processing.c
 ​Description: Principles of Embedded Systems Final Project -
 Contains different functions to process the commands entered
 File​ ​Author​ ​Name: Vidhya PL
 Date : 4/ 9/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 Reference : PES Lecture slides
 Credits:
 Reused from my(Vidhya . PL) assignment 6 of PES coursework
 https://github.com/vidhyapalaniappan/PES_Assignment_6
 *****************************************************************************************************************************
 */

/*Files to be included	*/
#include "command_processing.h"

/*Defining MACROS here*/
#define ZERO (0)
#define ARRAY_SIZE (5)
#define ONE (1)
#define THREE (3)
#define HEX (16)
#define LEN_MAX (640)
#define NEXT_LINE (8)
#define BUFF_SIZE (80)
#define MAX_CHAR (255)
#define TEMP_CHANNEL (26)
#define INC_DUTY_CYCLE (60.0f)
#define DEC_DUTY_CYCLE (40.0f)

/*Private function declarations*/
/*----------------------------------------------------------------------------
 *static void author_func(int argc, char *argv[])
 *@brief : this function is called after the author
 *command is received, prints the name of the author
 *
 *Parameters : int argc 	: number of arguments in the command
 * 			   char** argv	: array in which commands are stored
 *
 *Return : Returns nothing as it is a Void function
 *
 *----------------------------------------------------------------------------*/
static void author_func(int argc, char *argv[]);

/*----------------------------------------------------------------------------
 * static void help_func(int argc, char *argv[])
 * @brief	:	this function is called after the help
 * 				command is received, prints a help message for user
 *
 *Parameters
 * 				int argc 	: number of arguments in the command
 * 				char** argv	: array in which commands are stored
 *
 * Return	: 	none
 ----------------------------------------------------------------------------*/
static void help_func(int argc, char *argv[]);

/*----------------------------------------------------------------------------
 *static void temp_func(int argc, char *argv[])
 * @brief	:	this function prints the current temperature value
 *
 * @params	:
 * 				int argc 	: number of arguments in the command
 * 				char** argv	: array in which commands are stored
 *
 * @returns	: 	none
 ----------------------------------------------------------------------------*/

static void temp_func(int argc, char *argv[]);

/*----------------------------------------------------------------------------
 * static void acc_func(int argc, char *argv[])
 * @brief	:	this function prints the accelerometer reading
 *
 * @params	:
 * 				int argc 	: number of arguments in the command
 * 				char** argv	: array in which commands are stored
 *
 * @returns	: 	none
 ----------------------------------------------------------------------------*/
static void acc_func(int argc, char *argv[]);

/*----------------------------------------------------------------------------
 * static void motor_control(int argc, char *argv[])
 * @brief	:	this function helps to control the motor speed
 *
 * @params	:
 * 				int argc 	: number of arguments in the command
 * 				char** argv	: array in which commands are stored
 *
 * @returns	: 	none
 ----------------------------------------------------------------------------*/
static void motor_control(int argc, char *argv[]);

/*----------------------------------------------------------------------------
 * my_printf
 * @brief	:	this function is used to print the characters using putchar
 *
 * @params	:
 * 				const char *input	: Input to be printed
 *
 * @returns	: 	none
 ----------------------------------------------------------------------------*/
static void my_printf(const char *input)
{
	int len = strlen(input);
	for (int i = ZERO; i < len; i++)
	{
		putchar(input[i]);
	}
}

/* DEFINITION OF FUNCTION POINTER TO HANDLE COMMANDS */
typedef void (*cmd_handler_t)(int, char *argv[]);

/* STRUCTURE INDICATING A COMMAND AND THEIR CHARACTERISTICS */
typedef struct
{
	const char *command;
	cmd_handler_t command_func;
	const char *func_description;
} command_lookup_table_t;

/* LOOKUP TABLE FOR AVAILABLE COMMANDS AND THEIR CHARACTERISTICS */
static command_lookup_table_t commands[] =
{
		{ "author", author_func,"Prints the name of the Author\r\n" },
		{ "help", help_func,"Print this help message\r\n" },
		{ "temp", temp_func,"Print the current temperature\r\n" },
		{ "Acc", acc_func, "Print the stack pointer\r\n" },
		{ "motor", motor_control,"Prints the Info\r\n" },
};

/*MESSAGES TO BE DISPLAYED WHEN HELP COMMAND IS CALLED*/
const char author_msg[] = "1. Author: Prints the author name\r\n\0";
const char temp_msg[] = "2. Temp: Prints the current temperature\r\n\0";
const char acc_msg[] = "3. Acc: Prints the current acceleromter \r\n\0";
const char motor_msg[] = "4. Motor: Controls the motor speed\r\n\0";
const char help_msg[] = "5. Help: Prints the help message\r\n\0";

/* GLOBAL VARIABLES */
//determine number of commands during runtime
static const int num_commands = sizeof(commands)
		/ sizeof(command_lookup_table_t);

/* process commands received from terminal */
void command_process(char *input)
{
	char *p = input;	//iterator, points to start of the input
	char *end;	//to store the end of input

	//iterate through string to find the end of string
	for (end = input; *end != '\0'; end++)
		;

	bool in_token = false;
	char *argv[ARRAY_SIZE];	//to store each word in input separately
	int argc = ZERO;	//number of words (commands/arguments) in input

	bool command_flag = false;  //Flag to check if a known command is found

	memset(argv, 0, sizeof(argv));
	for (p = input; p < end; p++)
	{
		switch (in_token) {
		//previous character was a special character
		case false:
			//check if next character is a valid alpha-numeric character
			if (((*p >= 'a') && (*p <= 'z')) || ((*p >= 'A') && (*p <= 'Z'))
					|| ((*p >= '0') && (*p <= '9')))
			{
				//if yes, next word/argument/command starts now
				argv[argc] = p;
				argc++;
				in_token = true;
			}
			//else, skip this special character
			break;

			//previous character was a valid alpha-numeric character
		case true:
			//check if next character is a special character
			if ((*p == ' ') || (*p == '\t') || (*p == '\n') || (*p == '\r'))
			{
				//if yes, complete the previous word/argument/command
				*p = '\0';
				in_token = false;
			}
			break;
		}
	}

	//finally, finish the array of words/commands
	argv[argc] = NULL;

	if (argc == ZERO) // no command
		return;

	//now iterate through array of commands to see if we have a match
	for (int i = ZERO; i < num_commands; i++)
	{
		//check the received command against the lookup table
		if (strcasecmp(argv[0], commands[i].command) == ZERO)
		{
			//valid command found, call the handler function
			commands[i].command_func(argc, argv);
			//set the flag to true
			command_flag = true;
			//command execution done, break the loop
			break;
		}
	}

	//if no command is found, we print a message indicating that
	//invalid command has been entered
	if (command_flag == false)
	{
		printf("Unknown command: ");
		//print the unknown entered commands one by one
		for (int i = ZERO; i < argc; i++)
		{
			printf("%s ", argv[i]);
		}
	}
}

/* print name of author */
static void author_func(int argc, char *argv[])
{
	//for this command to work properly
	//argc should be exactly equal to 1
	if (argc != ONE)
	{
		//if not, the format of command is invalid
		printf("Unknown command: ");
		//print the invalid command
		for (int i = ZERO; i < argc; i++)
		{
			printf("%s ", argv[i]);
		}
		return;
	}
	//valid command format, print author name
	printf("Vidhya. PL");
	printf("\r\n");
}

/* print a help message for user */
static void help_func(int argc, char *argv[])
{
	//for this command to work properly
	//argc should be exactly equal to 1
	if (argc != ONE)
	{
		//if not, the format of command is invalid
		printf("Unknown command: ");
		//print the invalid command
		for (int i = ZERO; i < argc; i++)
		{
			printf("%s ", argv[i]);
		}
		return;
	}
	//valid command format, print help command
	my_printf(author_msg);
	my_printf(temp_msg);
	my_printf(acc_msg);
	my_printf(motor_msg);
	my_printf(help_msg);
}

/* print address of top of the stack */
static void temp_func(int argc, char *argv[])
{
	//for this command to work properly
	//argc should be exactly equal to 1
	if (argc != ONE)
	{
		//if not, the format of command is invalid
		printf("Unknown command: ");
		//print the invalid command
		for (int i = ZERO; i < argc; i++)
		{
			printf("%s ", argv[i]);
		}
		return;
	}
	printf("The current temp value is %d degree Celcius \r\n",
			(int) adc_read(TEMP_CHANNEL));
	//adc_read(TEMP_CHANNEL); //Reading the temperature sensor value
	//printf("\r\n");

}

/* print hexdump of memory */
static void acc_func(int argc, char *argv[])
{
	//for this command to work properly
	//argc should be exactly equal to 3
	if (argc != ONE)
	{
		//if not, the format of command is invalid
		printf("Unknown command: ");
		//print the invalid command
		for (int i = 0; i < argc; i++)
		{
			printf("%s ", argv[i]);
		}
		printf("\r\n");
		return;
	}
	calculate_axes(); //Calculating the accelerometer axes
	get_axes();  //printing the values of x,y and z axes
}

static void motor_control(int argc, char *argv[])
{
	if (argc != ONE) {
		//if not, the format of command is invalid
		printf("Unknown command: ");
		//print the invalid command
		for (int i = ZERO; i < argc; i++)
		{
			printf("%s ", argv[i]);
		}
		return;
	}
	printf("The current temp value is %d degree Celcius \r\n", (int) adc_read(TEMP_CHANNEL));
	printf("If the temp is high, increase the motor speed and if temp is low, decrease the motor speed\r\n");
	printf("Tilt right to increase the motor speed and tilt left to decrease the motor speed\n\r");
	printf("\r\n");

	/*************************************************************************************************
	 * The logic here is, if the temperature is high, the user can decide to increased the speed of
	 * the fan (motor) by using accelerometer as a remote control module and tilting it towards right
	 * If the temperature is low, the speed of fan (motor) can be decreased by tilting
	 * the accelerometer remote towards left
	 *************************************************************************************************/
	while (1)
	{
		calculate_axes();
		if ((tilt_check()) == ZERO) //Checking if there is left tilt
		{
			printf("Left tilt detected\n\r");
			printf("Speed of motor is decreased\n\r");
			Control_RGB_LEDs(ONE, ONE, ZERO); //LED Indicating decrease in motor speed
			setMotorSpeed(DEC_DUTY_CYCLE); //Decreasing the PWM to 40% duty cycle
			break;
		} else if ((tilt_check()) == ONE) //Checking if there is right tilt
		{
			printf("right tilt detected\r\n");
			printf("Speed of motor is increased\r\n");
			Control_RGB_LEDs(ZERO, ONE, ONE); //LED Indicating increase in motor speed
			setMotorSpeed(INC_DUTY_CYCLE); //Increasing the PWM to 60% duty cycle
			break;
		}
	}
}

void user_input()
{
	uint8_t buffer[BUFF_SIZE];
	uint8_t c;
	uint8_t bp;
	while (c != 0xD) //Till Enter is pressed
	{
		c = getchar();  //Getting input from user
		if (c < MAX_CHAR) {
			if ((c != '\n') || (c != '\r')) //Checking if it is a next line or carriage return
					{
				if ((c == '\b'))		//check for backspace
				{
					if (bp == 0)
					{
						//do nothing if bp=0
						//ignore any more backspaces at this moment
					}
					else
					{
						//if backspace is present, overwrite
						bp--;
						printf("\b \b");
					}
				}

				else
				{
					buffer[bp++] = c;    //Storing the input char in buffer
					printf("%c", (char) c);

				}
			}
		}
	}
	printf("\r\n");
	buffer[bp] = '\0';  //null character to terminate the string
	bp = 0;  //Reset the buffer pointer
	command_process((char*) buffer);  //Calling the command processing function
	printf("\n\r$$ ");
	c = 0;  //clear the input character
}
