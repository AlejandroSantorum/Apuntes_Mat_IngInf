#include "node.h"
#include "functions.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 255

Status imprimirColas(Queue *q1, Queue *q2, Queue *q3, FILE *f){
    int num;
    
    if(q1 == NULL || q2 == NULL || q3 == NULL || f == NULL ){
        return ERROR;
    }
    
    if(queue_isEmpty(q1)==TRUE){
        fprintf(f,"Cola 1: Queue vacia.\n");
    }
    else{
        fprintf(f, "Cola 1: Cola con %d elementos:\n", queue_size(q1));
        num = queue_print(f, q1);
        if(num==-1){
            return ERROR;
        }
    }
    
    if(queue_isEmpty(q2)==TRUE){
        fprintf(f,"Cola 2: Queue vacia.\n");
    }
    else{
        fprintf(f, "Cola 2: Cola con %d elementos:\n", queue_size(q2));
        num = queue_print(f, q2);
        if(num==-1){
            return ERROR;
        }
    }
    
    if(queue_isEmpty(q3)==TRUE){
        fprintf(f,"Cola 3: Queue vacia.\n");
    }
    else{
        fprintf(f, "Cola 3: Cola con %d elementos:\n", queue_size(q3));
        num = queue_print(f, q3);
        if(num==-1){
            return ERROR;
        }
    }
    
    return OK;
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
    
    if (argc < 2){
	fprintf(stdout, "Parámetros de entrada insuficientes: %d\n", argc);
	fprintf(stdout, "Introduzca nombre del programa y nombre del fichero de texto con los nodos.\n"); 
	return -1;
    }
    
    f1 = destroy_node_function;
    f2 = copy_node_function;
    f3 = print_node_function;
    
    q1 = queue_ini(f1, f2, f3);
    if(q1==NULL){
        return EXIT_FAILURE;
    }
    
    q2 = queue_ini(f1, f2, f3);
    if(q2==NULL){
        queue_destroy(q1);
        return EXIT_FAILURE;
    }
    
    q3 = queue_ini(f1, f2, f3);
    if(q3==NULL){
        queue_destroy(q1);
        queue_destroy(q2);
        return EXIT_FAILURE;
    }
    
    in = (FILE *) fopen(argv[1], "r");
    if (in == NULL){
	queue_destroy(q1);
        queue_destroy(q2);
        queue_destroy(q3);
	return EXIT_FAILURE;
    }
    
    fscanf(in, "%d", &nNodes);
    
    imprimirColas(q1, q2, q3, stdout);
    
    for(i=0; i<nNodes; i++){
        fscanf(in, "%d %s", &id, name);
        naux = node_ini();
        node_setId(naux, id);
        node_setName(naux, name);
        queue_insert(q1, naux);
        imprimirColas(q1, q2, q3, stdout);
        node_destroy(naux);
    }
    
    size = queue_size(q1);
    
    fprintf(stdout, "<<<Pasando la primera mitad de Cola 1 a Cola 2\n");
    for(i=0; i<(size/2); i++){
        naux = queue_extract(q1);
        queue_insert(q2, naux);
        imprimirColas(q1, q2, q3, stdout);
        node_destroy(naux);
    }
    
    fprintf(stdout, "<<<Pasando la segunda mitad de Cola 1 a Cola 3\n");
    for(; i<size; i++){
        naux = queue_extract(q1);
        queue_insert(q3, naux);
        imprimirColas(q1, q2, q3, stdout);
        node_destroy(naux);
    }
    
    queue_destroy(q1);
    queue_destroy(q2);
    queue_destroy(q3);
    
    return EXIT_SUCCESS;
}