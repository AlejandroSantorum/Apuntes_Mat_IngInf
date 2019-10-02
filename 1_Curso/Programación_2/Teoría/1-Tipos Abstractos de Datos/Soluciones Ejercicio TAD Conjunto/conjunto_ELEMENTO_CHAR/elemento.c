#include "elemento.h"
#include <string.h>

struct _Elemento {
    char dato;
};

Elemento *elemento_crear(const char *valor) {
    Elemento *pe;

    if(!valor)
        return NULL;
    pe = (Elemento*) malloc(sizeof(Elemento));
    if(pe) {
        if(strlen(valor) == 1)
            pe->dato = valor[0];
        else // Error, no nos están pasando un char
            pe->dato = '\0'; // lo marcamos con un símbolo especial
    }
    
    return pe;
}


void elemento_liberar(Elemento *pe) {    
    if(pe) // esto equivale a pe != NULL
        free(pe);
}

Elemento *elemento_copiar(const Elemento *pe_src) {
    Elemento *pe_dst;
    
    pe_dst = (Elemento*) malloc(sizeof(Elemento));
    if(pe_dst)
        pe_dst->dato = pe_src->dato;
    return pe_dst;
}

int elemento_comparar(const Elemento *pe1, const Elemento *pe2) {
// Devuelve: 0 si son iguales
//          -1 si elemento 1 va antes   que elemento 2
//           1 si elemento 1 va después que elemento 2
    
    if(pe1->dato < pe2->dato)
        return -1;
    if(pe1->dato > pe2->dato)
        return 1;
    return 0;
}

Status elemento_imprimir(FILE *f, const Elemento *pe) {
    if((!f) || (!pe))
        return ERR;
    
    fprintf(f, "%c\n", pe->dato);
    return OK;
}        
