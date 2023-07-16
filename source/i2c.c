/***************************************************************************************************************************
 File name: i2c.c
 ​Description: Principles of Embedded Systems Final Project -
 - Contains function to initialize i2c, to write, read through i2c and other functions related to i2c
 File​ ​Author​ ​Name: Alexander G Dean
 Modified by :  Vidhya PL
 Credits : https://github.com/alexander-g-dean/ESF
 Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 *****************************************************************************************************************************
 */

/*Including all other necessary header files*/
#include "i2c.h"

/* Defining MACROS here	*/
#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP  	I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART 	I2C0->C1 |= I2C_C1_RSTA_MASK

#define I2C_TRAN		I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_REC			I2C0->C1 &= ~I2C_C1_TX_MASK

#define BUSY_ACK 	    while(I2C0->S & 0x01)
#define TRANS_COMP		while(!(I2C0->S & 0x80))
#define I2C_WAIT 		i2c_wait();

#define NACK 	        I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK           	I2C0->C1 &= ~I2C_C1_TXAK_MASK

#define INITIAL (0)
#define WAIT_TIME (200)
#define PIN_1 (24)
#define PIN_2 (25)
#define MUX_PIN (5)
#define LOCK (1)

/*Declaring Global Variables*/
int lock_detect = INITIAL;
int i2c_lock = INITIAL;

/*Private function declarations*/

/*----------------------------------------------------------------------------
 void i2c_init(void)
 *@brief : this function is called to initialize I2C
 *
 *Parameters : none
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/

void i2c_init(void)
{
	//clock i2c peripheral and port E
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= (SIM_SCGC5_PORTE_MASK);

	//set pins to I2C function
	PORTE->PCR[PIN_1] |= PORT_PCR_MUX(MUX_PIN);
	PORTE->PCR[PIN_2] |= PORT_PCR_MUX(MUX_PIN);

	//set to 100k baud
	//baud = bus freq/(scl_div+mul)
	//~400k = 24M/(64); icr=0x12 sets scl_div to 64

	I2C0->F = (I2C_F_ICR(0x10) | I2C_F_MULT(INITIAL));

	//enable i2c and set to master mode
	I2C0->C1 |= (I2C_C1_IICEN_MASK);

	// Select high drive mode
	I2C0->C2 |= (I2C_C2_HDRS_MASK);
}

/*----------------------------------------------------------------------------
 void i2c_busy(void)
 *@brief : this function is used to determine if I2C is busy
 *
 *Parameters : none
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void i2c_busy(void)
{
	// Start Signal
	lock_detect = INITIAL;
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C_TRAN;
	I2C_M_START;
	I2C0->C1 |= I2C_C1_IICEN_MASK;
	// Write to clear line
	I2C0->C1 |= I2C_C1_MST_MASK; 			//set MASTER mode
	I2C0->C1 |= I2C_C1_TX_MASK; 			//Set transmit (TX) mode
	I2C0->D = 0xFF;
	while ((I2C0->S & I2C_S_IICIF_MASK) == 0U)
		;						//wait for interrupt
	I2C0->S |= I2C_S_IICIF_MASK; 			//clear interrupt bit
	I2C0->S |= I2C_S_ARBL_MASK;				//Clear arbitration error flag
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;			//Send start
	I2C0->C1 |= I2C_C1_TX_MASK; 			//Set transmit (TX) mode
	I2C0->C1 |= I2C_C1_MST_MASK; 			//START signal generated
	I2C0->C1 |= I2C_C1_IICEN_MASK;
	//Wait until start is send
	//Send stop
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;
	I2C0->C1 &= ~I2C_C1_MST_MASK; 			//set SLAVE mode
	I2C0->C1 &= ~I2C_C1_TX_MASK; 			//Set Rx
	I2C0->C1 |= I2C_C1_IICEN_MASK;
	//wait
	//Clear arbitration error & interrupt flag
	I2C0->S |= I2C_S_IICIF_MASK;
	I2C0->S |= I2C_S_ARBL_MASK;
	lock_detect = INITIAL;
	i2c_lock = LOCK;
}

/*----------------------------------------------------------------------------
 void i2c_wait(void)
 *@brief : this function is used make I2C wait till transmission is over
 *
 *Parameters : none
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void i2c_wait(void)
{
	lock_detect = INITIAL;
	while (((I2C0->S & I2C_S_IICIF_MASK) == INITIAL) & (lock_detect < WAIT_TIME)) {
		lock_detect++;
	}
	if (lock_detect >= WAIT_TIME)
		i2c_busy();
	I2C0->S |= I2C_S_IICIF_MASK;
}

/*----------------------------------------------------------------------------
 void i2c_start()
 *@brief : this function is used start the I2C
 *
 *Parameters : none
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void i2c_start()
{
	//send start sequence
	I2C_TRAN;							//set to transmit mode
	I2C_M_START;						//send start
}

/*----------------------------------------------------------------------------
 void i2c_start()
 *@brief : this function is used read bytes
 *
 *Parameters : uint8_t dev:  Device address
 *			   uint8_t address : Read address
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void i2c_read_setup(uint8_t dev, uint8_t address)
{
	I2C0->D = dev;			  			//send dev address
	I2C_WAIT
	//wait for completion

	I2C0->D = address;					//send read address
	I2C_WAIT
	//wait for completion

	I2C_M_RSTART;				   		//repeated start
	I2C0->D = (dev | 0x1);	 			//send dev address (read)
	I2C_WAIT
	//wait for completion

	I2C_REC;						   	//set to receive mode

}

/*----------------------------------------------------------------------------
 uint8_t i2c_repeated_read(uint8_t isLastRead)
 *@brief : this function is used read bytes and ack/nack as appropriate
 *
 *Parameters : uint8_t isLastRead : last read data
 *
 *Return : data read
 *
 *----------------------------------------------------------------------------*/
uint8_t i2c_repeated_read(uint8_t isLastRead)
{
	uint8_t data;

	lock_detect = INITIAL;

	if (isLastRead) {
		NACK;							//set NACK after read
	} else {
		ACK;							//ACK after read
	}

	data = I2C0->D;						//dummy read
	I2C_WAIT
	//wait for completion

	if (isLastRead) {
		I2C_M_STOP;						//send stop
	}
	data = I2C0->D;						//read data

	return data;
}

//functions for reading and writing a single byte
//using 7bit addressing reads a byte from dev:address

uint8_t i2c_read_byte(uint8_t dev, uint8_t address)
{
	uint8_t data;

	I2C_TRAN;						//set to transmit mode
	I2C_M_START;					//send start
	I2C0->D = dev;			  		//send dev address
	I2C_WAIT
	//wait for completion

	I2C0->D = address;				//send read address
	I2C_WAIT
	//wait for completion

	I2C_M_RSTART;				  	//repeated start
	I2C0->D = (dev | 0x1);	 		//send dev address (read)
	I2C_WAIT
	//wait for completion

	I2C_REC;						//set to receive mode
	NACK;							//set NACK after read

	data = I2C0->D;					//dummy read
	I2C_WAIT
	//wait for completion

	I2C_M_STOP;						//send stop
	data = I2C0->D;					//read data

	return data;
}

/*----------------------------------------------------------------------------
 void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data)
 *@brief : this function is used read bytes and ack/nack as appropriate
 *
 *Parameters : uint8_t dev:  Device address
 *			   uint8_t address : Read address
 *			   unit8_t data : data read
 *
 *Return : none
 *
 *----------------------------------------------------------------------------*/
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data)
{
	I2C_TRAN;						//set to transmit mode
	I2C_M_START;					//send start
	I2C0->D = dev;			  		//send dev address
	I2C_WAIT
	//wait for ack

	I2C0->D = address;				//send write address
	I2C_WAIT

	I2C0->D = data;					//send data
	I2C_WAIT
	I2C_M_STOP;
}

