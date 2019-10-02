#include "functions2.h"

/* Las siguientes se usarán cuando se quieran guardar nodos en la pila */

void destroy_node_function(void* e){
    node_destroy((Node *)e);
}


void * copy_node_function(const void* e){
    return node_copy((Node *)e);
}


int  print_node_function(FILE * f, const void* e){
    return node_print(f, (Node *)e);
} 

int cmp_node_function(const void *v1, const void *v2){
    return node_cmp((Node *)v1,(Node *)v2);
}

