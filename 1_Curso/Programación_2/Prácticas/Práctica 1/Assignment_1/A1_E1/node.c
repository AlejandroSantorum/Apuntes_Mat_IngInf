/**
*  Project: Assignment 1 - ProgII subject
*  File: node.c
*  Version: 2.0
*  Date: Feb 20, 2017
*  Revision date: May 26, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

#define NAME_SIZE 64

/**
*  Private struct with the node data
*/
struct _Node {
 char name[NAME_SIZE];
 int id;
};

/**
*  Initializes a node, allocating memory and returning the initialized node
*  if everything has gone successfully, NULL otherwise
*/
Node* node_ini(){
   Node *n=NULL;

   n = (Node *) malloc(sizeof(Node));
   if(!n){ /* Memory error */
      printf("Node Error: NULL pointer in node_ini function\n");
      return NULL;
   }
   return n;
}

/**
*  Frees allocated memory for the given node
*/
void node_destroy(Node* n){
   if(n){ /* n != NULL */
      free(n);
      return;
   }
   printf("Node Warning: NULL pointer in node_destroy function\n");
}

/**
*  Returns the ID of the given node on success, -1 if any error occurs
*/
int node_getId(Node* n){
   if(!n){ /* NULL pointer error */
      printf("Node Error: NULL pointer in node_getId function\n");
      return -1;
   }
   return n->id;
}

/**
*  Returns the name of the given node on success, NULL otherwise
*/
char* node_getName(Node* n){
   if(!n){ /* NULL pointer error */
      printf("Node Error: NULL pointer in node_getName function\n");
      return NULL;
   }
   return n->name;
}

/**
*  Modifies the ID of the given node.
*  It returns NULL if any error is produced, or a pointer to the modified node on success
*/
Node* node_setId(Node* n, int id){
   if(!n){ /* NULL pointer error */
      printf("Node Error: NULL pointer in node_setId function\n");
      return NULL;
   }
   n->id = id;
   return n;
}

/**
*  Modifies the name of the given node.
*  It returns NULL if any error is produced, or a pointer to the modified node on success
*/
Node* node_setName(Node* n, char* name){
   if(!n){ /* NULL pointer error */
      printf("Node Error: node NULL pointer in node_setName function\n");
      return NULL;
   }
   if(!name){ /* NULL pointer error */
      printf("Node Error: name NULL pointer in node_setName function\n");
      return NULL;
   }

   strcpy(n->name, name);
   return n;
}

/**
*  Checks if two nodes are equal.
*  Returns TRUE if they are equal, FALSE otherwise
*/
Bool node_equals(Node* n1, Node* n2){
   if(!n1){ /* NULL pointer error */
      printf("Node Error: node1 NULL pointer in node_equals function\n");
      return FALSE;
   }
   if(!n2){ /* NULL pointer error */
      printf("Node Error: node2 NULL pointer in node_equals function\n");
      return FALSE;
   }

   if(n1->id != n2->id){
      return FALSE;
   } else if(strcmp(n1->name, n2->name)!=0){
      return FALSE;
   }
   return TRUE;
}

/**
*  It copies the data of a given node into another.
*  On success, it returns a new allocated node with the same data than the input,
*  NULL otherwise
*/
Node* node_copy(Node* src){
   Node *copy=NULL;

   if(!src){ /* NULL pointer error */
      printf("Node Error: source NULL pointer in node_copy function\n");
      return NULL;
   }

   copy = node_ini();
   if(!copy){ /* NULL pointer error */
      printf("Node Error: copy NULL pointer in node_copy function\n");
      return NULL;
   }

   strcpy(copy->name, src->name);
   copy->id = src->id;
   return copy;
}

/**
*  Prints in pf the data of a given node with the next format: [ID, name].
*  As an example, a node with "aaa" as its name and 123 as its ID, this function will
*  print [123, aaa]. In addiction, it returns the number of written characters successfully
*/
int node_print(FILE *pf, Node *n){
   if(!pf){ /* NULL pointer error */
      printf("Node Error: file NULL pointer in node_print function\n");
      return -1;
   }
   if(!n){ /* NULL pointer error */
      printf("Node Error: node NULL pointer in node_print function\n");
      return -1;
   }
   return fprintf(pf, "[%d, %s]", n->id, n->name);
}
