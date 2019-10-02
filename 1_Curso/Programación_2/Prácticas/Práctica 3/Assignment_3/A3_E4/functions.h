/**
*  Project: Assignment 3 - ProgII subject
*  File: functions.h
*  Version: 2.0
*  Date: Apr 15, 2017
*  Revision date: May 30, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

/**
*  In this file destruction, copy and print functions of elements are defined,
*  in order to introduce them in a generic data type queue
*/


/**
*  Integer destruction function
*/
void destroy_intp_function(void* e);

/**
*  Integer copy function
*/
void * copy_intp_function(void* e);

/**
*  Integer copy function
*/
int print_intp_function(FILE * f, void* e);

/**
*  Integer compare function
*/
int cmp_intp_function(void *v1, void *v2);

#endif /* FUNCTIONS_H */
