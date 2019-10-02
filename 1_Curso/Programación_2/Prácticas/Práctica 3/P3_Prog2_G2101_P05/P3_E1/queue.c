#include "queue.h"

#define MAXQUEUE 150


struct _Queue {
    void** head;
    void** end;
    void* item[MAXQUEUE];
    destroy_elementqueue_function_type destroy_element_function;
    copy_elementqueue_function_type copy_element_function;
    print_elementqueue_function_type print_element_function;
};


Queue* queue_ini(destroy_elementqueue_function_type f1, copy_elementqueue_function_type f2, print_elementqueue_function_type f3){
    Queue *q;
    
    if(f1==NULL || f2==NULL || f3==NULL){
        return NULL;
    }
    
    q = (Queue *) malloc(sizeof(Queue));
    if(q==NULL){
        return NULL;
    }
    
    q->head = &(q->item[0]);
    q->end = &(q->item[0]);
    
    q->destroy_element_function = f1;
    q->copy_element_function = f2;
    q->print_element_function = f3;
    
    return q;
}


void queue_destroy(Queue *q){
    if(q==NULL){
        return;
    }
    
    while(q->head != q->end){
        q->destroy_element_function(*(q->head));
        if(q->head != &(q->item[MAXQUEUE-1])){
            q->head++;
        }
        else{
            q->head = &(q->item[0]);
        }
    }
    
    free(q);
}


Bool queue_isEmpty(Queue *q){
    if(q==NULL){
        return FALSE;
    }
    
    if(q->head == q->end){
        return TRUE;
    }
    
    return FALSE;
}


Bool queue_isFull(Queue* q){
    void **aux = NULL; 
    
    if(q==NULL){
        return FALSE;
    }
    
    if(q->end == &(q->item[MAXQUEUE-1])){
        aux = &(q->item[0]);
    }
    else{
        aux = q->end+1;
    }
    
    if(aux==q->head){
        return TRUE;
    }
    
    return FALSE;
}


Queue* queue_insert(Queue *q, void *ele){
    void *aux=NULL;
    
    if(q==NULL || ele==NULL || queue_isFull(q)==TRUE){
        return NULL;
    }
    
    aux = q->copy_element_function(ele);
    if(aux==NULL){
        return NULL;
    }
    
    *(q->end) = aux;
    
    
    if(q->end != &(q->item[MAXQUEUE-1])){
        q->end++;
    }
    else{
        q->end = &(q->item[0]);
    }
    
    return q;
}


void * queue_extract(Queue *q){
    void *aux;
    
    if(q==NULL || queue_isEmpty(q)==TRUE){
        return NULL;
    }
    
    aux = *(q->head);
        
    *(q->head) = NULL;
    
    if(q->head != &(q->item[MAXQUEUE-1])){
        q->head++;
    }
    else{
        q->head = &(q->item[0]);
    }
    
    return aux;
}



int queue_size(Queue *q){
    int contador=0;
    void **i;
    
    if(q==NULL){
        return -1;
    }
    
    if(queue_isFull(q)==TRUE){
        return MAXQUEUE-1;
    }
    
    if(queue_isEmpty(q)==TRUE){
        return 0;
    }
    
    i = q->head;
    
    while(i != q->end){
        if(i != &(q->item[MAXQUEUE-1])){
            i++;
        }
        else{
            i = &(q->item[0]);
        }
        contador++;
    }
    return contador;
}


int queue_print(FILE *pf, Queue *q){
    int contador=0;
    void **i;
    
    if(q==NULL || pf==NULL){
        return -1;
    }
    
    i = q->head;
    
    while(i != q->end){
        contador += q->print_element_function(pf, *i);
        
        if(i != &(q->item[MAXQUEUE-1])){
            i++;
        }
        else{
            i = &(q->item[0]);
        }
        contador++;
    }
    
    return contador;
}
