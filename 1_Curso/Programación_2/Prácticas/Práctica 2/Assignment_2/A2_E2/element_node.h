/**
*  Project: Assignment 2 - ProgII subject
*  File: element_node.h
*  Version: 2.0
*  Date: Mar 19, 2017
*  Revision date: May 27, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#ifndef ELEMENT_INT_H
#define ELEMENT_INT_H

#include <stdio.h>
#include "types.h"

typedef struct _Element Element;

/**
*  Initializes a new node type element, allocating memory and returning it, or NULL in error case
*/
Element* element_ini();

/**
*  Frees the allocated memory for a given element
*/
void element_destroy(Element *e);

/**
*  It returns the data of a given element, or NULL in error case
*/
void* element_getInfo(Element *e);

/**
*  It modifies the element data with a new one, given as a parameter.
*  It returns the modified element or NULL if any error ocurrs
*/
Element* element_setInfo(Element *e, void *data);

/**
*  It copies one element into a new one, allocating memory for it.
*  It returns the copy element or NULL if any error appears
*/
Element* element_copy(Element *e);

/**
*  It checks if two elements are equal, returning TRUE if they are, FALSE otherwise
*/
Bool element_equals(Element *e1, Element *e2);

/**
*  It prints in the given file the data associated to the given element.
*  It returns the number of characters successfully printed, or -1 in error case
*/
int element_print(FILE *f, Element *e);

#endif /*ELEMENT_INT_H*/
