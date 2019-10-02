/**
*  Project: Assignment 3 - ProgII subject
*  File: queue.h
*  Version: 2.0
*  Date: Apr 15, 2017
*  Revision date: May 30, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include "types.h"


typedef struct _Queue Queue;

/**
*  Function pointer types supported by queue
*/
typedef void (*destroy_elementqueue_function_type)(void*);
typedef void *(*copy_elementqueue_function_type)(void*);
typedef int (*print_elementqueue_function_type)(FILE *, void*);


/**
*  It initializes a queue, allocating memory for it and its elements.
*  It returns the created queue or NULL in case error
*/
Queue* queue_ini(destroy_elementqueue_function_type f1, copy_elementqueue_function_type f2, print_elementqueue_function_type f3);

/**
*  It frees the allocated memory for the given entire queue, including its elements
*/
void queue_destroy(Queue *q);

/**
*  It checks if the given queue is empty, returning TRUE in affirmative case,
*  FALSE otherwise
*/
Bool queue_isEmpty(Queue *q);

/**
*  It checks if the given queue is full, returning TRUE in affirmative case,
*  FALSE otherwise
*/
Bool queue_isFull(Queue* q);

/**
*  It inserts a COPY (allocates memory for the copy) of the given element into the queue.
*  It returns the modified queue, or NULL if any error appears
*/
Queue* queue_insert(Queue *q, void *ele);

/**
*  It extracts one element from the given queue, returning the element, or NULL if error case
*/
void * queue_extract(Queue *q);

/**
*  It returns the number of elements of the given queue.
*  -1 is returned in error case
*/
int queue_size(Queue *q);

/**
*  It prints the given queue, returning the number of characters successfully
*  written, or -1 if any error is produced
*/
int queue_print(FILE *pf, Queue *q);


#endif /* QUEUE_H */
