/**
*  Project: Assignment 3 - ProgII subject
*  File: list.c
*  Version: 2.0
*  Date: Apr 16, 2017
*  Revision date: May 30, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include "list.h"

/** Private list's nodes data structure */
typedef struct _NodeList{
    void * data;
    struct _NodeList *next;
}NodeList;

/** List data structure */
struct _List {
    NodeList *first;
    int sizeList;    /*Entero añadido a la estructura de lista para ayudar a conocer su tamaño*/
    destroy_elementlist_function_type   destroy_element_function;
    copy_elementlist_function_type      copy_element_function;
    print_elementlist_function_type     print_element_function;
    cmp_elementlist_function_type     cmp_element_function;
};

/**
*  Private function: it initializes one list node
*/
NodeList* nodeList_ini(){
   NodeList *nl=NULL;

   nl = (NodeList *) malloc(sizeof(NodeList));
   if(!nl){
      return NULL;
   }

   nl->data = NULL;
   nl->next = NULL;
   return nl;
}

/**
*  Private function: it frees the allocated memory for a list node
*/
void nodeList_destroy(NodeList *nl, List *l){
   if(!nl || !l){
      return;
   }

   if(nl->data){
      l->destroy_element_function(nl->data);
   }
   free(nl);
}

/**
*  It initializes a list, allocating memory for it and for its componenets,
*  returning the created list, or NULL in error case
*/
List * list_ini(destroy_elementlist_function_type f1, copy_elementlist_function_type f2, print_elementlist_function_type f3, cmp_elementlist_function_type f4){
   List *l=NULL;

   if(!f1 || !f2 || !f3){
      printf("List Error: list initialization parameters equal NULL in list_ini function\n");
      return NULL;
   }

   l = (List *) malloc(sizeof(List));
   if(!l){
      printf("List Error: unable to allocate memory to initializate a new list in list_ini function\n");
      return NULL;
   }

   l->destroy_element_function = f1;
   l->copy_element_function = f2;
   l->print_element_function = f3;
   l->cmp_element_function = f4;
   l->first = NULL;
   l->sizeList = 0;
   return l;
}

/**
*  It frees all the allocated memory for the given list
*/
void list_destroy(List* l){
   if(!l){
      printf("List Warning: trying to free a NULL list\n");
      return;
   }

   while(list_isEmpty(l)==FALSE){
      l->destroy_element_function(list_extractFirst(l));
   }
   free(l);
}

/**
*  It inserts a COPY of the given element into the given list at the beggining.
*  It returns the modified list or NULL in error case
*/
List* list_insertFirst(List *l, void *ele){
   NodeList *nl=NULL;

   if(!l){
      printf("List Error: list NULL pointer in list_insertFirst function\n");
      return NULL;
   }
   if(!ele){
      printf("List Error: element NULL pointer in list_insertFirst function\n");
      return NULL;
   }

   nl = nodeList_ini();
   if(!nl){
      printf("List Error: unable to allocate memory for a new list element in list_insertFirst function\n");
      return NULL;
   }

   nl->data = l->copy_element_function(ele);
   if(!nl->data){
      printf("List Error: unable to copy the element to be inserted in list_insertFirst function\n");
      nodeList_destroy(nl, l);
      return NULL;
   }

   nl->next = l->first;
   l->first = nl;
   l->sizeList++;
   return l;
}

/**
*  It inserts a COPY of the given element into the given list at the end.
*  It returns the modified list or NULL if any error occurs
*/
List* list_insertLast(List *l, void *ele){
   NodeList *nl=NULL, *i=NULL;

   if(!l){
      printf("List Error: list NULL pointer in list_insertLast function\n");
      return NULL;
   }
   if(!ele){
      printf("List Error: element NULL pointer in list_insertLast function\n");
      return NULL;
   }

   nl = nodeList_ini();
   if(!nl){
      printf("List Error: unable to allocate memory for a new list element in list_insertLast function\n");
      return NULL;
   }

   nl->data = l->copy_element_function(ele);
   if(!nl->data){
      printf("List Error: unable to copy the element to be inserted in list_insertLast function\n");
      nodeList_destroy(nl, l);
      return NULL;
   }

   if(list_isEmpty(l)==TRUE){
      l->first = nl;
      l->sizeList++;
      return l;
   }
   for(i=l->first; i->next != NULL; i=i->next); /* Getting to the end of the linked list */

   i->next = nl;
   l->sizeList++;
   return l;
}

/**
*  It inserts in order a COPY of the given element into the given list.
*  It returns the modfied list or NULL in error case
*/
List* list_insertInOrder(List *l, void *ele){
   NodeList *nl=NULL, *i=NULL;

   if(!l){
      printf("List Error: list NULL pointer in list_insertInOrder function\n");
      return NULL;
   }
   if(!ele){
      printf("List Error: element NULL pointer in list_insertInOrder function\n");
      return NULL;
   }

   nl = nodeList_ini();
   if(!nl){
      printf("List Error: unable to allocate memory for a new list element in list_insertInOrder function\n");
      return NULL;
   }

   nl->data = l->copy_element_function(ele);
   if(!nl->data){
      printf("List Error: unable to copy the element to be inserted in list_insertInOrder function\n");
      nodeList_destroy(nl, l);
      return NULL;
   }

   if(list_isEmpty(l)==TRUE){ /* If the list is empty we insert it directly */
      l->first = nl;
      l->sizeList++;
      return l;
   }

   if((l->cmp_element_function(nl->data, l->first->data))<0){ /* Inserting it directly if it is "better" then the first one */
      nl->next = l->first;
      l->first = nl;
      l->sizeList++;
      return l;
   }

   i = l->first;
   while(i->next->next != NULL){
      if((l->cmp_element_function(nl->data, i->next->data))<0){
         nl->next = i->next;
         i->next = nl;
         l->sizeList++;
         return l;
      }
      i = i->next;
   }

   if((l->cmp_element_function(nl->data, i->next->data))<0){
      nl->next = i->next;
      i->next = nl;
      l->sizeList++;
      return l;
   } else{
      i->next->next = nl;
      l->sizeList++;
      return l;
   }
}

/**
*  It extracts the element of the beggining of the given list, or NULL in error case
*/
void * list_extractFirst(List *l){
   void *eleaux=NULL;
   NodeList *naux=NULL;

   if(!l){
      printf("List Error: list NULL pointer in list_extractFirst function\n");
      return NULL;
   }
   if(list_isEmpty(l)==TRUE){
      printf("List Error: trying to extract one (first) element from a empty list\n");
      return NULL;
   }

   naux = l->first;
   eleaux = l->copy_element_function(naux->data);
   if(!eleaux){
      printf("List Error: unable to copy the element to be extracted in list_extractFirst function\n");
      return NULL;
   }

   l->first = naux->next;
   nodeList_destroy(naux, l);
   l->sizeList--;
   return eleaux;
}

/**
*  It extracts the element of the end of the given list , or NULL in error case
*/
void* list_extractLast(List *l){
   void *eleaux=NULL;
   NodeList *naux=NULL;

   if(!l){
      printf("List Error: list NULL pointer in list_extractLast function\n");
      return NULL;
   }
   if(list_isEmpty(l)==TRUE){
      printf("List Error: trying to extract one (last) element from a empty list\n");
      return NULL;
   }

   if(!l->first->next){ /* Case 1: just one element in the list */
      eleaux = l->copy_element_function(l->first->data);
      if(!eleaux){
         printf("List Error: unable to copy the element to be extracted in list_extractLast function (1)\n");
         return NULL;
      }
      nodeList_destroy(l->first, l);
      l->first = NULL;
      l->sizeList--;
      return eleaux;
   }

   /* Case 2: list with more than one element */
   for(naux=l->first; (naux->next)->next!=NULL; naux=naux->next);

   eleaux = l->copy_element_function(naux->next->data);
   if(!eleaux){
      printf("List Error: unable to copy the element to be extracted in list_extractLast function (2)\n");
      return NULL;
   }

   nodeList_destroy(naux->next, l);
   naux->next=NULL;
   l->sizeList--;
   return eleaux;
}

/**
*  It checks if the given list is empty, returning TRUE in affirmative case or FALSE otherwise
*/
Bool list_isEmpty(List *l){
   if(!l){
      printf("List Error: NULL pointer in list_isEmpty function\n");
      return FALSE;
   }

   if(!l->first){
      return TRUE;
   }
   return FALSE;
}

/**
*  It returns the i-th (obviously, starting at 0) element of the given list, NULL is returned in error case
*/
void* list_get(List* l, int i){
   int j;
   NodeList *naux=NULL;
   void *eleaux=NULL;

   if(!l){
      printf("List Error: list NULL pointer in list_get function\n");
      return NULL;
   }
   if(i<0){
      printf("List Error: negative index in list_get function\n");
      return NULL;
   }
   if(i>l->sizeList){
      printf("List Error: index out of bounds in list_get function\n");
      return NULL;
   }

   /* Moving to the i-th element */
   for(j=0, naux=l->first; j<i; j++,naux=naux->next);

   eleaux = l->copy_element_function(naux->data);
   if(!eleaux){
      printf("List Error: unable to copy the element to be extracted in list_get function\n");
      return NULL;
   }

   return eleaux;
}

/**
*  It returns the size of the given list. -1 if any error appears
*/
int list_size(List *l){
   if(l==NULL){
      printf("List Error: NULL pointer in list_size function\n");
      return -1;
   }

   return l->sizeList;
}

/**
*  It prints the given list, returning the number of the characters written
*  successfully, or -1 if any error is produced
*/
int list_print(FILE *f, List *l){
   int num=0;
   NodeList *nl=NULL;

   if(!f){
      printf("List Error: file NULL pointer in list_print function\n");
      return -1;
   }
   if(!l){
      printf("List Error: list NULL pointer in list_print function\n");
      return -1;
   }

   if(list_isEmpty(l)==TRUE){
      return fprintf(f, "[ - ]\n");
   }

   for(nl = l->first; nl!=NULL; nl = nl->next){
      num += l->print_element_function(f, nl->data);
      num += fprintf(f, "\n");
   }
   return num;
}

/**
*  It checks if a given list already contains a given element.
*  It returns TRUE in affirmative case, NULL otherwise
*/
Bool list_isElement(List *l, void *ele){
   NodeList *nl=NULL;

   if(!l){ /* Error */
      printf("List Error: list NULL pointer in list_isElement function\n");
      return FALSE;
   }
   if(!ele){ /* Error */
      printf("List Error: element NULL pointer in list_isElement function\n");
      return FALSE;
   }
   if(list_isEmpty(l)==TRUE) return FALSE;

   for(nl = l->first; nl->next != NULL; nl=nl->next){
      if((l->cmp_element_function(nl->data, ele))==0){
         return TRUE;
      }
   }
   if((l->cmp_element_function(nl->data, ele))==0){
      return TRUE;
   }
   return FALSE;
}
