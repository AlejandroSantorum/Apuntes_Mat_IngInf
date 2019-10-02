#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

struct _Node {
 char *name;
 int id;
};

Node* node_ini(){
    Node *n;
    
    n = (Node *) malloc(sizeof(Node));
    if(n == NULL){
        return NULL;
    }
    
    n->name = NULL;
    
    return n;
}

void node_destroy(Node* n){
    if(n == NULL){
        return;
    }
    free(n->name);
    free(n);
}

int node_getId(const Node* n){
    if(n==NULL){
        return -1;
    }
    
    return n->id;
}

char* node_getName(Node* n){
    if(n == NULL || n->name == NULL){
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

Node* node_setName(Node* n, const char *name){
    int lon;
    
    if(n==NULL){
        return NULL;
    }
    
    lon = strlen(name);
    n->name = (char *) malloc((lon+1)*sizeof(char));
    if(n->name == NULL){
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

Node* node_copy(Node *src){
    Node *copy;
    char *name;
    int lon;
        
    if(src==NULL){
        return NULL;
    }
    
    copy = node_ini();
    if(copy == NULL){
        return NULL;
    }
    
    /*calculamos longitud del nombre del nodo a copiar*/
    lon = strlen(src->name);
    
    /*reservamos espacio de memoria para el nombre del nodo que queremos copiar*/
    name = (char *) malloc((lon+1)*sizeof(char));
    
    /*copiamos el nombre*/
    strcpy(name, src->name);
    /*y lo copiamos en el nodoCopia*/
    if(node_setName(copy, name)==NULL){
        return NULL;
    }
    /*Copiamos Id´s*/
    copy->id = src->id;
    
    /*Liberamos la cadena de caracteres auxiliar para copiar el nombre pues ya no lo necesitamos*/
    free(name);
    
    return copy;   
}

int node_cmp(Node *n1,Node *n2){
    int num, a, b;
    
    a = node_getId(n1);
    b = node_getId(n2);
    
    num = a-b;
    if(num<0){
        return -1;
    }
    else if(num>0){
        return 1;
    }
    
    return 0;
}

int node_print(FILE *pf, const Node *n){
    int num=0;
    
    if(pf==NULL || n==NULL){
        return -1;
    }
    
    num = fprintf(pf, "[%d, %s]", n->id, n->name);
    
    return num;
}
