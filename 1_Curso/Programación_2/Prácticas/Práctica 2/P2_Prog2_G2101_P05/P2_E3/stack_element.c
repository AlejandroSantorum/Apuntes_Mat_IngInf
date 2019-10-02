#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack_element.h"
#include "element.h"

struct _Stack{
    Element *item[MAXSTACK];
    int top;
};

Stack * stack_ini(){
    Stack *p;
    int i;
    
    p = (Stack *) malloc(sizeof(Stack));
    if(p==NULL){
        return NULL;
    }
    for(i=0; i<MAXSTACK; i++){
        p->item[i]=NULL;
    }
    
    p->top = -1;
    
    return p;
}


void stack_destroy(Stack *p){
    int i;
    
    for(i=0; i<=(p->top); i++){
        element_destroy(p->item[i]);
    }
    
    free(p);
}


Stack * stack_push(Stack *p, const Element *ele){
    Element *aux=NULL;
    
    if(p==NULL || ele==NULL || stack_isFull(p)==TRUE){
        return NULL;
    }
    
    aux = element_copy(ele);
    if(aux == NULL){
        return NULL;
    }
    
    p->top++;
    p->item[p->top] = aux;
    
    return p;
}


Element * stack_pop(Stack *p){
    /*Element *ele=NULL;*/
    
    if(p==NULL || stack_isEmpty(p)==TRUE){
        return NULL;
    }
    
    /*ele = p->item[p->top];
    p->item[p->top] = NULL;
    (p->top)--;*/
    
    p->top--;
    return p->item[p->top+1];
    
    /*return ele;*/
}


Element * stack_top(const Stack *p){
    if(p==NULL || stack_isEmpty(p)==TRUE){
        return NULL;
    }
    
    return (p->item[p->top]);  
}


Bool stack_isEmpty(const Stack *p){
    if(p==NULL){
        return FALSE;
    }
    
    if((p->top) == -1){
        return TRUE;
    }
    
    return FALSE;
}


Bool stack_isFull(const Stack *p){
    if(p==NULL){
        return FALSE;
    }
    
    if(p->top == (MAXSTACK-1)){
        return TRUE;
    }
    
    return FALSE;
}


int stack_print(FILE *f, const Stack *p){
    int i, num=0;
    
    if(p==NULL || f==NULL){
        return -1;
    }
    for(i=p->top; i>=0; i--){
        num += element_print(f, p->item[i]);
    }
    
    return num;
}