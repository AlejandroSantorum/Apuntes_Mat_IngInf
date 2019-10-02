#include "functions1.h"

/*
 * En este fichero se definen las funciones de destrucción, copia e impresión
 *  de elementos a almacenar en una pila para distintos tipos de datos */

 
/* Las siguientes funciones se usarán cuando se quieran guardar enteros en la pila.
 *  Ojo! Estas funciones reciben un puntero a entero, no una estructura
 *  con un puntero a entero*/ 

void destroy_intp_function(void* e){
    free((int*)e);
}


void * copy_intp_function(const void* e){
    int * dst;
    if (e == NULL)
        return NULL;

    dst = (int*)malloc(sizeof(int));
    if(dst == NULL){
        return NULL;
    }
    
    /*Copiamos el elemento*/
    *(dst) = *((int*)e);
    return dst;
} 


int    print_intp_function(FILE * f, const void* e){
    if (f != NULL && e != NULL)
        return fprintf(f, "[%d]\n", *((int*)e));
    
    return -1;
}

int cmp_intp_function(void *v1, void *v2){
    int num, a, b;
    
    a = *((int *)v1);
    b = *((int *)v2);
    
    num = a-b;
    if(num<0){
        return -1;
    }
    else if(num>0){
        return 1;
    }
    
    return 0;
}
