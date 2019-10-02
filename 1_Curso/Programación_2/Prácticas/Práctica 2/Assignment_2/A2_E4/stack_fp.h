/**
*  Project: Assignment 2 - ProgII subject
*  File: stack_fp.h
*  Version: 2.0
*  Date: Mar 20, 2017
*  Revision date: May 27, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#ifndef STACK_ELEMENT_H
#define STACK_ELEMENT_H

#include <stdio.h>
#include "functions.h"
#include "types.h"

#define MAXSTACK 1024

typedef struct _Stack Stack;

/* Function pointer types */
typedef void (*destroy_element_function_type)(void*);
typedef void *(*copy_element_function_type)(void*);
typedef int (*print_element_function_type)(FILE *, void*);

/**
*  It Initializes a stack, allocating memory and returning it.
*  NULL is returned in error case
*/
Stack* stack_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3);

/**
*  It frees the allocated memory for the given stack
*/
void stack_destroy(Stack *s);

/**
*  It inserts a copy of the given element into the given stack.
*  It returns the modified stack, or NULL in error case
*/
Stack* stack_push(Stack *s, void *e);

/**
*  It extracts one element from the given stack, returning the extracted element,
*  or NULL if any error ocurrs
*/
void* stack_pop(Stack *s);

/**
*  It returns a copy of the first element of the given stack (top element),
*  NULL if any error is generated or if the stack is empty
*/
void* stack_top(Stack *s);

/**
*  It checks if the given stack has zero elements in it.
*  It returns TRUE in affirmative case, FALSE otherwise
*/
Bool stack_isEmpty(Stack *s);

/**
*  It checks if the given stack has the maximum number of elements in it.
*  It returns TRUE in affirmative case, FALSE otherwise
*/
Bool stack_isFull(Stack *s);

/**
*  It prints the whole data of the given stack in the file given as a parameter.
*  It returns the number of characters successfully written or -1 in error case
*/
int stack_print(FILE *f, Stack *s);

#endif /* STACK_FP_H */
