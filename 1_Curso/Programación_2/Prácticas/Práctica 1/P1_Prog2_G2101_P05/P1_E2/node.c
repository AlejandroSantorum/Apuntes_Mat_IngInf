#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"


struct _Node {
 char name[100];
 int id;
};

Node* node_ini(){
    Node *nodo;
    
    nodo = (Node *) malloc(sizeof(Node));
    
    if(nodo ==NULL){
        return NULL;
    }
    
    return nodo;
}

void node_destroy(Node* n){
    free(n);
}

int node_getId(const Node* n){
    if(n==NULL){
        return -1;
    }
    
    return n->id;
}

char* node_getName(const Node* n){
    if(n==NULL){
        return NULL;
    }
    return n->name;
}

Node* node_setId(Node* n, const int id){
    if(n==NULL){
        return NULL;
    }
    n->id = id;
    
    return n;
}

Node* node_setName(Node* n, const char* name){
    if(n==NULL){
        return NULL;
    }
    strcpy(n->name, name);
    
    return n;
}

Bool node_equals(const Node* n1, const Node* n2){
    if(n1->id != n2->id){
        return FALSE;
    }
    else if(strcmp(n1->name, n2->name)!=0){
        return FALSE;
    }
    
    return TRUE;
}

Node* node_copy(const Node* src){
    Node *copy;
    copy = node_ini();
        
    if(src==NULL || copy==NULL){
        return NULL;
    }
    
    strcpy(copy->name, src->name);
    copy->id = src->id;
    
    return copy;   
}

int node_print(FILE *pf, const Node *n){
    int num=0;
    
    if(pf==NULL || n==NULL){
        return -1;
    }
    
    num = fprintf(pf, "[%d, %s]", n->id, n->name);
    
    return (num);
}
