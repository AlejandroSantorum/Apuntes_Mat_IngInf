/**
*  Project: Assignment 1 - ProgII subject
*  File: node.h
*  Version: 2.0
*  Date: Feb 20, 2017
*  Revision date: May 26, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include "types.h"

typedef struct _Node Node;

/**
*  Initializes a node, allocating memory and returning the initialized node
*  if everything has gone successfully, NULL otherwise
*/
Node * node_ini();

/**
*  Frees allocated memory for the given node
*/
void node_destroy(Node * n);

/**
*  Returns the ID of the given node on success, -1 if any error occurs
*/
int node_getId(Node * n);

/**
*  Returns the name of the given node on success, NULL otherwise
*/
char* node_getName(Node * n);

/**
*  Modifies the ID of the given node.
*  It returns NULL if any error is produced, or a pointer to the modified node on success
*/
Node * node_setId(Node * n, int id);

/**
*  Modifies the name of the given node.
*  It returns NULL if any error is produced, or a pointer to the modified node on success
*/
Node * node_setName(Node * n, char* name);

/**
*  Checks if two nodes are equal.
*  Returns TRUE if they are equal, FALSE otherwise
*/
Bool node_equals(Node * n1, Node * n2);

/**
*  It copies the data of a given node into another.
*  On success, it returns a new allocated node with the same data than the input,
*  NULL otherwise
*/
Node * node_copy(Node * src);

/**
*  Prints in pf the data of a given node with the next format: [ID, name].
*  As an example, a node with "aaa" as its name and 123 as its ID, this function will
*  print [123, aaa]. In addiction, it returns the number of written characters successfully
*/
int node_print(FILE *pf, Node *n);

#endif /* NODE_H */
