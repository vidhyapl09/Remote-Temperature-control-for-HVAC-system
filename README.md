# FINAL PROJECT 

# MOTOR SPEED CONTROL FOR HVAC SYSTEMS USING ACCELEROMETER AND TEMPERATURE SENSORS

The objective of this project is to design and implement a HVAC system control by motor speed control using an accelerometer and temperature sensors. The system will be able to control the speed of a fan motor based on the tilt angle and temperature of the environment to maintain the desired airflow and temperature in the building while minimizing energy consumption. 

The system consists of a KL25Z board, a DC fan motor, an accelerometer sensor, a temperature sensor, and a motor driver circuit. The accelerometer sensor (MMA8451 - on board) is used to measure the tilt angle of the board and convert it into a digital signal. The temperature sensor (on board) is used to measure the temperature of the environment and convert it into a digital signal. The KL25Z board reads these digital signals and uses them to control the speed of the DC fan motor through the motor driver circuit. This program uses the analog input pins on the KL25Z board to read the accelerometer and temperature sensor data, and then use a PID control algorithm to adjust the fan speed based on the tilt angle and temperature.

A command line process is also implemented which has the following options:
- Author : Displays  the name of the author
- Acc : Displays the current accelerometer reading
- Temp : Displays the current temperature value
- Help : Displays the menu command
- Motor :  Helps to control the motor speed

Motor control function: When the motor control function is selected, the current temperature is first displayed. IF the user feels the current temperature to be high, the KL25Z board should be tilted towards rightwhich will turn on the blue LED and will also increase the motor speed. As a result, the fan will run at a higher speed thereby reducing the surrounding temperature. If the user finds the temperature to be low, the board should be tilted towards left. As a result, the fan will run at a slower speed. Here the board acts a remote control with the help of the accelerometer sensor. 

Test functions were written to test the robustness of the system. The functionality of LED and I2C were tested. The fuctionality of accelerometer module was also tested with a test function. The temperature sensor has a seperate test function apart from which manual testing was also done for temeprtaure sensor where it was tested in different environment and obtained values where verified with the standard values.


## Author

Vidhya Palaniappan - contact: vipa4058@colorado.edu

## Requirements

  * mcuXpresso

## Files included

```
main.c, command_processing.c, command_processing.h, llfifo.c, llfifo.h, sysclock.c, sysclock.h, UART.c, UART.h, accelerometer.c, accelerometer.h,  adc.c, adc.h,
 i2c.c, i2c.h, LEDs.c, LEDs.h, PWM.c, PWM.h, systick.c, systick.h, test_funcs.c, test_funcs.h

```


## Functionality of the Files

main.c - main.c file which calls all the necessary initialization functions and the user input function

command_processing.h -   header file of command_processing.h  

command_processing.c - Contains different functions to process the commands entered  
 
llfifo.h -  header file of llfifo.c

llfifo.c -  Functions to create, enqueue, dequeue, destroy, find length and capacity of LLfifo

sysclock.c - configuration routines for KL25Z system clock

sysclock.h - header file of sysclock.c

UART.h -   header file of UART.c
  
UART.c - Contains different functions for UART processing

accelerometer.c - Contains function to initialize accelerometer, detect tilt and and get the current accelerometer readings

accelerometer.h - header file for accelerometer.c

adc.c -  Function to initialize ADC and to read temperature values

adc.h - header file of adc.c

i2c.c - Contains function to initialize i2c, to write, read through i2c and other functions related to i2c

i2c.h - header file of i2c.c

LEDs.c -  Contains functions to initialize LEDs and control the RGB LED

LEDs.h - Contains header file of LEDs.c

PWM.c Contains functions to initialize PWM and to control the speed of motor

PWM.h - Header file of PWM.c

systick.c - Code that initializes the Systick timer and calls the Systick handler

systick.h -  Header file for systick.c

test_funcs.c - Contains test functions for accelerometer, temeperature, LED and I2C

test_funcs.h -  Header file for test_funcs.c


## Tools​ ​used​ ​to​ ​process​ ​the​ ​code​

```
mcuXpresso
```

## Build and Compile

The following steps are followed to compile all the files

```
- add all the files in the same project

-Check if the optimization is set to -O0

-Build in debug mode

-Set -Wall and -Werror

- First input help command to see all the available function

- Input motor function: Raise the board little above the surface and tilt it towards right to increase motor speed. 
  Again input motor command in UART and tilt board towards left to decrease the speed.

```

## REFERENCES
- PES Class slides
- https://github.com/alexander-g-dean/ESF
- https://learningmicro.wordpress.com/using-in-built-temperature-sensor-of-kl25z-mcu/
- Credits :
-  Alexandar G. Dean
-  Glue logic idea brain storming credit to Visweshwaran Baskharan
-  Temperature Sensor ADC read brain stormed with Isha Burange.
-  UART initialization : Daanish Sharif
-  UART, command processor - Vidhya. PL - PES assignment 6


## SCREEN SHOTS 
# Terminal parameters
![image](https://user-images.githubusercontent.com/111988668/230824815-95f218c5-e4de-4693-a9fe-529d7437bb07.png)

# Interactive terminal session
![image](https://user-images.githubusercontent.com/111988668/236396777-b475ec1b-728a-42f0-b632-17e6352c09cf.png)

## DEMO VIDEO
https://drive.google.com/drive/folders/1uH8Dn6LMyyoDCtfiDX42hFr-0IbT5iS5?usp=share_link

## REPO

[REPO_LINK](https://github.com/ECEN5813/final-project-vidhyapalaniappan/tree/main)

