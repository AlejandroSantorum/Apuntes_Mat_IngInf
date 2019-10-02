/**
*  Project: Assignment 3 - ProgII subject
*  File: list.h
*  Version: 2.0
*  Date: Apr 16, 2017
*  Revision date: May 30, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "functions.h"

typedef struct _List List;

/** Function pointer types supported by the list */
typedef void (*destroy_elementlist_function_type)(void*);
typedef void *(*copy_elementlist_function_type)(void*);
typedef int (*print_elementlist_function_type)(FILE*, void*);
typedef int (*cmp_elementlist_function_type)(void*, void*);


/**
*  It initializes a list, allocating memory for it and for its componenets,
*  returning the created list, or NULL in error case
*/
List* list_ini(destroy_elementlist_function_type f1, copy_elementlist_function_type f2, print_elementlist_function_type f3, cmp_elementlist_function_type f4);

/**
*  It frees all the allocated memory for the given list
*/
void list_destroy(List *l);

/**
*  It inserts a COPY of the given element into the given list at the beggining.
*  It returns the modified list or NULL in error case
*/
List* list_insertFirst(List *l, void *ele);

/**
*  It inserts a COPY of the given element into the given list at the end.
*  It returns the modified list or NULL if any error occurs
*/
List* list_insertLast(List *l, void *ele);

/**
*  It inserts in order a COPY of the given element into the given list.
*  It returns the modfied list or NULL in error case
*/
List* list_insertInOrder(List *list, void *pElem);

/**
*  It extracts the element of the beggining of the given list, or NULL in error case
*/
void * list_extractFirst(List *list);

/**
*  It extracts the element of the end of the given list , or NULL in error case
*/
void * list_extractLast(List *list);

/**
*  It checks if the given list is empty, returning TRUE in affirmative case or FALSE otherwise
*/
Bool list_isEmpty(List *list);

/**
*  It returns the i-th element of the given list, NULL is returned in error case
*/
void* list_get(List *list, int i);

/**
*  It returns the size of the given list. -1 if any error appears
*/
int list_size(List* list);

/**
*  It prints the given list, returning the number of the characters written
*  successfully, or -1 if any error is produced
*/
int list_print(FILE *fd, List* list);

/**
*  It checks if a given list already contains a given element.
*  It returns TRUE in affirmative case, NULL otherwise
*/
Bool list_isElement(List *l, void *ele);

#endif /* LIST_H */
