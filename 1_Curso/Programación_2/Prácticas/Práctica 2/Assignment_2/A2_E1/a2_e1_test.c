/**
*  Project: Assignment 2 - ProgII subject
*  File: a2_e1_test.c
*  Version: 2.0
*  Date: Mar 18, 2017
*  Revision date: May 27, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "element_int.h"
#include "stack_element.h"

#define N 10
void _stack_status(Stack *s){
   if(stack_isEmpty(s)==TRUE){
      printf("Stack status --> EMPTY\n");
      return;
   }
   if(stack_isFull(s)==TRUE){
      printf("Stack status --> FULL\n");
      return;
   }
   printf("Stack status --> NOT EMPTY WITH FREE SPACE\n");
}

int main(int argc, char **argv){
   Stack *s=NULL;
   Element *e=NULL;
   int n, i;

   s = stack_ini();
   if(!s) exit(EXIT_FAILURE);

   _stack_status(s);

   for(i=0; i<N; i++){
      e = element_ini();
      if(!e){
         printf("Error in the iteration number %d\n", i);
         exit(EXIT_FAILURE);
      }
      printf("Introduce a number: ");
      scanf("%d", &n);
      if(!element_setInfo(e, &n)){
         printf("Error in the iteration number %d\n", i);
         exit(EXIT_FAILURE);
      }
      if(!stack_push(s, e)){
         printf("Error in the iteration number %d\n", i);
         exit(EXIT_FAILURE);
      }
      printf("Element introduced successfully\n");
      element_destroy(e);
   }

   _stack_status(s);
   printf("Printing stack...\n");
   stack_print(stdout, s);

   for(i=0; i<N; i++){
      if(!(e = stack_pop(s))){
         exit(EXIT_FAILURE);
      }
      printf("Element extracted successfully\n");
      element_print(stdout, e);
      printf("\n");
      if(i!=N-1) element_destroy(e);
   }

   _stack_status(s);
   printf("Printing stack...\n");
   stack_print(stdout, s);

   printf("Filling the stack...");
   for(i=0; i<MAXSTACK; i++){
      if(!stack_push(s, e)) exit(EXIT_FAILURE);
   }
   printf("Stack is supposed to be full\n");
   element_destroy(e);

   _stack_status(s);
   printf("Printing stack...\n");
   stack_print(stdout, s);

   stack_destroy(s);

   return EXIT_SUCCESS;
}
