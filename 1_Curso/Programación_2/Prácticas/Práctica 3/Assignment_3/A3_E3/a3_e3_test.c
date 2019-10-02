/**
*  Project: Assignment 3 - ProgII subject
*  File: a3_e3_test.c
*  Version: 2.0
*  Date: Apr 16, 2017
*  Revision date: May 30, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "functions.h"

List* read_data_from_file(char *filename){
   FILE *in=NULL;
   List *l=NULL;
   destroy_elementlist_function_type f1;
   copy_elementlist_function_type f2;
   print_elementlist_function_type f3;
   cmp_elementlist_function_type f4;
   int aux;

   f1 = destroy_intp_function;
   f2 = copy_intp_function;
   f3 = print_intp_function;
   f4 = cmp_intp_function;

   l = list_ini(f1, f2, f3, f4);
   if(!l){
      printf("RDFF 1\n");
      return NULL;
   }

   in = (FILE*) fopen(filename, "r");
   if(!in){
      printf("RDFF 2\n");
	   list_destroy(l);
	   return NULL;
   }

   while(!feof(in)){
      fscanf(in,"%d",&aux);
      if(aux%2==0){
         if(!list_insertFirst(l, &aux)){
            printf("RDFF 3\n");
            list_destroy(l);
            fclose(in);
            return NULL;
         }
      } else if(aux%2==1){
         if(!list_insertLast(l, &aux)){
            printf("RDFF 4\n");
            list_destroy(l);
            fclose(in);
            return NULL;
         }
      }
      fprintf(stdout, "Printing list with %d elements:\n", list_size(l));
      list_print(stdout, l);
   }
   fclose(in);
   return l;
}

Status extract_data_from_list(List *l){
   int size, i, *aux1, *aux2;
   List *lOrdered=NULL;
   destroy_elementlist_function_type f1;
   copy_elementlist_function_type f2;
   print_elementlist_function_type f3;
   cmp_elementlist_function_type f4;

   if(!l){
      printf("EDFL 1\n");
      return ERROR;
   }

   f1 = destroy_intp_function;
   f2 = copy_intp_function;
   f3 = print_intp_function;
   f4 = cmp_intp_function;

   lOrdered = list_ini(f1, f2, f3, f4);
   if(!lOrdered){
      printf("EDFL 2\n");
      return ERROR;
   }

   size = list_size(l);
   for(i=0; i<(size/2); i++){
      aux1 = (int*)list_extractFirst(l);
      fprintf(stdout, "Extracted element from the beggining: [%d]\n", *aux1);
      fprintf(stdout, "Printing initial list with %d elements:\n", list_size(l));
      list_print(stdout, l);
      list_insertInOrder(lOrdered, aux1);
      fprintf(stdout, "Printing ordered list with %d elements:\n", list_size(lOrdered));
      list_print(stdout, lOrdered);
      free(aux1);

      aux2 = (int*)list_extractLast(l);
      fprintf(stdout, "Extract element from the end: [%d]\n", *aux2);
      fprintf(stdout, "Printing initial list with %d elements:\n", list_size(l));
      list_print(stdout, l);
      list_insertInOrder(lOrdered, aux2);
      fprintf(stdout, "Printing ordered list with %d elements:\n", list_size(lOrdered));
      list_print(stdout, lOrdered);
      free(aux2);
   }

   if(list_isEmpty(l)==FALSE){
      aux1 = (int *)list_extractFirst(l);
      fprintf(stdout, "Additional element due to a odd number of elements: [%d]\n", *aux1);
      fprintf(stdout, "Printing initial list with %d elementos:\n", list_size(l));
      list_print(stdout, l);
      list_insertInOrder(lOrdered, aux1);
      fprintf(stdout, "Printing ordered list with %d elementos:\n", list_size(lOrdered));
      list_print(stdout, lOrdered);
      free(aux1);
   }

   list_destroy(lOrdered);
   return OK;
}


int main(int argc, char** argv){
   List *l=NULL;
   Status check;

   l = read_data_from_file("data.txt");
   if(!l) return EXIT_FAILURE;

   check = extract_data_from_list(l);
   if(check==ERROR) return EXIT_FAILURE;

   list_destroy(l);
   return EXIT_SUCCESS;
}
