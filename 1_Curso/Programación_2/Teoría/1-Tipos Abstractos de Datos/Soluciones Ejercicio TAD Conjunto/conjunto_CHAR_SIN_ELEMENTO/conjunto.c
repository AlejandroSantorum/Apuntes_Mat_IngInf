#include "conjunto.h"

#define MAX_ELEMS 1000

struct _Conjunto {
    char datos[MAX_ELEMS];
    int n;
};

Conjunto *conjunto_crear() {
    Conjunto *pc;
    
    pc = (Conjunto*) malloc(sizeof(Conjunto));
    if(pc) // esto equivale a pc != NULL
        pc->n = 0;
    
    return pc;
}

void conjunto_liberar(Conjunto *pc) {
    if(pc)
        free(pc);
}

Status conjunto_vaciar(Conjunto *pc) {
    if(!pc)
        return ERR;
    pc->n = 0;    
    return OK;
}

int conjunto_cardinalidad(const Conjunto *pc) {
    if(!pc)
        return -1; // devuelvo un valor "absurdo" para informar del error
    return pc->n;
}

Bool conjunto_buscar(const Conjunto *pc, char elem) {    
    int i;
    
    if(!pc)
        return FALSE;

    for(i=0; i<conjunto_cardinalidad(pc); i++)
        if(pc->datos[i] == elem)
            return TRUE;
    
    return FALSE;
}

Status conjunto_insertar(Conjunto *pc, char elem) {

    if( (!pc) || (pc->n == MAX_ELEMS) || (conjunto_buscar(pc, elem) == TRUE))
        return ERR;
    
    pc->datos[pc->n] = elem;
    pc->n ++;
    return OK;
}

Status conjunto_imprimir(FILE *f, const Conjunto *pc) {

    int i;
    
    if( (!f) || (!pc))
        return ERR;
    
    for(i=0; i<conjunto_cardinalidad(pc); i++)
        fprintf(f, "%c\n", pc->datos[i]);
    
    return OK;
}

Conjunto *conjunto_union(const Conjunto *pc1, const Conjunto *pc2) {
    
    Conjunto *pc3;
    int i;
    
    pc3 = conjunto_crear();
    if(!pc3)
        return NULL;

    // primero copio el conjunto 1 en el 3, que está vacío ya que lo acabo
    // de crear. Como los elementos no están repetidos dentro de 1 por
    // definición, y como por otra parte el 3 está vacío inicialmente, no
    // tengo que controlar repeticiones
    for(i=0; i<conjunto_cardinalidad(pc1); i++)
        if(conjunto_insertar(pc3, pc1->datos[i]) == ERR) {
            conjunto_liberar(pc3);
            return NULL;
        }

    // ahora voy introduciendo los elementos del conjunto 2 en el 3,
    // chequeando antes si están ya en él
    for(i=0; i<conjunto_cardinalidad(pc2); i++)
        if(conjunto_buscar(pc3, pc2->datos[i]) == FALSE) {
            if(conjunto_insertar(pc3, pc2->datos[i]) == ERR) {
                conjunto_liberar(pc3);
                return NULL;
            }
        }
    
    return pc3;    
}

Conjunto *conjunto_interseccion(const Conjunto *pc1, const Conjunto *pc2) {
    
    Conjunto *pc3;
    int i;
    int n1, n2;
    
    pc3 = conjunto_crear();
    if(!pc3)
        return NULL;
    
    n1 = conjunto_cardinalidad(pc1);
    n2 = conjunto_cardinalidad(pc2);
    if(n1 < n2) {
        for(i=0; i<n1; i++)
            if(conjunto_buscar(pc2, pc1->datos[i]) == TRUE)
                if(conjunto_insertar(pc3, pc1->datos[i]) == ERR) {
                    conjunto_liberar(pc3);
                    return NULL;
                }
    }
    else
        for(i=0; i<n2; i++)
            if(conjunto_buscar(pc1, pc2->datos[i]) == TRUE)
                if(conjunto_insertar(pc3, pc2->datos[i]) == ERR) {
                    conjunto_liberar(pc3);
                    return NULL;
                }
    
    return pc3;
}

Status conjunto_eliminar(Conjunto *pc, char dato) {

    int i, j, n;
    
    if( (!pc) || (!(pc->n)))
        return ERR;
    
    n = conjunto_cardinalidad(pc);
    for(i=0; i<n; i++)
        if(pc->datos[i] == dato) {
            // reajusto los datos dentro del array para que no quede
            // un "hueco"
            pc->datos[i] = pc->datos[n-1];
            pc->datos[n-1] = '\0';
            pc->n --;
            return OK;
        }
    return ERR;
}
