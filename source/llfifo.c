/***************************************************************************************************************************
 File name: llfifo.h
 ​Description: Assignment 6 PES - Functions to create, enqueue, dequeue, destroy, find length and capacity of LLfifo
 File​ ​Author​ ​Name: Vidhya PL
 Tools​ ​used​ ​to​ ​process​ ​the​ ​code​: MCUXpresso
 Referred Google for a few concepts clarification
 Date : 5/ 4/ 2023

 Credits:
  	 	  Reused from my(Vidhya . PL) assignment 6 of PES coursework
 	 	  https://github.com/alexander-g-dean/ESF
 	 	  https://github.com/vidhyapalaniappan/PES_Assignment_6
     	  https://codeforwin.org/data-structures/c-program-to-create-and-traverse-singly-linked-list
		  https://codeforwin.org/data-structures/c-program-to-insert-node-at-end-of-singly-linked-list
		  https://codeforwin.org/data-structures/c-program-to-delete-last-node-of-singly-linked-list
		  https://codeforwin.org/data-structures/c-program-to-delete-all-nodes-of-singly-linked-list
 *****************************************************************************************************************************
 */

/*Including the required header files*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

#include "llfifo.h"

/*Defining MACROS here*/
#define ERROR (-1)
#define ZERO (0)
#define ONE (1)
#define MAX (256)

/*----------------------------------------------------------------------------
 Defining the structure of linked list here
 *
 *Parameters :
 *   struct llfifo_s* head - The top element of the list
 *   struct llfifo_s* next - Structure to build and save the elements of the list
 *   void *data - Pointer to data stored in the list
 *   int capacity - Capacity is the total number of nodes created in the linked list
 *   int length - Total number of elements stored in the list
 ----------------------------------------------------------------------------*/
struct llfifo_s
{
	uint8_t capacity;
	uint8_t length;
	uint8_t data;
	struct llfifo_s *head;
	struct llfifo_s *next;
};

/*----------------------------------------------------------------------------
 *Function to create a linked list
 *
 *Paramets:
 *   int capacity - The capacity of the linked list to be created
 *
 *Returns - A pointer to a newly-created llfifo_t instance
 *
 *Error - When newnode is NULL, when memory is not allocated to the malloced pointer.
 ----------------------------------------------------------------------------*/
llfifo_t* llfifo_create(int capacity)
{

	llfifo_t *current_head = NULL; /*declaring a pointer current_head of type llfifo_t and initializing it to NULL*/
	llfifo_t *newnode = (llfifo_t*) malloc(sizeof(llfifo_t)); /*allocating memory to the new node*/
	if (newnode == NULL) /*checking if the memory allocation was successful*/
	{
		return NULL;
	}
	current_head = newnode; /*setting the value of current_head to the address of the newly created node.*/
	newnode->head = newnode; /*setting the value of the head field of newnode to the address of newnode itself. */
	newnode->next = NULL; /*setting the next pointer to NULL to avoid segmentation fault*/
	newnode->capacity = capacity;	//assigning capacity value
	newnode->length = ZERO;			//length is zero when we create LLFIFO

	//now create required number of nodes
	for (int i = ONE; i < current_head->capacity; i++)
	{
		llfifo_t *temp = (llfifo_t*) malloc(sizeof(llfifo_t));
		if (temp == NULL) {
			return NULL;
		}
		newnode->next = temp; /*Setting next field of newnode to newly created node pointed by temp*/
		temp->next = NULL;
		newnode = newnode->next; /*setting the value of newnode to the address of the next node in the linked list, which was set in the previous step.*/
	}

	//return the head node
	return current_head;
}

/*----------------------------------------------------------------------------------------------------------------------
 *Function to enqueue an element onto the fifo
 *
 *Parameters :
 *   llfifo_t *fifo - The fifo being created
 *   void *element - Element to be enqueueed
 *
 *Returns:
 *   The length of the fifo
 *
 *Error : When passed element is NULL, when head of fifo is NULL,  when memory is not allocated to the malloced pointer.
 ----------------------------------------------------------------------------------------------------------------------*/
int llfifo_enqueue(llfifo_t *fifo, uint8_t element)
{
	__disable_irq();
	if (element == ZERO)
	{
		__enable_irq();
		return ERROR; /*if the element to be enqueueed is NULL, returns ERROR (-1)*/
	}

	if (fifo->head == NULL)
	{
		__enable_irq();
		return ERROR; /*if the list in which enqueue is to be performed is NULL, returns ERROR (-1)*/
	}

	if (fifo->length == fifo->capacity)
	{
		llfifo_t *temp = fifo->head; /*pointer temp is initialized with the value of the head of the linked list.*/
		while (temp->next != NULL) /*loop to move temp to the end of the linked list.*/
		{
			temp = temp->next;
		}
		llfifo_t *newnode = (llfifo_t*) malloc(sizeof(llfifo_t));
		temp->next = newnode; /*next field of the current end node is set to the newly created node.*/

		newnode->next = NULL;
		newnode->data = element;
		fifo->capacity++;
		fifo->length++;
		__enable_irq();
		return ONE;
	}
	else
	{
		llfifo_t *temp = fifo->head;
		int i = ZERO;
		while (i < fifo->length) /*loop to move temp to the next unoccupied node.*/
		{
			temp = temp->next;
			i++;
		}
		temp->data = element; /*data field of the next unoccupied node is set to the value of element*/
		fifo->length++;
		__enable_irq();
		return ONE;
	}
	__enable_irq();
	return ERROR; /*Returning the length of the linked list*/
}

/*------------------------------------------------------------------------------------
 *Function to dequeue(remove) an element from the fifo
 *
 *Parameters :
 *   llfifo_t *fifo - The fifo in question
 *
 *Returns:
 *   The element dequeued from the list
 *
 *Error : When fifo is NULL, when length of fifo is Zero, when capacity of fifo is zero
 -------------------------------------------------------------------------------------*/
uint8_t llfifo_dequeue(llfifo_t *fifo)
{
	__disable_irq();
	if (fifo == NULL)
	{
		__enable_irq();
		return ERROR; /*If the list passed is NULL, function should return NULL*/
	}
	if (fifo->length == ZERO)
	{
		__enable_irq();
		return ERROR; /*If there is no element in the list to be dequeued, function should return NULL*/
	}
	if (fifo->capacity == ZERO)
	{
		__enable_irq();
		return ERROR; /*If no node is created in the list to be dequeued, function should return NULL*/
	}

	uint8_t elmt;
	llfifo_t *temp = fifo->head; /*pointer temp is initialized with the value of the head of the linked list.*/
	fifo->head = fifo->head->next; /*second element in the queue will now be the head*/
	int i = ZERO;
	elmt = temp->data; /*data to return*/

	fifo->length--;		//update length of fifo
	if (fifo->length < ZERO)	//check for underflow
	{
		fifo->length = ZERO;	//if underflow, set it to zero
	}

	llfifo_t *last = fifo->head;
	while (i < fifo->capacity - 2) /* loop to move temp to the node just before the last node*/
	{
		last = last->next;	//iterate till last node
		i++;
	}
	last->next = temp;	//assign current head node to end of the queue
	temp->next = NULL;
	__enable_irq();
	return elmt; /*Returning the element dequeued*/
}

/*----------------------------------------------------------------------------
 *Function to find if FIFO is empty
 *
 *Parameters :
 *   llfifo_t *q - The fifo to be checked for empty
 *
 *Returns
 *	int : 	0 if FIFO is not empty
 *			1 if FIFO is empty
 *
 ----------------------------------------------------------------------------*/
int llfifo_Empty(llfifo_t *q)
{
	return q->length == ZERO;
}

/*----------------------------------------------------------------------------
 *Function to find if FIFO is Full
 *
 *Parameters :
 *   llfifo_t *fifo - The fifo to be checked for full
 *
 *Returns
 *	int	:	0 if FIFO is not full
 *			1 if FIFO is full
 ----------------------------------------------------------------------------*/
int llfifo_Full(llfifo_t *q)
{
	return q->length == MAX;
}
