#include "elemento.h"
#include <string.h>

#define MAX_CADENA 100 // longitud máxima de la cadena + 1
                       // (ya que hay que tener en cuenta el
                       // carácter especial fin de cadena '\0')

struct _Elemento {
    char cadena[MAX_CADENA];
};

Elemento *elemento_crear(const char *valor) {
    Elemento *pe;
    
    if((!valor) || (strlen(valor) >= MAX_CADENA)) // si valor es NULL o la
                                                  // cadena es demasiado grande
        return NULL;
    
    pe = (Elemento*) malloc(sizeof(Elemento));
    if(pe) // equivale a pe != NULL
        strcpy(pe->cadena, valor);
    return pe; // si el malloc ha ido mal, devuelve NULL
}

void elemento_liberar(Elemento *pe) {
    if(pe) // esto equivale a pe != NULL
        free(pe);
}

Elemento *elemento_copiar(const Elemento *pe_src) {
    Elemento *pe_dst;
    
    if(!pe_src)
        return NULL;
    
    pe_dst = (Elemento*) malloc(sizeof(Elemento)+1);
    // las cadenas siempre tienen internamente un carácter más, el '\0'
    
    if(pe_dst)
        strcpy(pe_dst->cadena, pe_src->cadena);
    return pe_dst;
}

int elemento_comparar(const Elemento *pe1, const Elemento *pe2) {
// Devuelve: 0 si son iguales
//          -1 si elemento 1 va antes   que elemento 2
//           1 si elemento 1 va después que elemento 2
    
    if((!pe1) || (!pe2))
        return -2; // devuelvo un valor diferente a los "normales"
                   // para avisar de error
    
    return strcmp(pe1->cadena, pe2->cadena);
}

Status elemento_imprimir(FILE *f, const Elemento *pe) {
    if((!f) || (!pe))
        return ERR;
    
    fprintf(f, "%s\n", pe->cadena);
    return OK;
}        
