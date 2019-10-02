#include "functions4.h"

/*
 * En este fichero se definen las funciones de destrucción, copia e impresión
 *  de elementos a almacenar en una pila para distintos tipos de datos */

 
/* Las siguientes funciones se usarán cuando se quieran guardar enteros en la pila.
 *  Ojo! Estas funciones reciben un puntero a entero, no una estructura
 *  con un puntero a entero*/ 

void destroy_str_function(void* e){
    free((char *)e);
}


void * copy_str_function(const void* e){
    char *dst;
    int lon;
    if (e == NULL)
        return NULL;
    
    lon = strlen((char *)e) + 1;
    dst = (char *) malloc(lon * sizeof(char));
    if(dst == NULL){
        return NULL;
    }
    
    /*Copiamos el elemento*/
    strcpy(dst, (char *)e);
    
    return dst;
} 


int    print_str_function(FILE * f, const void* e){
    if (f != NULL && e != NULL)
        return fprintf(f, " %s", ((char *)e));
    
    return -1;
}

int cmp_str_function(const void *v1, const void *v2){
    int cmp;
    
    cmp = strcmp((char *)v1, (char *)v2);
    
    return cmp;
}