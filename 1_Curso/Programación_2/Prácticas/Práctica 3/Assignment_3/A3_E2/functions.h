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

#include "node.h"

/**
*  In this file destruction, copy and print functions of elements are defined,
*  in order to introduce them in a generic data type queue
*/

/**
*  Node destruction function
*/
void destroy_node_function(void *e);

/**
*  Node copy function
*/
void * copy_node_function(void *e);

/**
*  Node print function
*/
int  print_node_function(FILE *f, void* e);


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

#endif /* FUNCTIONS_H */
