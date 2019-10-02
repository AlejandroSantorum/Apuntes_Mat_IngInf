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
*  Integer destruction function
*/
void destroy_intp_function(void* e){
   free((int*)e);
}

/**
*  Integer copy function
*/
void* copy_intp_function(void* e){
   int * dst;
   if (!e){
      printf("Error: NULL pointer in Integer copy function\n");
      return NULL;
   }

   dst = (int*)malloc(sizeof(int));
   if(!dst){
      printf("Error: unable to allocate memory for the copy in Integer copy function\n");
      return NULL;
   }

   *(dst) = *((int*)e);
   return dst;
}

/**
*  Integer print function
*/
int print_intp_function(FILE *f, void *e){
   if(!f){
      printf("Error: file NULL pointer in Integer print function\n");
      return -1;
   }
   if(!e){
      printf("Error: element NULL pointer in Integer print function\n");
      return -1;
   }

   return fprintf(f, "[%d]", *((int*)e));
}

/**
*  Integer compare function
*/
int cmp_intp_function(void *v1, void *v2){
   int num, a, b;

   if(!v1 || !v2){
      printf("Error: NULL parameter in Integer compare function\n");
      return 0;
   }

   a = *((int*)v1);
   b = *((int*)v2);

   num = a-b;
   if(num<0){
      return -1;
   }
   else if(num>0){
      return 1;
   }
   return 0;
}
