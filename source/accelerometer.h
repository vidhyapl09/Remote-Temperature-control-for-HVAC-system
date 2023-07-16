/***************************************************************************************************************************
 File name: accelerometer.h
 ​Description: Principles of Embedded Systems Final Project -
 header file for accelerometer.c
 File​ ​Author​ ​Name: Alexander G Dean
 Modified by :  Vidhya PL
 Credits : https://github.com/alexander-g-dean/ESF
 Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 *****************************************************************************************************************************
 */

#ifndef _ACCELEROMETER_H_
#define _ACCELEROMETER_H_

/*Library Files*/
#include <math.h>
#include <stdio.h>
#include <MKL25Z4.H>
#include <stdint.h>

/*Declaring MACROs here which are exposed to other files*/
#define MMA_ADDR 				0x3A
#define REG_CTRL1  				0x2A
#define REG_WHOAMI 				0x0D
#define REG_CTRL2  				0x2B
#define WHOAMI 					0x1A

/* Function Prototypes*/
int init_accelerometer(void);
void calculate_axes(void);
int tilt_check();
void get_axes();
int16_t get_x_axis();
int16_t get_y_axis();
int16_t get_z_axis();

#endif /*_ACCELEROMETER_H_*/
