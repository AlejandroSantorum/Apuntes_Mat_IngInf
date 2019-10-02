/**
*  Project: Assignment 3 - ProgII subject
*  File: functions.c
*  Version: 2.0
*  Date: Apr 15, 2017
*  Revision date: May 30, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include <stdlib.h>
#include "functions.h"

/**
*  In this file destruction, copy and print functions of elements are defined,
*  in order to introduce them in a generic data type queue
*/

/**
*  Node destruction function
*/
void destroy_node_function(void* e){
    node_destroy((Node *)e);
}

/**
*  Node copy function
*/
void* copy_node_function(void* e){
    return node_copy((Node *)e);
}

/**
*  Node print function
*/
int  print_node_function(FILE *f, void* e){
    return node_print(f, (Node *)e);
}
