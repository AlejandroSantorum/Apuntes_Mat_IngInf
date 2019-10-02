/**
*  Project: Assignment 3 - ProgII subject
*  File: a3_e1_test.c
*  Version: 2.0
*  Date: Apr 15, 2017
*  Revision date: May 30, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "node.h"
#include "functions.h"

#define MAX 255

/**
*  Auxiliary function that prints the status of three queues
*/
void _print_queues(Queue *q1, Queue *q2, Queue*q3, FILE *f){
   if(!q1 || !q2 || !q3 || !f) return;

   if(queue_isEmpty(q1)==TRUE){
      fprintf(f, "Queue 1 -> EMPTY\n");
   } else{
      fprintf(f, "Queue 1 -> %d elements\n", queue_size(q1));
      queue_print(f, q1);
   }
   if(queue_isEmpty(q2)==TRUE){
      fprintf(f, "Queue 2 -> EMPTY\n");
   } else{
      fprintf(f, "Queue 2 -> %d elements\n", queue_size(q2));
      queue_print(f, q2);
   }
   if(queue_isEmpty(q3)==TRUE){
      fprintf(f, "Queue 3 -> EMPTY\n");
   } else{
      fprintf(f, "Queue 3 -> %d elements\n", queue_size(q3));
      queue_print(f, q3);
   }
}

int main(int argc, char** argv){
   destroy_elementqueue_function_type f1;
   copy_elementqueue_function_type f2;
   print_elementqueue_function_type f3;
   Queue *q1, *q2, *q3;
   FILE *in;
   Node *naux;
   char name[MAX];
   int i, id, nNodes, size;

   f1 = destroy_node_function;
   f2 = copy_node_function;
   f3 = print_node_function;

   q1 = queue_ini(f1, f2, f3);
   if(!q1){
      printf("Unable to initializate Queue 1\n");
      return EXIT_FAILURE;
   }
   q2 = queue_ini(f1, f2, f3);
   if(!q2){
      printf("Unable to initializate Queue 2\n");
      queue_destroy(q1);
      return EXIT_FAILURE;
   }
   q3 = queue_ini(f1, f2, f3);
   if(!q3){
      printf("Unable to initializate Queue 2\n");
      queue_destroy(q1);
      queue_destroy(q2);
      return EXIT_FAILURE;
   }

   in = (FILE *) fopen("nodes.txt", "r");
   if(!in){
      printf("Unable to open nodes file\n");
	   queue_destroy(q1);
      queue_destroy(q2);
      queue_destroy(q3);
	   return EXIT_FAILURE;
   }

   fscanf(in, "%d", &nNodes);
   _print_queues(q1, q2, q3, stdout);

   for(i=0; i<nNodes; i++){
      fscanf(in, "%d %s", &id, name);
      naux = node_ini();
      node_setId(naux, id);
      node_setName(naux, name);
      queue_insert(q1, naux);
      _print_queues(q1, q2, q3, stdout);
      node_destroy(naux);
   }
   size = queue_size(q1);
   fprintf(stdout, "<<<Moving first half part from Queue 1 to Queue 2\n");
   for(i=0; i<(size/2); i++){
      naux = queue_extract(q1);
      queue_insert(q2, naux);
      _print_queues(q1, q2, q3, stdout);
      node_destroy(naux);
   }

   fprintf(stdout, "<<<Moving second half part from Queue 1 to Queue 3\n");
   for(; i<size; i++){
      naux = queue_extract(q1);
      queue_insert(q3, naux);
      _print_queues(q1, q2, q3, stdout);
      node_destroy(naux);
   }

   queue_destroy(q1);
   queue_destroy(q2);
   queue_destroy(q3);
   fclose(in);
   return EXIT_SUCCESS;
}
