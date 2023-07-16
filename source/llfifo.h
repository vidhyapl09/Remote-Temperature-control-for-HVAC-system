/***************************************************************************************************************************
 File name: llfifo.h
 ​Description: Assignment 6 PES -
 header file of llfifo.c
 File​ ​Author​ ​Name: Vidhya PL
 Date :  Date : 5/ 4/ 2023
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
  Credits:
  	 	  Reused from my(Vidhya . PL) assignment 6 of PES coursework
 	 	  https://github.com/alexander-g-dean/ESF
 	 	  https://github.com/vidhyapalaniappan/PES_Assignment_6
 *****************************************************************************************************************************
 */

#ifndef _LLFIFO_H_
#define _LLFIFO_H_

#include <stdint.h>
#include "UART.h"
/*
 * The llfifo's main data structure.
 *
 * Defined here as an incomplete type, in order to hide the
 * implementation from the user. You will need to define this struct
 * in your .c file.
 */

typedef struct llfifo_s llfifo_t;

/*
 * Creates and initializes the LIFO
 *
 * Parameters:
 *   capacity  the initial size of the lifo, in number of elements.
 *             Valid values are in the range of 0 to the limits of memory
 *
 * Returns: A pointer to a newly-created llfifo_t instance, or NULL in
 *   case of an error.
 */
llfifo_t* llfifo_create(int capacity);

/*
 * Pushes an element onto the LIFO, growing the LIFO by adding
 * additional elements, if necessary
 *
 * Parameters:
 *   lifo    The lifo in question
 *   element The element to push, which cannot be NULL
 *
 * Returns:
 *   The new length of the LIFO on success, -1 on failure. It is an error to attempt
 * to push the NULL pointer.
 */
int llfifo_enqueue(llfifo_t *lifo, uint8_t element);

/*
 * Removes ("pops") an element from the LIFO, and returns it
 *
 * Parameters:
 *   lifo  The lifo in question
 *
 * Returns:
 *   The poped element, or NULL if the LIFO was empty
 */
uint8_t llfifo_dequeue(llfifo_t *lifo);

/*
 * Returns the number of elements currently on the LIFO.
 *
 * Parameters:
 *   lifo  The lifo in question
 *
 * Returns:
 *   The number of elements currently on the LIFO
 */
int llfifo_length(llfifo_t *lifo);

/*
 * Returns the LIFO's current capacity
 *
 * Parameters:
 *   lifo  The lifo in question
 *
 * Returns:
 *   The current capacity, in number of elements, for the LIFO
 */
int llfifo_capacity(llfifo_t *lifo);

/*
 * Teardown function: Frees all dynamically allocated
 * memory. After calling this function, the lifo should not be used
 * again!
 *
 * Parameters:
 *   lifo  The lifo in question
 *
 * Returns: none
 */
void llfifo_destroy(llfifo_t *lifo);

int llfifo_Empty(llfifo_t *q);
int llfifo_Full(llfifo_t *q);

#endif // _LLFIFO_H_
