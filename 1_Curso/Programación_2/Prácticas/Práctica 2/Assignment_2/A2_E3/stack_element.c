/**
*  Project: Assignment 2 - ProgII subject
*  File: stack_element.c
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
#include "stack_element.h"

/** Stack data structure */
struct _Stack{
    Element *item[MAXSTACK]; /* Array of introduced elements */
    int top;   /* Index of the top element */
};

/**
*  It Initializes a stack, allocating memory and returning it.
*  NULL is returned in error case
*/
Stack* stack_ini(){
   Stack *s=NULL;
   int i;

   s = (Stack *) malloc(sizeof(Stack));
   if(!s){
      printf("Stack Error: unable to allocate memory for a new stack in stack_ini function\n");
      return NULL;
   }

   for(i=0; i<MAXSTACK; i++){
      s->item[i]=NULL;
   }
   s->top = -1;
   return s;
}

/**
*  It frees the allocated memory for the given stack
*/
void stack_destroy(Stack *s){
   int i;

   if(!s){
      printf("Stack Warning: trying to free a NULL stack in stack_destroy function\n");
      return;
   }

   for(i=0; i<=s->top; i++){
      element_destroy(s->item[i]);
   }
   free(s);
}

/**
*  It inserts a copy of the given element into the given stack.
*  It returns the modified stack, or NULL in error case
*/
Stack* stack_push(Stack *s, Element *e){
   Element *aux=NULL;

   if(!s){
      printf("Stack Error: stack NULL pointer in stack_push function\n");
      return NULL;
   }
   if(!e){
      printf("Stack Error: element NULL pointer in stack_push function\n");
      return NULL;
   }
   if(stack_isFull(s)==TRUE){
      printf("Stack Error: stack is full, unable to push another element\n");
      return NULL;
   }

   aux = element_copy(e);
   if(!aux){
      printf("Stack Error: unable to create a copy of the given element in stack_push function\n");
      return NULL;
   }

   (s->top)++;
   s->item[s->top] = aux;
   return s;
}

/**
*  It extracts one element from the given stack, returning the extracted element,
*  or NULL if any error ocurrs
*/
Element* stack_pop(Stack *s){
   Element *e=NULL;

   if(!s){
      printf("Stack Error: NULL pointer in stack_pop function\n");
      return NULL;
   }
   if(stack_isEmpty(s)==TRUE){
      printf("Stack Error: stack is empty, unable to pop an element\n");
      return NULL;
   }

   e = s->item[s->top];
   s->item[s->top] = NULL;
   (s->top)--;
   return e;
}

/**
*  It returns a copy of the first element of the given stack (top element),
*  NULL if any error is generated or if the stack is empty
*/
Element* stack_top(Stack *s){
   Element *e=NULL;

   if(!s){
      printf("Stack Error: NULL pointer in stack_pop function\n");
      return NULL;
   }
   if(stack_isEmpty(s)==TRUE){ /* This is not considered an error */
      return NULL;
   }

   e = element_copy(s->item[s->top]);
   if(!e){
      printf("Stack Error: unable to create a copy of the top element in stack_top function\n");
      return NULL;
   }
   return e;
}

/**
*  It checks if the given stack has zero elements in it.
*  It returns TRUE in affirmative case, FALSE otherwise
*/
Bool stack_isEmpty(Stack *s){
   if(!s){
      printf("Stack Error: NULL pointer in stack_isEmpty function\n");
      return FALSE;
   }

   if(s->top == -1){
       return TRUE;
   }
   return FALSE;
}

/**
*  It checks if the given stack has the maximum number of elements in it.
*  It returns TRUE in affirmative case, FALSE otherwise
*/
Bool stack_isFull(Stack *s){
   if(!s){
      printf("Stack Error: NULL pointer in stack_isFull function\n");
      return FALSE;
   }

   if(s->top == (MAXSTACK-1)){
      return TRUE;
   }
   return FALSE;
}

/**
*  It prints the whole data of the given stack in the file given as a parameter.
*  It returns the number of characters successfully written or -1 in error case
*/
int stack_print(FILE *f, Stack *s){
   int i, num=0;

   if(!s){
      printf("Stack Error: stack NULL pointer in stack_print function\n");
      return -1;
   }
   if(!f){
      printf("Stack Error: file NULL pointer in stack_print function\n");
      return -1;
   }

   if(stack_isEmpty(s)==TRUE){
      return fprintf(f, "[]\n");
   }
   for(i=s->top; i>=0; i--){
      num += fprintf(f, "[");
      num += element_print(f, s->item[i]);
      num += fprintf(f, "]\n");
   }
   return num;
}
