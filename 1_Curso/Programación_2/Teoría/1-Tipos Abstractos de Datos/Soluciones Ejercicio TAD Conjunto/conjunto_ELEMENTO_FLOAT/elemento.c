#include "elemento.h"
#include <string.h>

struct _Elemento {
    float dato;
};

Elemento *elemento_crear(const char *valor) {
    Elemento *pe;

    if(!valor)
        return NULL;
    
    pe = (Elemento*) malloc(sizeof(Elemento));
    if(pe)
        pe->dato = atof(valor);
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
    
    if((!pe1) || (!pe2))
        return -2; // devuelvo un valor diferente a los "normales"
                   // para avisar de error
    
    if(pe1->dato < pe2->dato)
        return -1;
    if(pe1->dato > pe2->dato)
        return 1;
    return 0;
}

Status elemento_imprimir(FILE *f, const Elemento *pe) {
    if((!f) || (!pe))
        return ERR;
    
    fprintf(f, "%f\n", pe->dato);
    return OK;
}        
