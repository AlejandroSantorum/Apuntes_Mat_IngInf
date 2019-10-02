/**
*  Project: Assignment 2 - ProgII subject
*  File: element_int.c
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

/** Element_int data structure */
struct _Element{
    int *data;
};

/**
*  Initializes a new integer element, allocating memory and returning it, or NULL in error case
*/
Element* element_ini(){
   Element *ele=NULL;

   ele = (Element *) malloc(sizeof(Element));
   if(!ele){
      printf("Element Error: unable to allocate memory to initialize an element in element_ini function\n");
      return NULL;
   }
   ele->data = (int *) malloc(sizeof(int));
   if(!ele->data){
      printf("Element Error: unable to allocate memory to the element data in element_ini function\n");
      return NULL;
   }
   return ele;
}

/**
*  Frees the allocated memory for a given element
*/
void element_destroy(Element *e){
   if(!e){
      printf("Element Warning: trying to free a NULL pointer in element_destroy function\n");
      return;
   }
   if(e->data) free(e->data);
   free(e);
}

/**
*  It returns the data of a given element, or NULL in error case
*/
void* element_getInfo(Element *e){
   if(!e){
      printf("Element Error: NULL pointer in element_getInfo function\n");
      return NULL;
   }
   return ((void*)e->data);
}

/**
*  It modifies the element data with a new one, given as a parameter.
*  It returns the modified element or NULL if any error ocurrs
*/
Element* element_setInfo(Element *e, void *data){
   if(!e){
      printf("Element Error: element NULL pointer in element_setInfo function\n");
      return NULL;
   }
   if(!data){
      printf("Element Error: data NULL pointer in element_setInfo function\n");
      return NULL;
   }

   *(e->data) = *((int *)data); /* First casting to a integer pointer, then we get its content */
   return e;
}

/**
*  It copies one element into a new one, allocating memory for it.
*  It returns the copy element or NULL if any error appears
*/
Element* element_copy(Element *e){
   Element *copy=NULL;

   if(!e){
      printf("Element Error: NULL pointer in element_copy function\n");
      return NULL;
   }

   copy = element_ini();
   if(!copy){
      printf("Element Error: unable to initialize a element copy in element_copy function\n");
      return NULL;
   }
   *(copy->data) = *(e->data);
   return copy;
}

/**
*  It checks if two elements are equal, returning TRUE if they are, FALSE otherwise
*/
Bool element_equals(Element *e1, Element *e2){
   if(!e1){
      printf("Element Error: element 1 NULL pointer in element_equals function\n");
      return FALSE;
   }
   if(!e2){
      printf("Element Error: element 2 NULL pointer in element_equals function\n");
      return FALSE;
   }

   if(*(e1->data) == *(e2->data)){
      return TRUE;
   }
   return FALSE;
}

/**
*  It prints in the given file the data associated to the given element.
*  It returns the number of characters successfully printed, or -1 in error case
*/
int element_print(FILE *f, Element *e){
   if(!f){
      printf("Element Error: file NULL pointer in element_print function\n");
      return -1;
   }
   if(!e){
      printf("Element Error: element NULL pointer in element_print function\n");
      return -1;
   }
   return fprintf(f, "%d", *(e->data));
}
