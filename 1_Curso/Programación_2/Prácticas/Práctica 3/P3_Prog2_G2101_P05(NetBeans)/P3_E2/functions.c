#include <stdlib.h>
#include "functions.h"

/*
 * En este fichero se definen las funciones de destrucción, copia e impresión
 *  de elementos a almacenar en una pila para distintos tipos de datos */


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
