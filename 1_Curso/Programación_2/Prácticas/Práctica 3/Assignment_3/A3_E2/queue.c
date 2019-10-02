/**
*  Project: Assignment 3 - ProgII subject
*  File: queue.c
*  Version: 2.0
*  Date: Apr 15, 2017
*  Revision date: May 30, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include "queue.h"

#define MAXQUEUE 1024 /** Maximum number of elements of a queue */

/** Queue data structure */
struct _Queue {
   void** head;
   void** end;
   void* item[MAXQUEUE];
   int size;
   destroy_elementqueue_function_type destroy_element_function;
   copy_elementqueue_function_type copy_element_function;
   print_elementqueue_function_type print_element_function;
};

/**
*  Function pointer types supported by queue
*/
Queue* queue_ini(destroy_elementqueue_function_type f1, copy_elementqueue_function_type f2, print_elementqueue_function_type f3){
   Queue *q=NULL;

   if(!f1 || !f2 || !f3){
      printf("Queue Error: parameter NULL pointer on queue_ini function\n");
      return NULL;
   }

   q = (Queue *) malloc(sizeof(Queue));
   if(!q){
      printf("Queue Error: unable to allocate memory for the new queue in queue_ini function\n");
      return NULL;
   }

   q->head = &(q->item[0]);
   q->end = &(q->item[0]);
   q->size = 0;
   q->destroy_element_function = f1;
   q->copy_element_function = f2;
   q->print_element_function = f3;
   return q;
}

/**
*  It frees the allocated memory for the given entire queue, including its elements
*/
void queue_destroy(Queue *q){
   if(!q){
      printf("Queue Warning: trying to free a NULL queue\n");
      return;
   }

   while(q->head != q->end){
      q->destroy_element_function(*(q->head));
      if(q->head != &(q->item[MAXQUEUE-1])){
         q->head++;
      } else{
         q->head = &(q->item[0]);
      }
   }
   free(q);
}

/**
*  It checks if the given queue is empty, returning TRUE in affirmative case,
*  FALSE otherwise
*/
Bool queue_isEmpty(Queue *q){
   if(!q){
      printf("Queue Error: NULL pointer in queue_isEmpty function\n");
      return FALSE;
   }

   if(q->head == q->end){
      return TRUE;
   }
   return FALSE;
}

/**
*  It checks if the given queue is full, returning TRUE in affirmative case,
*  FALSE otherwise
*/
Bool queue_isFull(Queue* q){
   void **aux = NULL;

   if(!q){
      printf("Queue Error: NULL pointer in queue_isFull function\n");
      return FALSE;
   }

   if(q->end == &(q->item[MAXQUEUE-1])){
      aux = &(q->item[0]);
   } else{
      aux = q->end+1;
   }
   if(aux==q->head){
      return TRUE;
   }
   return FALSE;
}

/**
*  It inserts a COPY (allocates memory for the copy) of the given element into the queue.
*  It returns the modified queue, or NULL if any error appears
*/
Queue* queue_insert(Queue *q, void *ele){
   void *aux=NULL;

   if(!q){
      printf("Queue Error: queue NULL pointer in queue_insert function\n");
      return NULL;
   }
   if(!ele){
      printf("Queue Error: element NULL pointer in queue_insert function\n");
      return NULL;
   }
   if(queue_isFull(q)==TRUE){
      printf("Queue Error: trying to insert an element in a completely filled queue\n");
      return NULL;
   }

   aux = q->copy_element_function(ele);
   if(!aux){
      printf("Queue Error: unable to copy the element to be inserted in queue_insert function\n");
      return NULL;
   }

   *(q->end) = aux;
   if(q->end != &(q->item[MAXQUEUE-1])){
      q->end++;
   } else{
      q->end = &(q->item[0]);
   }
   q->size++;
   return q;
}

/**
*  It extracts one element from the given queue, returning the element, or NULL if error case
*/
void * queue_extract(Queue *q){
   void *aux;

   if(!q){
      printf("Queue Error: queue NULL pointer in queue_extract function\n");
      return NULL;
   }
   if(queue_isEmpty(q)==TRUE){
      printf("Queue Error: trying to extract an element in a completely empty queue\n");
      return NULL;
   }

   aux = *(q->head);
   *(q->head) = NULL;
   if(q->head != &(q->item[MAXQUEUE-1])){
      q->head++;
   } else{
      q->head = &(q->item[0]);
   }
   q->size--;
   return aux;
}

/**
*  It returns the number of elements of the given queue.
*  -1 is returned in error case
*/
int queue_size(Queue *q){
   if(!q){
      printf("Queue Error: queue NULL pointer in queue_size function\n");
      return -1;
   }

   return q->size;
}

/**
*  It prints the given queue, returning the number of characters successfully
*  written, or -1 if any error is produced
*/
int queue_print(FILE *pf, Queue *q){
    int counter=0;
    void **i;

   if(!q){
      printf("Queue Error: queue NULL pointer in queue_print function\n");
      return -1;
   }
   if(!pf){
      printf("Queue Error: file NULL pointer in queue_print function\n");
      return -1;
   }

   if(queue_isEmpty(q)==TRUE){
      return fprintf(pf, "[ - ]\n");
   }

   i = q->head;
   while(i != q->end){
      counter += q->print_element_function(pf, *i);
      counter += fprintf(pf, "\n");
      if(i != &(q->item[MAXQUEUE-1])){
         i++;
      } else{
         i = &(q->item[0]);
      }
   }
   return counter;
}
