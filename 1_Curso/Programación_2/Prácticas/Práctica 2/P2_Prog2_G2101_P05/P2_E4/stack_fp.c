#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack_fp.h"

struct _Stack {
    int top;
    void * item[MAXSTACK];
    destroy_element_function_type destroy_element_function;
    copy_element_function_type copy_element_function;
    print_element_function_type print_element_function;
};

Stack * stack_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3){
    Stack *p;
    int i;
    
    if(f1==NULL || f2==NULL || f3==NULL){
        return NULL;
    }
    
    p = (Stack *) malloc(sizeof(Stack));
    if(p==NULL){
        return NULL;
    }
    for(i=0; i<MAXSTACK; i++){
        p->item[i]=NULL;
    }

    p->top = -1;
    
    p->destroy_element_function = f1;
    p->copy_element_function = f2;
    p->print_element_function = f3;
    
    return p;
}


void stack_destroy(Stack *p){
    int i;
    
    if(p==NULL){
        return;
    }
    
    for(i=0; i<=(p->top); i++){
        p->destroy_element_function(p->item[i]);
    }
    
    free(p);
}


Stack * stack_push(Stack *p, const void *ele){
    void *aux=NULL;
    
    if(p==NULL || ele==NULL || stack_isFull(p)==TRUE){
        return NULL;
    }
    
    aux = p->copy_element_function(ele);
    if(aux == NULL){
        return NULL;
    }
    
    (p->top)++;
    p->item[p->top] = aux;
    
    return p;
}


void * stack_pop(Stack *p){
    void *ele=NULL;
    
    if(p==NULL || stack_isEmpty(p)==TRUE){
        return NULL;
    }
    
    ele = p->item[p->top];
    p->item[p->top] = NULL;
    (p->top)--;
    
    return ele;
}


void * stack_top(const Stack *p){
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


int stack_print(FILE*f, const Stack*p){
    int i, num=0;
    
    if(p==NULL || f==NULL){
        return -1;
    }
    for(i=p->top; i>=0; i--){
        num += p->print_element_function(f, p->item[i]);
    }
    
    return num;
}