/**
*  Project: Assignment 1 - ProgII subject
*  File: a1_e1_test.c
*  Version: 2.0
*  Date: Feb 20, 2017
*  Revision date: May 26, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include "node.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
   Node *n1=NULL, *n2=NULL;

   /** Allocating memory for two nodes */
   printf("Allocating memory...\n");
   n1 = node_ini();
   if(!n1){
      printf("Error initializing node 1\n");
      exit(EXIT_FAILURE);
   }
   n2 = node_ini();
   if(!n2){
      printf("Error initializing node 2\n");
      exit(EXIT_FAILURE);
   }
   printf("Memory allocated successfully!\n");

   /** Setting nodes names and ID's*/
   printf("\nSetting nodes names and ID's\n");
   n1 = node_setName(n1, "first");
   if(!n1){
      printf("Error setting node 1 name\n");
      exit(EXIT_FAILURE);
   }
   n1 = node_setId(n1, 111);
   if(!n1){
      printf("Error setting node 1 ID\n");
      exit(EXIT_FAILURE);
   }
   n2 = node_setName(n2, "second");
   if(!n2){
      printf("Error setting node 2 name\n");
      exit(EXIT_FAILURE);
   }
   n2 = node_setId(n2, 222);
   if(!n2){
      printf("Error setting node 2 ID\n");
      exit(EXIT_FAILURE);
   }
   printf("Names and ID's set successfully!\n");

   /** Printing nodes data */
   printf("\nPrinting nodes data...\n");
   if(node_print(stdout, n1)==-1){
      printf("Error printing node 1\n");
      exit(EXIT_FAILURE);
   }
   if(node_print(stdout, n2)==-1){
      printf("Error printing node 2\n");
      exit(EXIT_FAILURE);
   }
   printf("\nData printed successfully!\n");

   /** Checking if they are equal */
   printf("\nChecking if the nodes are equal (they should be different)\n");
   printf("Are they equal? --> ");
   if(node_equals(n1, n2)==TRUE){
      printf("Yes\n");
   } else if(node_equals(n1, n2)==FALSE){
      printf("No\n");
   }

   /** Checking getters and setters */
   printf("\nChecking some data...\n");
   printf("First node ID: %d\n", node_getId(n1));
   printf("Name of the second node: %s\n", node_getName(n2));
   printf("Done\n");

   /** Checking copy function */
   printf("\nCopying node 1 into node 2...\n");
   node_destroy(n2);
   n2 = node_copy(n1);
   if(!n2){
      printf("Error making a copy of the first node into the second node\n");
      exit(EXIT_FAILURE);
   }
   printf("Copy performed successfully\n");

   /** Printing after copy */
   printf("\nPrinting data after the copy...\n");
   if(node_print(stdout, n1)==-1){
      printf("Error printing node 1\n");
      exit(EXIT_FAILURE);
   }
   if(node_print(stdout, n2)==-1){
      printf("Error printing node 2\n");
      exit(EXIT_FAILURE);
   }
   fprintf(stdout, "\n");

   /** Checking if they are equal after copy */
   printf("\nChecking if they are equal (they should be)\n");
   printf("Are they equal? --> ");
   if(node_equals(n1, n2)==TRUE){
      printf("Yes\n");
   } else if(node_equals(n1, n2)==FALSE){
      printf("No\n");
   }

   /** Freeing memory */
   printf("\nChecking freeing function\n");
   node_destroy(n1);
   node_destroy(n2);

   printf("\nThe test has been a success!\n");
   exit(EXIT_SUCCESS);
}
