/***************************************************************************************************************************
 File name: UART.c
 ​Description: Assignment 6 PES -
 Contains different functions for UART processing
 File​ ​Author​ ​Name: Vidhya PL, Alexander G. Dean
 Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 Credits: UART initialization - Dhaanish Sharif
 	 	  Glue logic idea brain storming credit to Visweshwaran Baskharan
 	 	  Reused from my(Vidhya . PL) assignment 6 of PES coursework
 	 	  https://github.com/alexander-g-dean/ESF
 	 	  https://github.com/vidhyapalaniappan/PES_Assignment_6
 *****************************************************************************************************************************
 */
#include "UART.h"

/*Defining Macros here*/
#define BAUD_RATE				38400
#define BYTE_SHIFT				8
#define PARITY_DISABLED			(UART0_C1_PE(1))
#define DATA_8_BIT 				(UART0_C1_M(1))
#define TWO_STOP_BITS 			(UART0_BDH_SBNS(0))
#define UART_OVERSAMPLE_RATE 	16
#define BUS_CLOCK				24e6
#define SIZE (80)
#define MAX_CHAR_SIZE (255)

//Defining linked list for UART Tx and Rx
llfifo_t *TxQ, *RxQ;

/*----------------------------------------------------------------------------
 * @brief:	initializes UART0
 *
 * @parameters:
 *   	uint32_t baud_rate	: Baud rate of UART
 *
 * @returns: none
 ----------------------------------------------------------------------------*/
void Init_UART0(uint32_t baud_rate)
{
	uint16_t sbr;

	/* Enable clock gating for UART0 and Port A */
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	/* Make sure transmitter and receiver are disabled before init */
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	/* Set UART clock to 24 MHz clock */
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

	/* Set pins to UART0 Rx and Tx */
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	/* Set baud rate and oversampling ratio */
	/*Baud Rate is set to 38400 by loading the value based on the formula into the BDH and BDL registers. */
	sbr = (uint16_t) ((BUS_CLOCK) / (BAUD_RATE * UART_OVERSAMPLE_RATE)); /*Formula to calculate load value for Baud rate. */
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>BYTE_SHIFT); /*MSB loaded into BDH */
	UART0->BDL = UART0_BDL_SBR(sbr); /*LSB loaded into BDL. */
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

	/* Disable interrupts for RX active edge and LIN break detect, select two stop bits*/
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | TWO_STOP_BITS | UART0_BDH_LBKDIE(0);

	/* Don't enable loopback mode, use 8 data bit mode, don't use parity */
	UART0->C1 = UART0_C1_LOOPS(
			0) | DATA_8_BIT | PARITY_DISABLED | UART0_C1_PT(0);
	/* Don't invert transmit data, don't enable interrupts for errors */
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
	| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	/* Clear error flags */
	UART0->S1 = UART0_S1_OR(
			1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	/* Send LSB first, do not invert received data */
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);
	TxQ = llfifo_create (SIZE);
	RxQ = llfifo_create(SIZE);

	NVIC_SetPriority(UART0_IRQn, 2);
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	/* Enable receive interrupts but not transmit interrupts yet */
	UART0->C2 |= UART_C2_RIE(1);

	/* Enable UART receiver and transmitter */
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	/* Clear the UART RDRF flag */

	UART0->S1 &= ~UART0_S1_RDRF_MASK;

}

/*----------------------------------------------------------------------------
 * @brief:	UART0 interrupt service routine
 *
 * @parameters:
 *   	none
 *
 * @returns: none
 ----------------------------------------------------------------------------*/
void UART0_IRQHandler(void)
{
	uint8_t ch;

	if (UART0->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK |
	UART_S1_FE_MASK | UART_S1_PF_MASK))
	{
		// clear the error flags
		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
		UART0_S1_FE_MASK | UART0_S1_PF_MASK;
		// read the data register to clear RDRF
		ch = UART0->D;
	}
	if (UART0->S1 & UART0_S1_RDRF_MASK)
	{
		// received a character, enqueue
		ch = UART0->D;
		llfifo_enqueue(RxQ, ch);

	}
	if ((UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
			(UART0->S1 & UART0_S1_TDRE_MASK))
	{ // tx buffer empty

		ch = llfifo_dequeue(TxQ);
		if (ch < MAX_CHAR_SIZE)
		{
			UART0->D = ch;
		}
		else
		{
			// queue is empty so disable transmitter interrupt
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}
	}
}

/*----------------------------------------------------------------------------
 * @brief:	glue logic to replace lower level write function for printf/putchar
 *
 * @parameters:
 *   	int		:
 *   		iFileHandle : file descriptor, 1 for stdout, 2 for stderr
 *   		iLength : length of string
 *   	char *str : string to write to file
 *
 * @returns: int : 0 on success
 ----------------------------------------------------------------------------*/
int __sys_write(int iFileHandle, char *str, int iLength)
{
	// enqueue string
	while (*str != '\0')
	{ // copy characters up to null terminator
		while (llfifo_Full(TxQ))
			;  // wait for space to open up
		llfifo_enqueue(TxQ, *str); //space opened up, enqueue
		str++;	//update pointer
	}
	// start transmitter if it isn't already running
	if (!(UART0->C2 & UART0_C2_TIE_MASK))
	{
		UART0->C2 |= UART0_C2_TIE(1);
	}
	return 0; //return success
}

/*----------------------------------------------------------------------------
 * @brief:	glue logic to replace lower level read function for printf/putchar
 *
 * @parameters:
 *   	none
 *
 * @returns: int : 	ascii value of character read on success
 * 					-1 on failure
 ----------------------------------------------------------------------------*/
int __sys_readc(void)
{
	while (llfifo_Empty(RxQ))
		;   			//wait here till list is empty
	uint8_t character;
	character = llfifo_dequeue(RxQ);      	//dequeue the next elemenet in queue
	if (character < MAX_CHAR_SIZE)
	{					//check for valid character
		return character;						//valid character, return
	}
	return -1;								//invalid character, return error
}
